#include "GLWidget.h"

#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include "../Core/stringHelp.cpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"
#include "../Parametric/ParametricSurfaces3.h"

using namespace std;

/*komplikáltabb scene
 * szép görbék
 * knot points állítása*/

#include <Core/Exceptions.h>

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
    {
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {

        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(width()) / static_cast<double>(height());
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;


        // ...
        HCoordinate3 direction(0.0, 0.0, 1.0, 0.0);
        Color4       ambient(0.4, 0.4, 0.4, 1.0);
        Color4       diffuse(0.8, 0.8, 0.8, 1.0);
        Color4       specular(1.0, 1.0, 1.0, 1.0);

        _dl = new (nothrow) DirectionalLight(GL_LIGHT0, direction, ambient, diffuse, specular);

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...
            HCoordinate3 direction(0.0, 0.0, 1.0, 0.0);
            Color4       ambient(0.4, 0.4, 0.4, 1.0);
            Color4       diffuse(0.8, 0.8, 0.8, 1.0);
            Color4       specular(1.0, 1.0, 1.0, 1.0);

            _dl = new (nothrow) DirectionalLight(GL_LIGHT0, direction, ambient, diffuse, specular);

            if(!_dl){
                throw Exception("Could not create the directional light object!");
            }

            glEnable(GL_LIGHTING);
            glEnable(GL_NORMALIZE);
            _shaders.ResizeColumns(4);
            string vertFileName, fragFileName;
            for(int i = 0; i < 4; ++i){
                switch(i){
                    case 0:
                        vertFileName = "Shaders/directional_light.vert";
                        fragFileName = "Shaders/directional_light.frag";
                        break;
                    case 1:
                        vertFileName = "Shaders/reflection_lines.vert";
                        fragFileName = "Shaders/reflection_lines.frag";
                        break;
                    case 2:
                        vertFileName = "Shaders/toon.vert";
                        fragFileName = "Shaders/toon.frag";
                        break;
                    case 3:
                        vertFileName = "Shaders/two_sided_lighting.vert";
                        fragFileName = "Shaders/two_sided_lighting.frag";
                        break;
                }

                _shaders[i] = new ShaderProgram();
                if(!_shaders[i]->InstallShaders(vertFileName, fragFileName)){
                    throw Exception("Could not install a shader");
                }
                _shaders[i]->Enable();
                switch(i){
                    case 2:
                        _shaders[i]->SetUniformVariable4f("default_outline_color", _r, _g, _b, 1.0f);
                        break;
                    case 1:
                        _shaders[i]->SetUniformVariable1f("smoothing", _smoothing);
                        _shaders[i]->SetUniformVariable1f("shading", _shading);
                        _shaders[i]->SetUniformVariable1f("scale_factor", _scaling);
                        break;
                }
                _shaders[i]->Disable();
            }

            _composite_arc = new FOAHCompositeArc(1, 5);
            _composite_arc->InsertNewArc();
            _composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::RIGHT);
            _composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::LEFT);

            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

            glEnable(GL_DEPTH_TEST);
            cout << "initialize done" << endl;

        }
        catch (Exception &e)
        {
            cout << e << endl;
        }

    }    

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            glDisable(GL_LIGHTING);
            _composite_arc->RenderAllArcs(0, GL_LINE_STRIP);
            _composite_arc->RenderAllArcData(GL_LINE_STRIP);
            glPointSize(10.0f);
            _composite_arc->RenderAllArcData(GL_POINTS);
//            _composite_arc->RenderSelectedArc(0, 0, GL_LINE_STRIP);
            glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(w) / static_cast<double>(h);

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        update();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    GLWidget::~GLWidget(){
        delete _dl;
        _dl = nullptr;
        delete _composite_arc;
        _composite_arc = nullptr;
    }

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            update();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            update();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            update();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            update();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            update();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            update();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            update();
        }
    }

    void GLWidget::set_show_first_der(bool value)
    {
        _show_first_der = value;

        update();
    }

    void GLWidget::set_show_second_der(bool value)
    {
        _show_second_der = value;

        update();
    }

    void GLWidget::update_selected_point_x(double new_value){
        update_selected_surface_point_x(new_value);
    }

    void GLWidget::update_selected_point_y(double new_value){
        update_selected_curve_point_y(new_value);
    }

    void GLWidget::update_selected_point_z(double new_value){
        update_selected_curve_point_z(new_value);
    }

    void GLWidget::update_selected_surface_point_x(double new_value){
//        int x = _selected_point / 4;
//        int y = _selected_point % 4;

//        _surface_cpoints(x, y)[0] = new_value;
//        update();
    }

    void GLWidget::update_selected_surface_point_y(double new_value){
//        int x = _selected_point / 4;
//        int y = _selected_point % 4;

//        _surface_cpoints(x, y)[1] = new_value;
//        update();
    }

    void GLWidget::update_selected_surface_point_z(double new_value){
//        int x = _selected_point / 4;
//        int y = _selected_point % 4;

//        _surface_cpoints(x, y)[2] = new_value;
//        update();
    }

    void GLWidget::update_selected_curve_point_x(double new_value){
    }

    void GLWidget::update_selected_curve_point_y(double new_value){
    }

    void GLWidget::update_selected_curve_point_z(double new_value){
    }


    GLvoid GLWidget::set_selected_shader(int index){
        if(index < 0 || index >= _shaders.GetColumnCount()){
            return;
        }

        _selected_shader = index;
        update();
    }

    GLvoid GLWidget::updateUniformVariables(){
        _shaders[_selected_shader]->Enable();
        switch(_selected_shader){
            case 2:
                _shaders[_selected_shader]->SetUniformVariable4f("default_outline_color", _r, _g, _b, 1.0f);
                break;
            case 1:
                _shaders[_selected_shader]->SetUniformVariable1f("smoothing", _smoothing);
                _shaders[_selected_shader]->SetUniformVariable1f("shading", _shading);
                _shaders[_selected_shader]->SetUniformVariable1f("scale_factor", _scaling);
                break;
        }
        _shaders[_selected_shader]->Disable();
    }

    GLvoid GLWidget::set_selected_r(GLdouble value){
        _r = value;
        updateUniformVariables();
        update();
    }

    GLvoid GLWidget::set_selected_g(GLdouble value){
        _g = value;
        updateUniformVariables();
        update();
    }

    GLvoid GLWidget::set_selected_b(GLdouble value){
        _b = value;
        updateUniformVariables();
        update();
    }

    GLvoid GLWidget::set_selected_smoothing(GLdouble value){
        _smoothing = value;
        updateUniformVariables();
        update();
    }

    GLvoid GLWidget::set_selected_scaling(GLdouble value){
        _scaling = value;
        updateUniformVariables();
        update();
    }

    GLvoid GLWidget::set_selected_shading(GLdouble value){
        _shading = value;
        updateUniformVariables();
        update();
    }
}
