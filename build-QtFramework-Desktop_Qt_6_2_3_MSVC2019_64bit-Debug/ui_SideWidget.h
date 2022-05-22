/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QCheckBox *first_der;
    QCheckBox *second_der;
    QLabel *label_8;
    QDoubleSpinBox *scale;
    QLabel *NumberOfSubdivisionPointsLabel;
    QSpinBox *set_div_points;
    QLabel *selectedCurveLabel_3;
    QDoubleSpinBox *x_selector;
    QLabel *selectedCurveLabel_4;
    QDoubleSpinBox *y_selector;
    QLabel *selectedCurveLabel_5;
    QDoubleSpinBox *z_selector;
    QLabel *selectedCurveLabel_8;
    QSpinBox *surface_selector;
    QLabel *selectedCurveLabel_9;
    QSpinBox *shader_selector;
    QLabel *selectedCurveLabel_10;
    QDoubleSpinBox *r_selector;
    QDoubleSpinBox *g_selector;
    QDoubleSpinBox *b_selector;
    QLabel *selectedCurveLabel_11;
    QDoubleSpinBox *scaling_selector;
    QDoubleSpinBox *smooth_selector;
    QDoubleSpinBox *shade_selector;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(467, 911);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 441, 841));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 431, 805));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.000100000000000);
        zoom_factor_spin_box->setMaximum(10000.000000000000000);
        zoom_factor_spin_box->setSingleStep(0.100000000000000);
        zoom_factor_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100.000000000000000);
        trans_x_spin_box->setMaximum(100.000000000000000);
        trans_x_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100.000000000000000);
        trans_y_spin_box->setMaximum(100.000000000000000);
        trans_y_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100.000000000000000);
        trans_z_spin_box->setMaximum(100.000000000000000);
        trans_z_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        first_der = new QCheckBox(layoutWidget);
        first_der->setObjectName(QString::fromUtf8("first_der"));

        formLayout->setWidget(7, QFormLayout::LabelRole, first_der);

        second_der = new QCheckBox(layoutWidget);
        second_der->setObjectName(QString::fromUtf8("second_der"));

        formLayout->setWidget(7, QFormLayout::FieldRole, second_der);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_8);

        scale = new QDoubleSpinBox(layoutWidget);
        scale->setObjectName(QString::fromUtf8("scale"));
        scale->setDecimals(5);
        scale->setMinimum(0.000100000000000);
        scale->setMaximum(100.000000000000000);
        scale->setSingleStep(0.100000000000000);
        scale->setValue(1.000000000000000);

        formLayout->setWidget(9, QFormLayout::FieldRole, scale);

        NumberOfSubdivisionPointsLabel = new QLabel(layoutWidget);
        NumberOfSubdivisionPointsLabel->setObjectName(QString::fromUtf8("NumberOfSubdivisionPointsLabel"));

        formLayout->setWidget(10, QFormLayout::LabelRole, NumberOfSubdivisionPointsLabel);

        set_div_points = new QSpinBox(layoutWidget);
        set_div_points->setObjectName(QString::fromUtf8("set_div_points"));
        set_div_points->setMinimum(1);
        set_div_points->setMaximum(1000);
        set_div_points->setValue(200);

        formLayout->setWidget(10, QFormLayout::FieldRole, set_div_points);

        selectedCurveLabel_3 = new QLabel(layoutWidget);
        selectedCurveLabel_3->setObjectName(QString::fromUtf8("selectedCurveLabel_3"));

        formLayout->setWidget(11, QFormLayout::LabelRole, selectedCurveLabel_3);

        x_selector = new QDoubleSpinBox(layoutWidget);
        x_selector->setObjectName(QString::fromUtf8("x_selector"));
        x_selector->setMinimum(-100.000000000000000);
        x_selector->setMaximum(100.000000000000000);
        x_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(11, QFormLayout::FieldRole, x_selector);

        selectedCurveLabel_4 = new QLabel(layoutWidget);
        selectedCurveLabel_4->setObjectName(QString::fromUtf8("selectedCurveLabel_4"));

        formLayout->setWidget(12, QFormLayout::LabelRole, selectedCurveLabel_4);

        y_selector = new QDoubleSpinBox(layoutWidget);
        y_selector->setObjectName(QString::fromUtf8("y_selector"));
        y_selector->setMinimum(-100.000000000000000);
        y_selector->setMaximum(100.000000000000000);
        y_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(12, QFormLayout::FieldRole, y_selector);

        selectedCurveLabel_5 = new QLabel(layoutWidget);
        selectedCurveLabel_5->setObjectName(QString::fromUtf8("selectedCurveLabel_5"));

        formLayout->setWidget(13, QFormLayout::LabelRole, selectedCurveLabel_5);

        z_selector = new QDoubleSpinBox(layoutWidget);
        z_selector->setObjectName(QString::fromUtf8("z_selector"));
        z_selector->setMinimum(-100.000000000000000);
        z_selector->setMaximum(100.000000000000000);
        z_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(13, QFormLayout::FieldRole, z_selector);

        selectedCurveLabel_8 = new QLabel(layoutWidget);
        selectedCurveLabel_8->setObjectName(QString::fromUtf8("selectedCurveLabel_8"));

        formLayout->setWidget(14, QFormLayout::LabelRole, selectedCurveLabel_8);

        surface_selector = new QSpinBox(layoutWidget);
        surface_selector->setObjectName(QString::fromUtf8("surface_selector"));
        surface_selector->setMaximum(10);
        surface_selector->setValue(0);

        formLayout->setWidget(14, QFormLayout::FieldRole, surface_selector);

        selectedCurveLabel_9 = new QLabel(layoutWidget);
        selectedCurveLabel_9->setObjectName(QString::fromUtf8("selectedCurveLabel_9"));

        formLayout->setWidget(15, QFormLayout::LabelRole, selectedCurveLabel_9);

        shader_selector = new QSpinBox(layoutWidget);
        shader_selector->setObjectName(QString::fromUtf8("shader_selector"));
        shader_selector->setMaximum(10);
        shader_selector->setValue(0);

        formLayout->setWidget(15, QFormLayout::FieldRole, shader_selector);

        selectedCurveLabel_10 = new QLabel(layoutWidget);
        selectedCurveLabel_10->setObjectName(QString::fromUtf8("selectedCurveLabel_10"));

        formLayout->setWidget(16, QFormLayout::LabelRole, selectedCurveLabel_10);

        r_selector = new QDoubleSpinBox(layoutWidget);
        r_selector->setObjectName(QString::fromUtf8("r_selector"));
        r_selector->setMinimum(0.000000000000000);
        r_selector->setMaximum(1.000000000000000);
        r_selector->setSingleStep(0.010000000000000);

        formLayout->setWidget(16, QFormLayout::FieldRole, r_selector);

        g_selector = new QDoubleSpinBox(layoutWidget);
        g_selector->setObjectName(QString::fromUtf8("g_selector"));
        g_selector->setMinimum(0.000000000000000);
        g_selector->setMaximum(1.000000000000000);
        g_selector->setSingleStep(0.010000000000000);

        formLayout->setWidget(17, QFormLayout::FieldRole, g_selector);

        b_selector = new QDoubleSpinBox(layoutWidget);
        b_selector->setObjectName(QString::fromUtf8("b_selector"));
        b_selector->setMinimum(0.000000000000000);
        b_selector->setMaximum(1.000000000000000);
        b_selector->setSingleStep(0.010000000000000);

        formLayout->setWidget(18, QFormLayout::FieldRole, b_selector);

        selectedCurveLabel_11 = new QLabel(layoutWidget);
        selectedCurveLabel_11->setObjectName(QString::fromUtf8("selectedCurveLabel_11"));

        formLayout->setWidget(19, QFormLayout::LabelRole, selectedCurveLabel_11);

        scaling_selector = new QDoubleSpinBox(layoutWidget);
        scaling_selector->setObjectName(QString::fromUtf8("scaling_selector"));
        scaling_selector->setMinimum(0.000000000000000);
        scaling_selector->setMaximum(10.000000000000000);
        scaling_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(19, QFormLayout::FieldRole, scaling_selector);

        smooth_selector = new QDoubleSpinBox(layoutWidget);
        smooth_selector->setObjectName(QString::fromUtf8("smooth_selector"));
        smooth_selector->setMinimum(0.000000000000000);
        smooth_selector->setMaximum(10.000000000000000);
        smooth_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(20, QFormLayout::FieldRole, smooth_selector);

        shade_selector = new QDoubleSpinBox(layoutWidget);
        shade_selector->setObjectName(QString::fromUtf8("shade_selector"));
        shade_selector->setMinimum(0.000000000000000);
        shade_selector->setMaximum(10.000000000000000);
        shade_selector->setSingleStep(0.100000000000000);

        formLayout->setWidget(21, QFormLayout::FieldRole, shade_selector);

