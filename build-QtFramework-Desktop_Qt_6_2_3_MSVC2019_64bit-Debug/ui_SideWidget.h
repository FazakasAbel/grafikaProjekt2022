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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
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
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QDoubleSpinBox *scale;
    QLabel *NumberOfSubdivisionPointsLabel;
    QSpinBox *set_div_points;
    QLabel *label_9;
    QSpinBox *arc_selector;
    QComboBox *direction_selector;
    QPushButton *plus;
    QPushButton *minus;
    QLabel *label_10;
    QSpinBox *arc_point_selector;
    QLabel *selectedCurveLabel_3;
    QDoubleSpinBox *x_selector;
    QLabel *selectedCurveLabel_4;
    QDoubleSpinBox *y_selector;
    QLabel *selectedCurveLabel_5;
    QDoubleSpinBox *z_selector;
    QWidget *tab_2;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_4;
    QLabel *label_14;
    QLabel *label_11;
    QCheckBox *checkBox_texture;
    QLabel *label_12;
    QComboBox *comboBox_texture;
    QLabel *label_13;
    QCheckBox *checkBox_shader;
    QLabel *label_27;
    QComboBox *comboBox_shader;
    QLabel *label_28;
    QCheckBox *checkBox_material;
    QLabel *label_29;
    QComboBox *comboBox_material;
    QLabel *selectedCurveLabel_10;
    QDoubleSpinBox *r_selector;
    QDoubleSpinBox *g_selector;
    QDoubleSpinBox *b_selector;
    QLabel *selectedCurveLabel_11;
    QDoubleSpinBox *scaling_selector;
    QDoubleSpinBox *smooth_selector;
    QDoubleSpinBox *shade_selector;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *spinBox_r;
    QDoubleSpinBox *spinBox_g;
    QDoubleSpinBox *spinBox_b;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(467, 1106);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 441, 1281));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 431, 221));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(7);
        formLayout->setVerticalSpacing(6);
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

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 240, 431, 621));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 421, 361));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_8);

        scale = new QDoubleSpinBox(formLayoutWidget);
        scale->setObjectName(QString::fromUtf8("scale"));
        scale->setDecimals(5);
        scale->setMinimum(0.000100000000000);
        scale->setMaximum(100.000000000000000);
        scale->setSingleStep(0.100000000000000);
        scale->setValue(1.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, scale);

        NumberOfSubdivisionPointsLabel = new QLabel(formLayoutWidget);
        NumberOfSubdivisionPointsLabel->setObjectName(QString::fromUtf8("NumberOfSubdivisionPointsLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, NumberOfSubdivisionPointsLabel);

        set_div_points = new QSpinBox(formLayoutWidget);
        set_div_points->setObjectName(QString::fromUtf8("set_div_points"));
        set_div_points->setMinimum(1);
        set_div_points->setMaximum(1000);
        set_div_points->setValue(200);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, set_div_points);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_9);

        arc_selector = new QSpinBox(formLayoutWidget);
        arc_selector->setObjectName(QString::fromUtf8("arc_selector"));
        arc_selector->setMinimum(0);
        arc_selector->setMaximum(20);
        arc_selector->setValue(0);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, arc_selector);

        direction_selector = new QComboBox(formLayoutWidget);
        direction_selector->addItem(QString());
        direction_selector->addItem(QString());
        direction_selector->addItem(QString());
        direction_selector->setObjectName(QString::fromUtf8("direction_selector"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, direction_selector);

        plus = new QPushButton(formLayoutWidget);
        plus->setObjectName(QString::fromUtf8("plus"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, plus);

        minus = new QPushButton(formLayoutWidget);
        minus->setObjectName(QString::fromUtf8("minus"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, minus);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_10);

        arc_point_selector = new QSpinBox(formLayoutWidget);
        arc_point_selector->setObjectName(QString::fromUtf8("arc_point_selector"));
        arc_point_selector->setMinimum(0);
        arc_point_selector->setMaximum(3);
        arc_point_selector->setValue(0);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, arc_point_selector);

        selectedCurveLabel_3 = new QLabel(formLayoutWidget);
        selectedCurveLabel_3->setObjectName(QString::fromUtf8("selectedCurveLabel_3"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, selectedCurveLabel_3);

        x_selector = new QDoubleSpinBox(formLayoutWidget);
        x_selector->setObjectName(QString::fromUtf8("x_selector"));
        x_selector->setMinimum(-100.000000000000000);
        x_selector->setMaximum(100.000000000000000);
        x_selector->setSingleStep(0.100000000000000);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, x_selector);

        selectedCurveLabel_4 = new QLabel(formLayoutWidget);
        selectedCurveLabel_4->setObjectName(QString::fromUtf8("selectedCurveLabel_4"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, selectedCurveLabel_4);

        y_selector = new QDoubleSpinBox(formLayoutWidget);
        y_selector->setObjectName(QString::fromUtf8("y_selector"));
        y_selector->setMinimum(-100.000000000000000);
        y_selector->setMaximum(100.000000000000000);
        y_selector->setSingleStep(0.100000000000000);

        formLayout_2->setWidget(8, QFormLayout::FieldRole, y_selector);

        selectedCurveLabel_5 = new QLabel(formLayoutWidget);
        selectedCurveLabel_5->setObjectName(QString::fromUtf8("selectedCurveLabel_5"));

        formLayout_2->setWidget(9, QFormLayout::LabelRole, selectedCurveLabel_5);

        z_selector = new QDoubleSpinBox(formLayoutWidget);
        z_selector->setObjectName(QString::fromUtf8("z_selector"));
        z_selector->setMinimum(-100.000000000000000);
        z_selector->setMaximum(100.000000000000000);
        z_selector->setSingleStep(0.100000000000000);

        formLayout_2->setWidget(9, QFormLayout::FieldRole, z_selector);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayoutWidget_2 = new QWidget(tab_2);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 0, 421, 437));
        formLayout_4 = new QFormLayout(formLayoutWidget_2);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(formLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_14);

        label_11 = new QLabel(formLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_11);

        checkBox_texture = new QCheckBox(formLayoutWidget_2);
        checkBox_texture->setObjectName(QString::fromUtf8("checkBox_texture"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, checkBox_texture);

        label_12 = new QLabel(formLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_4->setWidget(4, QFormLayout::LabelRole, label_12);

        comboBox_texture = new QComboBox(formLayoutWidget_2);
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->addItem(QString());
        comboBox_texture->setObjectName(QString::fromUtf8("comboBox_texture"));

        formLayout_4->setWidget(4, QFormLayout::FieldRole, comboBox_texture);

        label_13 = new QLabel(formLayoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_4->setWidget(5, QFormLayout::LabelRole, label_13);

        checkBox_shader = new QCheckBox(formLayoutWidget_2);
        checkBox_shader->setObjectName(QString::fromUtf8("checkBox_shader"));

        formLayout_4->setWidget(5, QFormLayout::FieldRole, checkBox_shader);

        label_27 = new QLabel(formLayoutWidget_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_4->setWidget(6, QFormLayout::LabelRole, label_27);

        comboBox_shader = new QComboBox(formLayoutWidget_2);
        comboBox_shader->addItem(QString());
        comboBox_shader->addItem(QString());
        comboBox_shader->addItem(QString());
        comboBox_shader->addItem(QString());
        comboBox_shader->setObjectName(QString::fromUtf8("comboBox_shader"));

        formLayout_4->setWidget(6, QFormLayout::FieldRole, comboBox_shader);

        label_28 = new QLabel(formLayoutWidget_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout_4->setWidget(7, QFormLayout::LabelRole, label_28);

        checkBox_material = new QCheckBox(formLayoutWidget_2);
        checkBox_material->setObjectName(QString::fromUtf8("checkBox_material"));
        checkBox_material->setChecked(false);

        formLayout_4->setWidget(7, QFormLayout::FieldRole, checkBox_material);

        label_29 = new QLabel(formLayoutWidget_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        formLayout_4->setWidget(8, QFormLayout::LabelRole, label_29);

        comboBox_material = new QComboBox(formLayoutWidget_2);
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->addItem(QString());
        comboBox_material->setObjectName(QString::fromUtf8("comboBox_material"));

        formLayout_4->setWidget(8, QFormLayout::FieldRole, comboBox_material);

        selectedCurveLabel_10 = new QLabel(formLayoutWidget_2);
        selectedCurveLabel_10->setObjectName(QString::fromUtf8("selectedCurveLabel_10"));

        formLayout_4->setWidget(9, QFormLayout::LabelRole, selectedCurveLabel_10);

        r_selector = new QDoubleSpinBox(formLayoutWidget_2);
        r_selector->setObjectName(QString::fromUtf8("r_selector"));
        r_selector->setMinimum(0.000000000000000);
        r_selector->setMaximum(1.000000000000000);
        r_selector->setSingleStep(0.010000000000000);

        formLayout_4->setWidget(9, QFormLayout::FieldRole, r_selector);

        g_selector = new QDoubleSpinBox(formLayoutWidget_2);
        g_selector->setObjectName(QString::fromUtf8("g_selector"));
        g_selector->setMinimum(0.000000000000000);
        g_selector->setMaximum(1.000000000000000);
        g_selector->setSingleStep(0.010000000000000);

        formLayout_4->setWidget(10, QFormLayout::FieldRole, g_selector);

        b_selector = new QDoubleSpinBox(formLayoutWidget_2);
        b_selector->setObjectName(QString::fromUtf8("b_selector"));
        b_selector->setMinimum(0.000000000000000);
        b_selector->setMaximum(1.000000000000000);
        b_selector->setSingleStep(0.010000000000000);

        formLayout_4->setWidget(11, QFormLayout::FieldRole, b_selector);

        selectedCurveLabel_11 = new QLabel(formLayoutWidget_2);
        selectedCurveLabel_11->setObjectName(QString::fromUtf8("selectedCurveLabel_11"));

        formLayout_4->setWidget(12, QFormLayout::LabelRole, selectedCurveLabel_11);

        scaling_selector = new QDoubleSpinBox(formLayoutWidget_2);
        scaling_selector->setObjectName(QString::fromUtf8("scaling_selector"));
        scaling_selector->setMinimum(0.000000000000000);
        scaling_selector->setMaximum(10.000000000000000);
        scaling_selector->setSingleStep(0.100000000000000);

        formLayout_4->setWidget(12, QFormLayout::FieldRole, scaling_selector);

        smooth_selector = new QDoubleSpinBox(formLayoutWidget_2);
        smooth_selector->setObjectName(QString::fromUtf8("smooth_selector"));
        smooth_selector->setMinimum(0.000000000000000);
        smooth_selector->setMaximum(10.000000000000000);
        smooth_selector->setSingleStep(0.100000000000000);

        formLayout_4->setWidget(13, QFormLayout::FieldRole, smooth_selector);

        shade_selector = new QDoubleSpinBox(formLayoutWidget_2);
        shade_selector->setObjectName(QString::fromUtf8("shade_selector"));
        shade_selector->setMinimum(0.000000000000000);
        shade_selector->setMaximum(10.000000000000000);
        shade_selector->setSingleStep(0.100000000000000);

        formLayout_4->setWidget(14, QFormLayout::FieldRole, shade_selector);

        label_15 = new QLabel(formLayoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_15);

        label_16 = new QLabel(formLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_16);

        spinBox_r = new QDoubleSpinBox(formLayoutWidget_2);
        spinBox_r->setObjectName(QString::fromUtf8("spinBox_r"));
        spinBox_r->setMaximum(1.000000000000000);
        spinBox_r->setSingleStep(0.010000000000000);
        spinBox_r->setValue(1.000000000000000);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, spinBox_r);

        spinBox_g = new QDoubleSpinBox(formLayoutWidget_2);
        spinBox_g->setObjectName(QString::fromUtf8("spinBox_g"));
        spinBox_g->setMaximum(1.000000000000000);
        spinBox_g->setSingleStep(0.010000000000000);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, spinBox_g);

        spinBox_b = new QDoubleSpinBox(formLayoutWidget_2);
        spinBox_b->setObjectName(QString::fromUtf8("spinBox_b"));
        spinBox_b->setMaximum(1.000000000000000);
        spinBox_b->setSingleStep(0.010000000000000);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, spinBox_b);

        tabWidget->addTab(tab_2, QString());
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

        tabWidget->setCurrentIndex(1);


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
        label_9->setText(QCoreApplication::translate("SideWidget", "Selected arc", nullptr));
        direction_selector->setItemText(0, QCoreApplication::translate("SideWidget", "x", nullptr));
        direction_selector->setItemText(1, QCoreApplication::translate("SideWidget", "y", nullptr));
        direction_selector->setItemText(2, QCoreApplication::translate("SideWidget", "z", nullptr));

        plus->setText(QCoreApplication::translate("SideWidget", "+", nullptr));
        minus->setText(QCoreApplication::translate("SideWidget", "-", nullptr));
        label_10->setText(QCoreApplication::translate("SideWidget", "Selected arc point", nullptr));
        selectedCurveLabel_3->setText(QCoreApplication::translate("SideWidget", "X coordinate:", nullptr));
        selectedCurveLabel_4->setText(QCoreApplication::translate("SideWidget", "Y coordinate:", nullptr));
        selectedCurveLabel_5->setText(QCoreApplication::translate("SideWidget", "Z coordinate:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SideWidget", "Arc", nullptr));
        label_14->setText(QCoreApplication::translate("SideWidget", "R", nullptr));
        label_11->setText(QCoreApplication::translate("SideWidget", "Enable Texture", nullptr));
        checkBox_texture->setText(QString());
        label_12->setText(QCoreApplication::translate("SideWidget", "Select Texture", nullptr));
        comboBox_texture->setItemText(0, QCoreApplication::translate("SideWidget", "0", nullptr));
        comboBox_texture->setItemText(1, QCoreApplication::translate("SideWidget", "1", nullptr));
        comboBox_texture->setItemText(2, QCoreApplication::translate("SideWidget", "2", nullptr));
        comboBox_texture->setItemText(3, QCoreApplication::translate("SideWidget", "3", nullptr));
        comboBox_texture->setItemText(4, QCoreApplication::translate("SideWidget", "4", nullptr));
        comboBox_texture->setItemText(5, QCoreApplication::translate("SideWidget", "5", nullptr));
        comboBox_texture->setItemText(6, QCoreApplication::translate("SideWidget", "6", nullptr));
        comboBox_texture->setItemText(7, QCoreApplication::translate("SideWidget", "7", nullptr));
        comboBox_texture->setItemText(8, QCoreApplication::translate("SideWidget", "8", nullptr));
        comboBox_texture->setItemText(9, QCoreApplication::translate("SideWidget", "9", nullptr));
        comboBox_texture->setItemText(10, QCoreApplication::translate("SideWidget", "10", nullptr));
        comboBox_texture->setItemText(11, QCoreApplication::translate("SideWidget", "11", nullptr));
        comboBox_texture->setItemText(12, QCoreApplication::translate("SideWidget", "12", nullptr));
        comboBox_texture->setItemText(13, QCoreApplication::translate("SideWidget", "13", nullptr));

        label_13->setText(QCoreApplication::translate("SideWidget", "Enable Shader", nullptr));
        checkBox_shader->setText(QString());
        label_27->setText(QCoreApplication::translate("SideWidget", "Select Shader", nullptr));
        comboBox_shader->setItemText(0, QCoreApplication::translate("SideWidget", "Directional Light", nullptr));
        comboBox_shader->setItemText(1, QCoreApplication::translate("SideWidget", "Reflection Lines", nullptr));
        comboBox_shader->setItemText(2, QCoreApplication::translate("SideWidget", "Toonify", nullptr));
        comboBox_shader->setItemText(3, QCoreApplication::translate("SideWidget", "Two Sided Lighting", nullptr));

        label_28->setText(QCoreApplication::translate("SideWidget", "Enable Material", nullptr));
        checkBox_material->setText(QString());
        label_29->setText(QCoreApplication::translate("SideWidget", "Select Material", nullptr));
        comboBox_material->setItemText(0, QCoreApplication::translate("SideWidget", "Brass", nullptr));
        comboBox_material->setItemText(1, QCoreApplication::translate("SideWidget", "Emerald", nullptr));
        comboBox_material->setItemText(2, QCoreApplication::translate("SideWidget", "Gold", nullptr));
        comboBox_material->setItemText(3, QCoreApplication::translate("SideWidget", "Pearl", nullptr));
        comboBox_material->setItemText(4, QCoreApplication::translate("SideWidget", "Ruby", nullptr));
        comboBox_material->setItemText(5, QCoreApplication::translate("SideWidget", "Silver", nullptr));
        comboBox_material->setItemText(6, QCoreApplication::translate("SideWidget", "Turquoise", nullptr));

        selectedCurveLabel_10->setText(QCoreApplication::translate("SideWidget", "Toon variables", nullptr));
        selectedCurveLabel_11->setText(QCoreApplication::translate("SideWidget", "Reflection lines variables", nullptr));
        label_15->setText(QCoreApplication::translate("SideWidget", "G", nullptr));
        label_16->setText(QCoreApplication::translate("SideWidget", "B", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SideWidget", "Patch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
