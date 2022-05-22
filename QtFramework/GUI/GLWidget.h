#pragma once

#include "../Core/Constants.h"
#include <QTimer>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include "../Core/Lights.h"
#include "../Core/Materials.h"
#include "../Parametric/ParametricCurves3.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Core/CyclicCurves3.h"
#include <QOpenGLTexture>
#include "../Core/FirstOrderAlgebraic-HyperbolicPatch3.h"
#include "../Core/FirstOrderAlgebraic-HyperbolicArc3.h"
#include "../Core/ShaderPrograms.h"
#include "../Core/FOAHCompositeArc.h"

namespace cagd
{
    class GLWidget: public QOpenGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations

        GLboolean                       _show_first_der = false;
        GLboolean                       _show_second_der = false;
        int                             _div_point_count = 200;
        GLenum                          _usage_flag;
        GLdouble                        _scale = 1;
        FOAHCompositeArc*               _composite_arc;
        FirstOrderAlgebraicHyperbolicArc3* arc;
        GenericCurve3*                  image;

        DirectionalLight *_dl = nullptr;

        TriangulatedMesh3 _mouse;

        RowMatrix<ShaderProgram*>                _shaders;
        GLuint                                   _selected_shader = 0;
        GLdouble                                 _r = 0, _g = 0, _b = 0, _scaling = 0, _smoothing = 0, _shading = 0;

        GLvoid    update_selected_curve_point_x(double);
        GLvoid    update_selected_curve_point_y(double);
        GLvoid    update_selected_curve_point_z(double);
        GLvoid    update_selected_surface_point_x(double);
        GLvoid    update_selected_surface_point_y(double);
        GLvoid    update_selected_surface_point_z(double);
        GLvoid    updateUniformVariables();


    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots

        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_show_second_der(bool value);
        void set_show_first_der(bool value);       

        void update_selected_point_x(double);
        void update_selected_point_y(double);
        void update_selected_point_z(double);
        void set_selected_shader(int);

        void set_selected_r(double);
        void set_selected_g(double);
        void set_selected_b(double);

        void set_selected_scaling(double);
        void set_selected_smoothing(double);
        void set_selected_shading(double);


    signals:

        void set_x_signal(double);
        void set_y_signal(double);
        void set_z_signal(double);

    };
}
