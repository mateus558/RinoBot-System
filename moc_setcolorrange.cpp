/****************************************************************************
** Meta object code from reading C++ file 'setcolorrange.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setcolorrange.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setcolorrange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetColorRange_t {
    QByteArrayData data[17];
    char stringdata0[339];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetColorRange_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetColorRange_t qt_meta_stringdata_SetColorRange = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SetColorRange"
QT_MOC_LITERAL(1, 14, 14), // "updateVisionUI"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 31), // "on_horizontalSlider_sliderMoved"
QT_MOC_LITERAL(4, 62, 8), // "position"
QT_MOC_LITERAL(5, 71, 33), // "on_horizontalSlider_2_sliderM..."
QT_MOC_LITERAL(6, 105, 33), // "on_horizontalSlider_3_sliderM..."
QT_MOC_LITERAL(7, 139, 33), // "on_horizontalSlider_4_sliderM..."
QT_MOC_LITERAL(8, 173, 33), // "on_horizontalSlider_5_sliderM..."
QT_MOC_LITERAL(9, 207, 33), // "on_horizontalSlider_6_sliderM..."
QT_MOC_LITERAL(10, 241, 9), // "showEvent"
QT_MOC_LITERAL(11, 251, 11), // "QShowEvent*"
QT_MOC_LITERAL(12, 263, 5), // "event"
QT_MOC_LITERAL(13, 269, 10), // "closeEvent"
QT_MOC_LITERAL(14, 280, 12), // "QCloseEvent*"
QT_MOC_LITERAL(15, 293, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(16, 317, 21) // "on_pushButton_clicked"

    },
    "SetColorRange\0updateVisionUI\0\0"
    "on_horizontalSlider_sliderMoved\0"
    "position\0on_horizontalSlider_2_sliderMoved\0"
    "on_horizontalSlider_3_sliderMoved\0"
    "on_horizontalSlider_4_sliderMoved\0"
    "on_horizontalSlider_5_sliderMoved\0"
    "on_horizontalSlider_6_sliderMoved\0"
    "showEvent\0QShowEvent*\0event\0closeEvent\0"
    "QCloseEvent*\0on_pushButton_2_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetColorRange[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       3,    1,   72,    2, 0x08 /* Private */,
       5,    1,   75,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SetColorRange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetColorRange *_t = static_cast<SetColorRange *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateVisionUI((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->on_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_2_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_horizontalSlider_3_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_horizontalSlider_4_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_horizontalSlider_5_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_6_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        case 10: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SetColorRange::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SetColorRange.data,
      qt_meta_data_SetColorRange,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetColorRange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetColorRange::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetColorRange.stringdata0))
        return static_cast<void*>(const_cast< SetColorRange*>(this));
    return QWidget::qt_metacast(_clname);
}

int SetColorRange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
