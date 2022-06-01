#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));


        connect(_side_widget->first_der, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_show_first_der(bool)));
        connect(_side_widget->second_der, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_show_second_der(bool)));

        connect(_side_widget->x_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(update_selected_point_x(double)));
        connect(_side_widget->y_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(update_selected_point_y(double)));
        connect(_side_widget->z_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(update_selected_point_z(double)));

        connect(_gl_widget, SIGNAL(set_x_signal(double)), _side_widget->x_selector, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(set_y_signal(double)), _side_widget->y_selector, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(set_z_signal(double)), _side_widget->z_selector, SLOT(setValue(double)));

        connect(_side_widget->r_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_r(double)));
        connect(_side_widget->g_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_g(double)));
        connect(_side_widget->b_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_b(double)));

        connect(_side_widget->smooth_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_smoothing(double)));
        connect(_side_widget->scaling_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_scaling(double)));
        connect(_side_widget->shade_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_shading(double)));

        connect(_side_widget->arc_selector, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_arc(int)));
        connect(_side_widget->arc_point_selector, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_point(int)));

        connect(_side_widget->plus, SIGNAL(pressed()), _gl_widget, SLOT(pushArc()));
        connect(_side_widget->minus, SIGNAL(pressed()), _gl_widget, SLOT(pullArc()));


        connect(_side_widget->direction_selector, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_selected_direction(int)));

        // Patch - Shaders, Textures, ...
        _side_widget->tabWidget->setCurrentIndex(0);
        connect(_side_widget->tabWidget, SIGNAL(currentChanged(int)), _gl_widget, SLOT(set_selected_page(int)));

        connect(_side_widget->checkBox_material, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_material_enable(bool)));
        connect(_side_widget->checkBox_texture, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_texture_enable(bool)));
        connect(_side_widget->checkBox_shader, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_shader_enable(bool)));
        connect(_side_widget->comboBox_material, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_material_index(int)));
        connect(_side_widget->comboBox_shader, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_selected_shader(int)));
        connect(_side_widget->comboBox_texture, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_texture_index(int)));
        connect(_side_widget->spinBox_r, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_patch_color_r(double)));
        connect(_side_widget->spinBox_g, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_patch_color_g(double)));
        connect(_side_widget->spinBox_b, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_patch_color_b(double)));
        // Join, merge and extend
        connect(_side_widget->comboBox_curve1_direction, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_curve_1(int)));
        connect(_side_widget->spinBox_curve1, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_curve_1(int)));
        connect(_side_widget->comboBox_curve2_direction, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_curve_2(int)));
        connect(_side_widget->spinBox_curve2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_curve_2(int)));
        connect(_side_widget->pushButton_join, SIGNAL(pressed()), _gl_widget, SLOT(call_join()));
        connect(_side_widget->pushButton_insert, SIGNAL(pressed()), _gl_widget, SLOT(call_insert()));
        connect(_side_widget->pushButton_extend, SIGNAL(pressed()), _gl_widget, SLOT(call_extend()));
        connect(_side_widget->pushButton_merge, SIGNAL(pressed()), _gl_widget, SLOT(call_merge()));

        //PATCH
        connect(_side_widget->patch_selector, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_patch(int)));
        connect(_side_widget->pushButton_insert_patch, SIGNAL(pressed()),_gl_widget, SLOT(call_insert_patch()));
        connect(_side_widget->direction_selector_patch, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_selected_direction_patch(int)));
        connect(_side_widget->plus_patch, SIGNAL(pressed()), _gl_widget, SLOT(pushPatch()));
        connect(_side_widget->minus_patch, SIGNAL(pressed()),_gl_widget, SLOT(pullPatch()));
        connect(_side_widget->patch_point_selector_x,SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_point_patch_x(int)));
        connect(_side_widget->patch_point_selector_y,SIGNAL(valueChanged(int)),_gl_widget, SLOT(set_selected_point_patch_y(int)));
        connect(_side_widget->x_selector_patch, SIGNAL(valueChanged(double)),_gl_widget, SLOT(update_selected_point_patch_x(double)));
        connect(_side_widget->y_selector_patch, SIGNAL(valueChanged(double)),_gl_widget, SLOT(update_selected_point_patch_y(double)));
        connect(_side_widget->z_selector_patch, SIGNAL(valueChanged(double)),_gl_widget, SLOT(update_selected_point_patch_z(double)));
        connect(_gl_widget, SIGNAL(set_x_signal_patch(double)), _side_widget->x_selector_patch, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(set_y_signal_patch(double)), _side_widget->y_selector_patch, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(set_z_signal_patch(double)), _side_widget->z_selector_patch, SLOT(setValue(double)));
        connect(_side_widget->spinBox_patch1, SIGNAL(valueChanged(int)),_gl_widget, SLOT(set_selected_patch_1(int)));
        connect(_side_widget->spinBox_patch2, SIGNAL(valueChanged(int)),_gl_widget, SLOT(set_selected_patch_2(int)));
        connect(_side_widget->comboBox_patch1_direction, SIGNAL(currentIndexChanged(int)),_gl_widget, SLOT(set_direction_patch_1(int)));
        connect(_side_widget->comboBox_patch2_direction, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_direction_patch_2(int)));
        connect(_side_widget->pushButton_join_patch, SIGNAL(pressed()),_gl_widget, SLOT(call_join_patch()));
        connect(_side_widget->pushButton_extend_patch, SIGNAL(pressed()),_gl_widget, SLOT(call_extend_patch()));
        connect(_side_widget->pushButton_merge_patch, SIGNAL(pressed()),_gl_widget,SLOT(call_merge_patch()));
        connect(_side_widget->comboBox_lightsource, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(set_selected_light(int)));
        connect(_side_widget->first_der_patch, SIGNAL(clicked(bool)),_gl_widget, SLOT(set_show_first_der_patch(bool)));
        connect(_side_widget->second_der_patch, SIGNAL(clicked(bool)),_gl_widget, SLOT(set_show_second_der_patch(bool)));
    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
