#include "GLWidget.h"

#if !defined(__APPLE__)
#define APPL 0
#include <GL/glu.h>
#else
#define APPL 1
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
        _materials.ResizeColumns(7);
        _materials[0] = MatFBBrass;
        _materials[1] = MatFBEmerald;
        _materials[2] = MatFBGold;
        _materials[3] = MatFBPearl;
        _materials[4] = MatFBRuby;
        _materials[5] = MatFBSilver;
        _materials[6] = MatFBTurquoise;


        _text = new QOpenGLTexture(QImage("Textures/texture_11.jpg").mirrored());
        _text->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _text->setMagnificationFilter(QOpenGLTexture::Linear);
        _textures[0] = new QOpenGLTexture(QImage("Textures/texture_01.jpg").mirrored());
        _textures[0]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[0]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[1] = new QOpenGLTexture(QImage("Textures/texture_02.jpg"));
        _textures[1]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[1]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[2] = new QOpenGLTexture(QImage("Textures/texture_03.jpg"));
        _textures[2]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[2]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[3] = new QOpenGLTexture(QImage("Textures/texture_04.jpg"));
        _textures[3]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[3]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[4] = new QOpenGLTexture(QImage("Textures/texture_05.jpg"));
        _textures[4]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[4]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[5] = new QOpenGLTexture(QImage("Textures/texture_06.jpg"));
        _textures[5]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[5]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[6] = new QOpenGLTexture(QImage("Textures/texture_07.jpg"));
        _textures[6]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[6]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[7] = new QOpenGLTexture(QImage("Textures/texture_08.jpg"));
        _textures[7]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[7]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[8] = new QOpenGLTexture(QImage("Textures/texture_09.jpg"));
        _textures[8]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[8]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[9] = new QOpenGLTexture(QImage("Textures/texture_10.jpg"));
        _textures[9]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[9]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[10] = new QOpenGLTexture(QImage("Textures/texture_11.jpg"));
        _textures[10]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[10]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[11] = new QOpenGLTexture(QImage("Textures/texture_12.jpg"));
        _textures[11]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[11]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[12] = new QOpenGLTexture(QImage("Textures/texture_13.jpg"));
        _textures[12]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[12]->setMagnificationFilter(QOpenGLTexture::Linear);

        _textures[13] = new QOpenGLTexture(QImage("Textures/texture_14.jpg"));
        _textures[13]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        _textures[13]->setMagnificationFilter(QOpenGLTexture::Linear);

        //_potykany.LoadFromOFF("/Users/andorgere/Documents/Egyetem/Grafika/Models/Flying objects/Airplanes/airplane_01.off",GL_TRUE);
        //_potykany.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);

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
                        if(APPL) {
                            vertFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/directional_light.vert";
                            fragFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/directional_light.frag";
                        } else {
                            vertFileName = "Shaders/directional_light.vert";
                            fragFileName = "Shaders/directional_light.frag";
                        }
                        break;
                    case 1:
                        if(APPL){
                            vertFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/reflection_lines.vert";
                            fragFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/reflection_lines.frag";
                        } else {
                            vertFileName = "Shaders/reflection_lines.vert";
                            fragFileName = "Shaders/reflection_lines.frag";
                        }
                        break;
                    case 2:
                        if(APPL){
                            vertFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/toon.vert";
                            fragFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/toon.frag";
                        } else {
                            vertFileName = "Shaders/toon.vert";
                            fragFileName = "Shaders/toon.frag";
                        }
                        break;
                    case 3:
                        if(APPL){
                            vertFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/two_sided_lighting.vert";
                            fragFileName = "/Users/andorgere/Documents/Egyetem/Grafika/Shaders/two_sided_lighting.frag";
                        } else {
                            vertFileName = "Shaders/two_sided_lighting.vert";
                            fragFileName = "Shaders/two_sided_lighting.frag";
                        }
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
            if(APPL){
                _potykany.LoadFromOFF("/Users/andorgere/Documents/Egyetem/Grafika/Models/Characters/mouse.off",GL_TRUE);
            } else {
                _potykany.LoadFromOFF("Models/Characters/mouse.off",GL_TRUE);
            }
            _potykany.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);

            _composite_arc = new FOAHCompositeArc(1, 100);
            _composite_arc->InsertNewArc();
            //_composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::RIGHT);
            //_composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::LEFT);

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

        emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
        emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
        emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);

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
            // Arc
            if(_selected_page == 0) {
                glDisable(GL_LIGHTING);
                _composite_arc->RenderAllArcs(0, GL_LINE_STRIP);
                _composite_arc->RenderAllArcData(GL_LINE_STRIP);
                glPointSize(10.0f);
                _composite_arc->RenderAllArcData(GL_POINTS);
    //          _composite_arc->RenderSelectedArc(0, 0, GL_LINE_STRIP);
                glEnable(GL_LIGHTING);
            // Patch
            } else {
                glDisable(GL_LIGHTING);
                _dl->Enable();
                if(_enable_shader) {
                    _shaders[_selected_shader]->Enable();
                }
                if(_enable_material) {
                    glEnable(GL_LIGHTING);
                    _materials[_selected_material].Apply();
                } else {

                    glColor3f(patch_r, patch_g, patch_b);
                }
                if(_enable_texture) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_LIGHT0);
                    glEnable(GL_NORMALIZE);
                    _textures[_selected_texture]->bind();
                    _text->bind();

                }

                //content
                _potykany.Render();

                if(_enable_shader) {
                    _shaders[_selected_shader]->Disable();
                }
                if(_enable_texture) {
                    _textures[_selected_texture]->release();
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_NORMALIZE);
                }
            }
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

    void GLWidget::set_selected_arc(int index){
        if(index != _selected_arc && index >= 0 && index < _composite_arc->getArcCount()-1){
            cout<<"ifben"<<endl;
            _selected_arc = index;
            emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
            emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
            emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);
            update();
        }

    }
    void GLWidget::set_selected_curve_1(int index){
        if(index != _selected_curve_1){
            _selected_curve_1 = index;
        }
        update();
    }
    void GLWidget::set_selected_curve_2(int index){
        if(index != _selected_curve_2){
            _selected_curve_2 = index;
        }
        update();
    }
    void GLWidget::set_direction_curve_1(int dir){
        if(_selected_curve_1_direction != dir){
            _selected_curve_1_direction = dir;
        }
        update();
    }
    void GLWidget::set_direction_curve_2(int dir){
        if(_selected_curve_2_direction != dir){
            _selected_curve_2_direction = dir;
        }
        update();
    }
    void GLWidget::call_insert(){
        _composite_arc->InsertNewArc();
        update();
    }
    void GLWidget::call_extend(){
        if(_selected_curve_1 >= 0 && _selected_curve_1 <= _composite_arc->getArcCount()){
            if(_selected_curve_1_direction == 0){
                _composite_arc->ContinueExisitingArc(_selected_curve_1, FOAHCompositeArc::LEFT);
            } else {
                _composite_arc->ContinueExisitingArc(_selected_curve_1, FOAHCompositeArc::RIGHT);
            }
            update();
        }
    }
    void GLWidget::call_join(){
        if((_selected_curve_1 == _selected_curve_2) || _selected_curve_1 < 0 || _selected_curve_2 < 0 || _selected_curve_1 >_composite_arc->getArcCount() || _selected_curve_1 > _composite_arc->getArcCount()){
            return;
        } else {
            FOAHCompositeArc::Direction dir_curve_1, dir_curve_2;
            if(_selected_curve_1_direction == 0){
                dir_curve_1 = FOAHCompositeArc::LEFT;
            } else {
                dir_curve_1 = FOAHCompositeArc::RIGHT;
            }
            if(_selected_curve_2_direction == 0){
                dir_curve_2 = FOAHCompositeArc::LEFT;
            } else {
                dir_curve_2 = FOAHCompositeArc::RIGHT;
            }
            GLuint _selected_curve_1_gl = _selected_curve_1;
            GLuint _selected_curve_2_gl = _selected_curve_2;
            _composite_arc->JoinExistingArcs(_selected_curve_1_gl, dir_curve_1, _selected_curve_2_gl, dir_curve_2);
            update();
        }
    }
    void GLWidget::call_merge() {
        if((_selected_curve_1 == _selected_curve_2) || _selected_curve_1 < 0 || _selected_curve_2 < 0 || _selected_curve_1 >_composite_arc->getArcCount() || _selected_curve_1 > _composite_arc->getArcCount()){
            return;
        } else {
            FOAHCompositeArc::Direction dir_curve_1, dir_curve_2;
            if(_selected_curve_1_direction == 0){
                dir_curve_1 = FOAHCompositeArc::LEFT;
            } else {
                dir_curve_1 = FOAHCompositeArc::RIGHT;
            }
            if(_selected_curve_2_direction == 0){
                dir_curve_2 = FOAHCompositeArc::LEFT;
            } else {
                dir_curve_2 = FOAHCompositeArc::RIGHT;
            }
            GLuint _selected_curve_1_gl = _selected_curve_1;
            GLuint _selected_curve_2_gl = _selected_curve_2;
            _composite_arc->MergeExistingArcs(_selected_curve_1_gl, dir_curve_1, _selected_curve_2_gl, dir_curve_2);
            update();
        }
    }
    void GLWidget::set_selected_point(int index){
        if(index >= 0 && index < 4){
            _selected_arc_point = index;
        }

        emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
        emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
        emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);
        update();
    }

    void GLWidget::pushArc(){
        _composite_arc->pushArc(_selected_arc, _direction);

        update();
    }

    void GLWidget::pullArc(){
        _composite_arc->pullArc(_selected_arc, _direction);

        update();
    }

    void GLWidget::set_selected_direction(int value){
        if(value >= 0 && value <= 3){
            _direction = value;
        }
    }

    void GLWidget::update_selected_point_x(double new_value){
        _composite_arc->setPoint(_selected_arc, _selected_arc_point, 0, new_value);
        update();
    }

    void GLWidget::update_selected_point_y(double new_value){
        _composite_arc->setPoint(_selected_arc, _selected_arc_point, 1, new_value);
        update();
    }

    void GLWidget::update_selected_point_z(double new_value){
        _composite_arc->setPoint(_selected_arc, _selected_arc_point, 2, new_value);
        update();
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

    void GLWidget::set_shader_enable(bool value) {
        if(_enable_shader!=value) {
            _enable_shader = value;
            update();
        }
    }

    void GLWidget::set_material_index(int value) {
        _selected_material = value;
        update();
    }
    void GLWidget::set_material_enable(bool value) {
        if(_enable_material!=value) {
            _enable_material=value;
            update();
        }
    }

    void GLWidget::set_texture_index(int value) {
        _selected_texture = value;
        update();
    }

    void GLWidget::set_texture_enable(bool value) {
        if(_enable_texture!=value) {
            _enable_texture = value;
            update();
        }
    }

    void GLWidget::set_selected_page(int value) {
        _selected_page = value;
        update();
    }
    void GLWidget::set_patch_color_r(GLdouble value){
        patch_r = value;
        update();
    }
    void GLWidget::set_patch_color_g(GLdouble value){
        patch_g = value;
        update();
    }
    void GLWidget::set_patch_color_b(GLdouble value){
        patch_b = value;
        update();
    }
}
