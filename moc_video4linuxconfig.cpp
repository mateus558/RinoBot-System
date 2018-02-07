/****************************************************************************
** Meta object code from reading C++ file 'video4linuxconfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "video4linuxconfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'video4linuxconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_video4linuxConfig_t {
    QByteArrayData data[14];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_video4linuxConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_video4linuxConfig_t qt_meta_stringdata_video4linuxConfig = {
    {
QT_MOC_LITERAL(0, 0, 17), // "video4linuxConfig"
QT_MOC_LITERAL(1, 18, 9), // "showEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "QShowEvent*"
QT_MOC_LITERAL(4, 41, 5), // "event"
QT_MOC_LITERAL(5, 47, 28), // "on_bright_slider_sliderMoved"
QT_MOC_LITERAL(6, 76, 8), // "position"
QT_MOC_LITERAL(7, 85, 30), // "on_contrast_slider_sliderMoved"
QT_MOC_LITERAL(8, 116, 32), // "on_saturation_slider_sliderMoved"
QT_MOC_LITERAL(9, 149, 31), // "on_white_bal_slider_sliderMoved"
QT_MOC_LITERAL(10, 181, 31), // "on_sharpness_slider_sliderMoved"
QT_MOC_LITERAL(11, 213, 30), // "on_exposure_slider_sliderMoved"
QT_MOC_LITERAL(12, 244, 27), // "on_focus_slider_sliderMoved"
QT_MOC_LITERAL(13, 272, 23) // "on_pushButton_2_clicked"

    },
    "video4linuxConfig\0showEvent\0\0QShowEvent*\0"
    "event\0on_bright_slider_sliderMoved\0"
    "position\0on_contrast_slider_sliderMoved\0"
    "on_saturation_slider_sliderMoved\0"
    "on_white_bal_slider_sliderMoved\0"
    "on_sharpness_slider_sliderMoved\0"
    "on_exposure_slider_sliderMoved\0"
    "on_focus_slider_sliderMoved\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_video4linuxConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       7,    1,   65,    2, 0x08 /* Private */,
       8,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      10,    1,   74,    2, 0x08 /* Private */,
      11,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void video4linuxConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        video4linuxConfig *_t = static_cast<video4linuxConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 1: _t->on_bright_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_contrast_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_saturation_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_white_bal_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_sharpness_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_exposure_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_focus_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject video4linuxConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_video4linuxConfig.data,
      qt_meta_data_video4linuxConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *video4linuxConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *video4linuxConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_video4linuxConfig.stringdata0))
        return static_cast<void*>(const_cast< video4linuxConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int video4linuxConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
