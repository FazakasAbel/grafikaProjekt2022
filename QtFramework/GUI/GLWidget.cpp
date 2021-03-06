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


        if(APPL){
            _text = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_14.jpg").mirrored());
            _text->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _text->setMagnificationFilter(QOpenGLTexture::Linear);
            _textures[0] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_01.jpg").mirrored());
            _textures[0]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[0]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[1] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_02.jpg"));
            _textures[1]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[1]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[2] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_02.jpg"));
            _textures[2]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[2]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[3] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_05.jpg"));
            _textures[3]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[3]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[4] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_05.jpg"));
            _textures[4]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[4]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[5] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_06.jpg"));
            _textures[5]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[5]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[6] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_07.jpg"));
            _textures[6]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[6]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[7] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_08.jpg"));
            _textures[7]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[7]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[8] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_09.jpg"));
            _textures[8]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[8]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[9] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_10.jpg"));
            _textures[9]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[9]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[10] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_11.jpg"));
            _textures[10]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[10]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[11] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_12.jpg"));
            _textures[11]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[11]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[12] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_13.jpg"));
            _textures[12]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[12]->setMagnificationFilter(QOpenGLTexture::Linear);

            _textures[13] = new QOpenGLTexture(QImage("/Users/andorgere/Documents/Egyetem/Grafika/build-QtFramework-Qt_6_2_3_for_macOS-Debug/Textures/texture_14.jpg"));
            _textures[13]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            _textures[13]->setMagnificationFilter(QOpenGLTexture::Linear);
        } else {
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
        }

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

            HCoordinate3    direction2   (0.0, 0.0, 1.0, 1.0);
            Color4          ambient2     (0.4f, 0.4f, 0.4f, 1.0f);
            Color4          diffuse2     (0.8f, 0.8f, 0.8f, 1.0f);
            Color4          specular2    (1.0, 1.0, 1.0, 1.0);
            GLfloat         constant_attenuation2(1.0);
            GLfloat         linear_attenuation2(0.0);
            GLfloat         quadratic_attenuation2(0.0);
            HCoordinate3    spot_direction2(0.0, 0.0, -1.0);

            _pl = new (nothrow) PointLight(GL_LIGHT1, direction2, ambient2, diffuse2, specular2, constant_attenuation2, linear_attenuation2, quadratic_attenuation2);

            if(!_pl){
               throw Exception("Could not create the point light object!");
            }

            HCoordinate3 direction3(0.0f, 0.0f, 1.0f, 0.1f);
            Color4 ambient3(0.4f, 0.4f, 0.4f, 1.0f);
            Color4 diffuse3(0.8f, 0.8f, 0.8f, 1.0f);
            Color4 specular3(1.0, 1.0, 1.0, 1.0);
            GLfloat constant_attenuation3(0.1f);
            GLfloat linear_attenuation3(0.1f);
            GLfloat quadratic_attenuation3(0.01f);
            HCoordinate3 spot_direction3(0.0f, 0.0f, -1.0f, 1.0f);
            GLfloat spot_cutoff3(4.5f);
            GLfloat spot_exponent3(2.0f);

            _sl = new (nothrow) Spotlight(GL_LIGHT2, direction3, ambient3, diffuse3, specular3, constant_attenuation3, linear_attenuation3, quadratic_attenuation3, spot_direction3, spot_cutoff3, spot_exponent3);

            if(!_sl){
               throw Exception("Could not create the spotlight object!");
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
            //_potykany.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW);

            _composite_arc = new FOAHCompositeArc(1, 100);
            _composite_arc->InsertNewArc();
            //_composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::RIGHT);
            //_composite_arc->ContinueExisitingArc(0, FOAHCompositeArc::LEFT);

            _composite_patch = new FOAHCompositePatch3(1, 100);
            _composite_patch->InsertNewPatch();
            _composite_patch->pushPatch(0, 1);
            _composite_patch->pushPatch(0, 0);
            _composite_patch->pushPatch(0, 0);
            _composite_patch->pushPatch(0, 0);
            _composite_patch->pushPatch(0, 0);
            _composite_patch->InsertNewPatch();
            _composite_patch->MergeExistingPatches(0, FOAHCompositePatch3::N, 1, FOAHCompositePatch3::S);

            _composite_patch->InsertNewPatch();
            _composite_patch->pushPatch(2, 2);
            _composite_patch->pushPatch(2, 2);
            _composite_patch->pushPatch(2, 2);
            _composite_patch->pushPatch(2, 2);
            _composite_patch->pushPatch(2, 1);
            _composite_patch->pushPatch(2, 1);
            _composite_patch->MergeExistingPatches(2, FOAHCompositePatch3::E, 1, FOAHCompositePatch3::W);

            _composite_patch->setMaterial(0,0);
            _composite_patch->setMaterial(1,1);
            _composite_patch->setMaterial(2,3);
            _composite_patch->setTexture(0,0);
            _composite_patch->setTexture(1,1);
            _composite_patch->setTexture(2,3);
            _composite_patch->setShader(0,0);
            _composite_patch->setShader(1,1);
            _composite_patch->setShader(2,3);
//            _composite_patch->JoinExistingPatches(0, FOAHCompositePatch3::N, 1, FOAHCompositePatch3::S);
//            _composite_patch->JoinExistingPatches(2, FOAHCompositePatch3::E, 1, FOAHCompositePatch3::W);

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
        emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y)[0]);
        emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y)[1]);
        emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y)[2]);

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
                if(_show_first_der) {
                    std::cout<<"hello";
                    _composite_arc->RenderAllArcs(1,GL_LINES);
                }
                if(_show_second_der) {
                    _composite_arc->RenderAllArcs(2,GL_LINES);
                }
                glPointSize(10.0f);
                _composite_arc->RenderAllArcData(GL_POINTS);
    //          _composite_arc->RenderSelectedArc(0, 0, GL_LINE_STRIP);
