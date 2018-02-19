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
    QByteArrayData data[20];
    char stringdata0[414];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_video4linuxConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_video4linuxConfig_t qt_meta_stringdata_video4linuxConfig = {
    {
QT_MOC_LITERAL(0, 0, 17), // "video4linuxConfig"
QT_MOC_LITERAL(1, 18, 14), // "updateVisionUI"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "showEvent"
QT_MOC_LITERAL(4, 44, 11), // "QShowEvent*"
QT_MOC_LITERAL(5, 56, 5), // "event"
QT_MOC_LITERAL(6, 62, 10), // "closeEvent"
QT_MOC_LITERAL(7, 73, 12), // "QCloseEvent*"
QT_MOC_LITERAL(8, 86, 28), // "on_bright_slider_sliderMoved"
QT_MOC_LITERAL(9, 115, 8), // "position"
QT_MOC_LITERAL(10, 124, 30), // "on_contrast_slider_sliderMoved"
QT_MOC_LITERAL(11, 155, 32), // "on_saturation_slider_sliderMoved"
QT_MOC_LITERAL(12, 188, 31), // "on_white_bal_slider_sliderMoved"
QT_MOC_LITERAL(13, 220, 31), // "on_sharpness_slider_sliderMoved"
QT_MOC_LITERAL(14, 252, 30), // "on_exposure_slider_sliderMoved"
QT_MOC_LITERAL(15, 283, 27), // "on_focus_slider_sliderMoved"
QT_MOC_LITERAL(16, 311, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(17, 335, 23), // "on_setToDefault_clicked"
QT_MOC_LITERAL(18, 359, 26), // "on_gain_slider_sliderMoved"
QT_MOC_LITERAL(19, 386, 27) // "on_Init_Capture_btn_clicked"

    },
    "video4linuxConfig\0updateVisionUI\0\0"
    "showEvent\0QShowEvent*\0event\0closeEvent\0"
    "QCloseEvent*\0on_bright_slider_sliderMoved\0"
    "position\0on_contrast_slider_sliderMoved\0"
    "on_saturation_slider_sliderMoved\0"
    "on_white_bal_slider_sliderMoved\0"
    "on_sharpness_slider_sliderMoved\0"
    "on_exposure_slider_sliderMoved\0"
    "on_focus_slider_sliderMoved\0"
    "on_pushButton_2_clicked\0on_setToDefault_clicked\0"
    "on_gain_slider_sliderMoved\0"
    "on_Init_Capture_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_video4linuxConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       3,    1,   87,    2, 0x08 /* Private */,
       6,    1,   90,    2, 0x08 /* Private */,
       8,    1,   93,    2, 0x08 /* Private */,
      10,    1,   96,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      12,    1,  102,    2, 0x08 /* Private */,
      13,    1,  105,    2, 0x08 /* Private */,
      14,    1,  108,    2, 0x08 /* Private */,
      15,    1,  111,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    1,  116,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void video4linuxConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        video4linuxConfig *_t = static_cast<video4linuxConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateVisionUI((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->on_bright_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_contrast_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_saturation_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_white_bal_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_sharpness_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_exposure_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_focus_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->on_setToDefault_clicked(); break;
        case 12: _t->on_gain_slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_Init_Capture_btn_clicked(); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
