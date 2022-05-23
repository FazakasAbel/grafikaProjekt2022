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

        connect(_side_widget->shader_selector, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_selected_shader(int)));

        connect(_side_widget->r_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_r(double)));
        connect(_side_widget->g_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_g(double)));
        connect(_side_widget->b_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_b(double)));


        connect(_side_widget->smooth_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_smoothing(double)));
        connect(_side_widget->scaling_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_scaling(double)));
        connect(_side_widget->shade_selector, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_selected_shading(double)));
    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}