#if QT_CONFIG(shortcut)
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SideWidget);

        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QCoreApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QCoreApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QCoreApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QCoreApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_4->setText(QCoreApplication::translate("SideWidget", "Zoom factor", nullptr));
#if QT_CONFIG(tooltip)
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QCoreApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QCoreApplication::translate("SideWidget", "Translate along z", nullptr));
        first_der->setText(QCoreApplication::translate("SideWidget", "1st order derivatives", nullptr));
        second_der->setText(QCoreApplication::translate("SideWidget", "2nd order derivatives", nullptr));
        label_8->setText(QCoreApplication::translate("SideWidget", "Scale", nullptr));
#if QT_CONFIG(tooltip)
        scale->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        NumberOfSubdivisionPointsLabel->setText(QCoreApplication::translate("SideWidget", "Number of subdivision points", nullptr));
        selectedCurveLabel_3->setText(QCoreApplication::translate("SideWidget", "X coordinate:", nullptr));
        selectedCurveLabel_4->setText(QCoreApplication::translate("SideWidget", "Y coordinate:", nullptr));
        selectedCurveLabel_5->setText(QCoreApplication::translate("SideWidget", "Z coordinate:", nullptr));
        selectedCurveLabel_8->setText(QCoreApplication::translate("SideWidget", "Selected Surface", nullptr));
        selectedCurveLabel_9->setText(QCoreApplication::translate("SideWidget", "Selected Shader", nullptr));
        selectedCurveLabel_10->setText(QCoreApplication::translate("SideWidget", "Toon variables", nullptr));
        selectedCurveLabel_11->setText(QCoreApplication::translate("SideWidget", "Reflection lines variables", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
