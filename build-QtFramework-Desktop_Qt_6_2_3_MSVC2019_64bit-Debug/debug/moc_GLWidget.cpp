/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtFramework/GUI/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cagd__GLWidget_t {
    const uint offsetsAndSize[50];
    char stringdata0[390];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_cagd__GLWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_cagd__GLWidget_t qt_meta_stringdata_cagd__GLWidget = {
    {
QT_MOC_LITERAL(0, 14), // "cagd::GLWidget"
QT_MOC_LITERAL(15, 12), // "set_x_signal"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 12), // "set_y_signal"
QT_MOC_LITERAL(42, 12), // "set_z_signal"
QT_MOC_LITERAL(55, 11), // "set_angle_x"
QT_MOC_LITERAL(67, 5), // "value"
QT_MOC_LITERAL(73, 11), // "set_angle_y"
QT_MOC_LITERAL(85, 11), // "set_angle_z"
QT_MOC_LITERAL(97, 15), // "set_zoom_factor"
QT_MOC_LITERAL(113, 11), // "set_trans_x"
QT_MOC_LITERAL(125, 11), // "set_trans_y"
QT_MOC_LITERAL(137, 11), // "set_trans_z"
QT_MOC_LITERAL(149, 19), // "set_show_second_der"
QT_MOC_LITERAL(169, 18), // "set_show_first_der"
QT_MOC_LITERAL(188, 23), // "update_selected_point_x"
QT_MOC_LITERAL(212, 23), // "update_selected_point_y"
QT_MOC_LITERAL(236, 23), // "update_selected_point_z"
QT_MOC_LITERAL(260, 19), // "set_selected_shader"
QT_MOC_LITERAL(280, 14), // "set_selected_r"
QT_MOC_LITERAL(295, 14), // "set_selected_g"
QT_MOC_LITERAL(310, 14), // "set_selected_b"
QT_MOC_LITERAL(325, 20), // "set_selected_scaling"
QT_MOC_LITERAL(346, 22), // "set_selected_smoothing"
QT_MOC_LITERAL(369, 20) // "set_selected_shading"

    },
    "cagd::GLWidget\0set_x_signal\0\0set_y_signal\0"
    "set_z_signal\0set_angle_x\0value\0"
    "set_angle_y\0set_angle_z\0set_zoom_factor\0"
    "set_trans_x\0set_trans_y\0set_trans_z\0"
    "set_show_second_der\0set_show_first_der\0"
    "update_selected_point_x\0update_selected_point_y\0"
    "update_selected_point_z\0set_selected_shader\0"
    "set_selected_r\0set_selected_g\0"
    "set_selected_b\0set_selected_scaling\0"
    "set_selected_smoothing\0set_selected_shading"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cagd__GLWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  146,    2, 0x06,    1 /* Public */,
       3,    1,  149,    2, 0x06,    3 /* Public */,
       4,    1,  152,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,  155,    2, 0x0a,    7 /* Public */,
       7,    1,  158,    2, 0x0a,    9 /* Public */,
       8,    1,  161,    2, 0x0a,   11 /* Public */,
       9,    1,  164,    2, 0x0a,   13 /* Public */,
      10,    1,  167,    2, 0x0a,   15 /* Public */,
      11,    1,  170,    2, 0x0a,   17 /* Public */,
      12,    1,  173,    2, 0x0a,   19 /* Public */,
      13,    1,  176,    2, 0x0a,   21 /* Public */,
      14,    1,  179,    2, 0x0a,   23 /* Public */,
      15,    1,  182,    2, 0x0a,   25 /* Public */,
      16,    1,  185,    2, 0x0a,   27 /* Public */,
      17,    1,  188,    2, 0x0a,   29 /* Public */,
      18,    1,  191,    2, 0x0a,   31 /* Public */,
      19,    1,  194,    2, 0x0a,   33 /* Public */,
      20,    1,  197,    2, 0x0a,   35 /* Public */,
      21,    1,  200,    2, 0x0a,   37 /* Public */,
      22,    1,  203,    2, 0x0a,   39 /* Public */,
      23,    1,  206,    2, 0x0a,   41 /* Public */,
      24,    1,  209,    2, 0x0a,   43 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void cagd::GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->set_x_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->set_y_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->set_z_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->set_angle_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->set_angle_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->set_angle_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->set_zoom_factor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->set_trans_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->set_trans_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->set_trans_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->set_show_second_der((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->set_show_first_der((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->update_selected_point_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->update_selected_point_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->update_selected_point_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->set_selected_shader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->set_selected_r((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->set_selected_g((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->set_selected_b((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->set_selected_scaling((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->set_selected_smoothing((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->set_selected_shading((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_x_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_y_signal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_z_signal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject cagd::GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_cagd__GLWidget.offsetsAndSize,
    qt_meta_data_cagd__GLWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_cagd__GLWidget_t
, QtPrivate::TypeAndForceComplete<GLWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>


>,
    nullptr
} };


const QMetaObject *cagd::GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cagd::GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cagd__GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int cagd::GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void cagd::GLWidget::set_x_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cagd::GLWidget::set_y_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cagd::GLWidget::set_z_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
