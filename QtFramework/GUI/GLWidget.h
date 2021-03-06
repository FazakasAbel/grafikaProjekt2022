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
#include "../Core/FOAHCompositePatch.h"

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
        int                             _selected_arc = 0;
        int                             _selected_arc_point = 0;
        int                             _direction = 0;

        FOAHCompositePatch3* 			_composite_patch;
        RowMatrix<GenericCurve3*>		*_u_lines, *_v_lines;

        DirectionalLight *_dl = nullptr;
        PointLight *_pl = nullptr;
        Spotlight *_sl = nullptr;

        RowMatrix<ShaderProgram*>                _shaders;
        GLuint                                   _selected_shader = 0;
        bool                                  _enable_shader = false;
        GLdouble                                 _r = 0, _g = 0, _b = 0, _scaling = 0, _smoothing = 0, _shading = 0;
        RowMatrix<Material>                     _materials;
        GLuint                                  _selected_material = 0;
        bool                                    _enable_material = false;
        QOpenGLTexture *_textures[14];
        QOpenGLTexture *_text;
        GLuint                                  _selected_texture = 0;
        bool                                  _enable_texture = false;
        bool                                  _enable_color = false;
        int _selected_page = 0;
        int _selected_light = 0;

        TriangulatedMesh3                       _potykany;
        GLvoid    updateUniformVariables();
        double patch_r = 255.0;
        double patch_g = 0.0;
        double patch_b = 0.0;
        // Curve merge, join ... GUI
        int                             _selected_curve_1 = 0;
        int                             _selected_curve_2 = 0;
        int                             _selected_curve_1_direction = 0;
        int                             _selected_curve_2_direction = 0;

        //patch
        int                             _selected_patch = 0;
        int                             _direction_patch = 0;
        int                             _selected_patch_point_x = 0;
        int                             _selected_patch_point_y = 0;

        int                             _selected_patch_1 = 0;
        int                             _selected_patch_2 = 0;
        int                             _selected_direction_patch_1 = 0;
        int                             _selected_direction_patch_2 = 0;
        GLboolean                       _show_first_der_patch = false;
        GLboolean                       _show_second_der_patch = false;

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

        void set_selected_point(int);

        void set_selected_direction(int);

        void pushArc();
        void pullArc();

        void set_selected_shader(int);

        void set_selected_r(double);
        void set_selected_g(double);
        void set_selected_b(double);

        void set_selected_scaling(double);
        void set_selected_smoothing(double);
        void set_selected_shading(double);

        void set_shader_enable(bool);

        void set_material_index(int);
        void set_material_enable(bool);

        void set_texture_index(int);
        void set_texture_enable(bool);

        void set_selected_page(int);
        void set_selected_light(int);
        void set_patch_color_r(double);
        void set_patch_color_g(double);
        void set_patch_color_b(double);
        // Merge, join and extend
        void set_selected_arc(int);
        void set_selected_curve_1(int);
        void set_selected_curve_2(int);
        void set_direction_curve_1(int);
        void set_direction_curve_2(int);
        void call_join();
        void call_insert();
        void call_merge();
        void call_extend();

        //patch
        void call_insert_patch();
        void set_selected_patch(int);
        void set_selected_direction_patch(int);
        void set_selected_point_patch_x(int);
        void set_selected_point_patch_y(int);
        void set_selected_patch_1(int);
        void set_selected_patch_2(int);
        void set_direction_patch_1(int);
        void set_direction_patch_2(int);

        void pushPatch();
        void pullPatch();

        void call_join_patch();
        void call_extend_patch();
        void call_merge_patch();

        void set_show_second_der_patch(bool value);
        void set_show_first_der_patch(bool value);

        void update_selected_point_patch_x(double value);
        void update_selected_point_patch_y(double value);
        void update_selected_point_patch_z(double value);
    signals:
        void set_x_signal(double);
        void set_y_signal(double);
        void set_z_signal(double);
        void set_x_signal_patch(double);
        void set_y_signal_patch(double);
        void set_z_signal_patch(double);
        void set_texture_signal_patch(int);
        void set_material_signal_patch(int);
        void set_shader_signal_patch(int);
    };
}