//                if(_show_first_der) {
//                    _composite_arc->RenderSelectedArcs(1,0,GL_LINES);
//                }
//                if(_show_second_der) {
//                    _composite_arc->RenderSelectedArcs(2,0,GL_LINES);
//                }
                glEnable(GL_LIGHTING);
            // Patch
            } else {
                glDisable(GL_LIGHTING);
                switch(_selected_light){
                    case 0:
                        _dl->Enable();
                    break;
                    case 1:
                        _pl->Enable();
                    break;
                    case 2:
                        _sl->Enable();
                    break;
                }
                /*
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

                }
*/
                //content
                // _composite_patch->RenderAllPatches(0, GL_TRIANGLES);
            if(!_enable_material) {
                glColor3f(patch_r, patch_g, patch_b);
            }
             for(GLuint i=0; i< _composite_patch->getPatchCount(); i++) {
                 if(_enable_shader) {
                     _shaders[_composite_patch->getShader(i)]->Enable();
                 }
                 if(_enable_texture) {
                        glEnable(GL_TEXTURE_2D);
                       // glEnable(GL_LIGHT0);
                        //glEnable(GL_NORMALIZE);
                        _textures[_composite_patch->getTexture(i)]->bind();
                    }
                 if(_enable_material){
                 glEnable(GL_LIGHTING);
                 switch(_composite_patch->getMaterial(i)){
                         case 0:
                             MatFBBrass.Apply();
                             break;
                         case 1:
                             MatFBEmerald.Apply();
                             break;
                         case 2:
                             MatFBGold.Apply();
                             break;
                         case 3:
                             MatFBPearl.Apply();
                             break;
                         case 4:
                             MatFBRuby.Apply();
                             break;
                         case 5:
                             MatFBSilver.Apply();
                             break;
                         case 6:
                             MatFBTurquoise.Apply();
                             break;
                     }
                 }
                 _composite_patch->RenderSelectedPatchWithoutData(i, 0, GL_TRIANGLES);
                 if(_enable_shader) {
                     _shaders[_composite_patch->getShader(i)]->Disable();
                 }
             }
                _composite_patch->RenderAllPatchData(GL_LINE_STRIP);
                glColor3f(0.0f, 1.0f, 0.0f);
                DCoordinate3 selected_point = _composite_patch->getPoint(_selected_patch, _selected_patch_point_x, _selected_patch_point_y);
                glDisable(GL_LIGHTING);
                glBegin(GL_POINTS);
                    glPointSize(100.0f);
                        glVertex3f(selected_point.x(), selected_point.y(), selected_point.z());
                    glPointSize(1.0f);
                glEnd();
//                glEnable(GL_LIGHTING);

                glColor3f(0.0f, 0.0f, 1.0f);
                glPointSize(10.0f);
                _composite_patch->RenderAllPatchData(GL_POINTS);
                glColor3f(0.0f, 1.0f, 0.0f);
                if(_show_first_der_patch) {
                    _composite_patch->RenderIsoparametricCurves(1, GL_LINES);
                }
                if(_show_second_der_patch) {
                    _composite_patch->RenderIsoparametricCurves(2, GL_LINES);
                }

                if(_enable_texture) {
                    _textures[_selected_texture]->release();
                    glDisable(GL_TEXTURE_2D);
                   // glDisable(GL_NORMALIZE);
                     //glDisable(GL_LIGHT0);
                }
                switch(_selected_light){
                    case 0:
                        _dl->Disable();
                    break;
                    case 1:
                        _pl->Disable();
                    break;
                    case 2:
                        _sl->Disable();
                    break;
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
        delete _pl;
        _pl = nullptr;
        delete _sl;
        _sl = nullptr;
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
    void GLWidget::set_show_first_der_patch(bool value)
    {
        _show_first_der_patch = value;

        update();
    }
    void GLWidget::set_show_second_der(bool value)
    {
        _show_second_der = value;

        update();
    }
    void GLWidget::set_show_second_der_patch(bool value)
    {
        _show_second_der_patch = value;

        update();
    }
    void GLWidget::set_selected_arc(int index){
        if(index != _selected_arc && _selected_arc >= 0 && _selected_arc <= _composite_arc->getArcCount()-1 && index<=_composite_arc->getArcCount()-1){
            cout<<"ifben"<<endl;
            _selected_arc = index;
            emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
            emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
            emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);
            update();
        }

    }
    void GLWidget::set_selected_patch(int index) {
        if(index != _selected_patch && _selected_patch >= 0 && _selected_patch <= _composite_patch->getPatchCount()-1 && index<=_composite_patch->getPatchCount()-1){
            cout<<"ifben"<<endl;
            _selected_patch = index;
            //TODO allitani az indexeket
            emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[0]);
            emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[1]);
            emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[2]);
            emit set_texture_signal_patch(_composite_patch->getTexture(_selected_patch));
            emit set_material_signal_patch(_composite_patch->getMaterial(_selected_patch));
            emit set_shader_signal_patch(_composite_patch->getShader(_selected_patch));
            update();
        }
    }
    void GLWidget::set_selected_light(int value) {
        _selected_light = value;
        update();
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
    void GLWidget::set_selected_patch_1(int index) {
        if(index!=_selected_patch_1) {
            _selected_patch_1 = index;
        }
        update();
    }
    void GLWidget::set_selected_patch_2(int index) {
        if(index!=_selected_patch_2) {
            _selected_patch_2 = index;
        }
        update();
    }
    void GLWidget::set_direction_patch_1(int dir) {
        if(_selected_direction_patch_1!=dir) {
            _selected_direction_patch_1 = dir;
        }
        update();
    }
    void GLWidget::set_direction_patch_2(int dir) {
        if(_selected_direction_patch_2!=dir) {
            _selected_direction_patch_2 = dir;
        }
        update();
    }
    void GLWidget::call_insert(){
        _composite_arc->InsertNewArc();
        update();
    }
    void GLWidget::call_insert_patch() {
        _composite_patch->InsertNewPatch();
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
    void GLWidget::call_extend_patch() {
        if(_selected_patch_1>=0 && _selected_patch_1<=_composite_patch->getPatchCount()) {
            switch(_selected_direction_patch_1) {
            case 0: {
                _composite_patch->ContinueExistingPatch(_selected_patch_1,FOAHCompositePatch3::N);
                break;
            }
            case 1: {
                _composite_patch->ContinueExistingPatch(_selected_patch_1,FOAHCompositePatch3::E);
                break;
            }
            case 2: {
                _composite_patch->ContinueExistingPatch(_selected_patch_1,FOAHCompositePatch3::S);
                break;
            }
            case 3: {
                _composite_patch->ContinueExistingPatch(_selected_patch_1,FOAHCompositePatch3::W);
                break;
            }
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
    void GLWidget::call_join_patch() {
        if((_selected_patch_1==_selected_patch_2) || _selected_patch_1<0 || _selected_patch_2<0 || _selected_patch_1>_composite_patch->getPatchCount() || _selected_patch_2> _composite_patch->getPatchCount()) {
            return;
        } else {
            FOAHCompositePatch3::Direction dir_patch_1, dir_patch_2;
            switch(_selected_direction_patch_1) {
            case 0: {
                dir_patch_1 = FOAHCompositePatch3::N;
                break;
            }
            case 1: {
                dir_patch_1 = FOAHCompositePatch3::E;
                break;
            }
            case 2: {
                dir_patch_1 = FOAHCompositePatch3::S;
                break;
            }
            case 3: {
                dir_patch_1 = FOAHCompositePatch3::W;
                break;
            }
            }
            switch(_selected_direction_patch_2) {
            case 0: {
                dir_patch_2 = FOAHCompositePatch3::N;
                break;
            }
            case 1: {
                dir_patch_2 = FOAHCompositePatch3::E;
                break;
            }
            case 2: {
                dir_patch_2 = FOAHCompositePatch3::S;
                break;
            }
            case 3: {
                dir_patch_2 = FOAHCompositePatch3::W;
                break;
            }
            }
            GLuint _selected_patch_1_gl = _selected_patch_1;
            GLuint _selected_patch_2_gl = _selected_patch_2;
            _composite_patch->JoinExistingPatches(_selected_patch_1_gl,dir_patch_1,_selected_patch_2_gl,dir_patch_2);
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
    void GLWidget::call_merge_patch() {
        if((_selected_patch_1==_selected_patch_2) || _selected_patch_1<0 || _selected_patch_2<0 || _selected_patch_1>_composite_patch->getPatchCount() || _selected_patch_2> _composite_patch->getPatchCount()) {
            return;
        } else {
            FOAHCompositePatch3::Direction dir_patch_1, dir_patch_2;
            switch(_selected_direction_patch_1) {
            case 0: {
                dir_patch_1 = FOAHCompositePatch3::N;
                break;
            }
            case 1: {
                dir_patch_1 = FOAHCompositePatch3::E;
                break;
            }
            case 2: {
                dir_patch_1 = FOAHCompositePatch3::S;
                break;
            }
            case 3: {
                dir_patch_1 = FOAHCompositePatch3::W;
                break;
            }
            }
            switch(_selected_direction_patch_2) {
            case 0: {
                dir_patch_2 = FOAHCompositePatch3::N;
                break;
            }
            case 1: {
                dir_patch_2 = FOAHCompositePatch3::E;
                break;
            }
            case 2: {
                dir_patch_2 = FOAHCompositePatch3::S;
                break;
            }
            case 3: {
                dir_patch_2 = FOAHCompositePatch3::W;
                break;
            }
            }
            GLuint _selected_patch_1_gl = _selected_patch_1;
            GLuint _selected_patch_2_gl = _selected_patch_2;
            _composite_patch->MergeExistingPatches(_selected_patch_1_gl,dir_patch_1,_selected_patch_2_gl,dir_patch_2);
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
    void GLWidget::set_selected_point_patch_x(int index) {
        if(index>= 0 && index<4) {
            _selected_patch_point_x = index;
        }

        //todo javitani
        emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[0]);
        emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[1]);
        emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[2]);

        glDisable(GL_LIGHTING);

        glBegin(GL_POINTS);
          glPointSize(250.0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f((_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[0],(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[1],(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[2]);
        glEnd();
        glPointSize(1.0);
        glEnable(GL_LIGHTING);
        update();


    }
    void GLWidget::set_selected_point_patch_y(int index) {
        if(index>=0 && index<4) {
            _selected_patch_point_y = index;
        }
        //todo javitani

        emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[0]);
        emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[1]);
        emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[2]);

        glDisable(GL_LIGHTING);

        glBegin(GL_POINTS);
        glPointSize(250.0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f((_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[0],(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[1],(_composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y))[2]);
        glEnd();
        glPointSize(1.0);
        glEnable(GL_LIGHTING);
        update();


    }
    void GLWidget::pushArc(){
        _composite_arc->pushArc(_selected_arc, _direction);
        emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
        emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
        emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);
        update();
    }

    void GLWidget::pullArc(){
        _composite_arc->pullArc(_selected_arc, _direction);
        emit set_x_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[0]);
        emit set_y_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[1]);
        emit set_z_signal(_composite_arc->getPoint(_selected_arc, _selected_arc_point)[2]);
        update();
    }

    void GLWidget::pushPatch() {
        _composite_patch->pushPatch(_selected_patch, _direction_patch);

        emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[0]);
        emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[1]);
        emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[2]);

        update();
    }
    void GLWidget::pullPatch() {
        _composite_patch->pullPatch(_selected_patch, _direction_patch);

        emit set_x_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[0]);
        emit set_y_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[1]);
        emit set_z_signal_patch(_composite_patch->getPoint(_selected_patch, _selected_patch_point_x,_selected_patch_point_y)[2]);

        update();
    }

    void GLWidget::set_selected_direction(int value){
        if(value >= 0 && value <= 3){
            _direction = value;
        }
    }
    void GLWidget::set_selected_direction_patch(int value) {
        if(value >= 0 && value <= 3){
            _direction_patch = value;
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
        _composite_patch->setShader(_selected_patch, _selected_shader);
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
         _composite_patch->setMaterial(_selected_patch, _selected_material);
        update();
    }
    void GLWidget::set_material_enable(bool value) {
        if(_enable_material!=value) {
            _enable_material=value;
            _composite_patch->setEnableMaterial(_enable_material);
            update();
        }
    }

    void GLWidget::set_texture_index(int value) {
        _selected_texture = value;
         _composite_patch->setTexture(_selected_patch, _selected_texture);
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
    void GLWidget::update_selected_point_patch_x(double newValue) {
        DCoordinate3 temp = _composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y);
        DCoordinate3 *temp2 = new DCoordinate3(newValue,temp.y(),temp.z());
        _composite_patch->setPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y,*temp2);
        update();
    }
    void GLWidget::update_selected_point_patch_y(double newValue) {
        DCoordinate3 temp = _composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y);
        DCoordinate3 *temp2 = new DCoordinate3(temp.x(),newValue,temp.z());
        _composite_patch->setPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y,*temp2);
        update();
    }
    void GLWidget::update_selected_point_patch_z(double newValue) {
        DCoordinate3 temp = _composite_patch->getPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y);
        DCoordinate3 *temp2 = new DCoordinate3(temp.x(),temp.y(),newValue);
        _composite_patch->setPoint(_selected_patch,_selected_patch_point_x,_selected_patch_point_y,*temp2);
        update();
    }
}
