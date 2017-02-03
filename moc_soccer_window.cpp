/****************************************************************************
** Meta object code from reading C++ file 'soccer_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "soccer_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'soccer_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_soccer_window_t {
    QByteArrayData data[28];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_soccer_window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_soccer_window_t qt_meta_stringdata_soccer_window = {
    {
QT_MOC_LITERAL(0, 0, 13), // "soccer_window"
QT_MOC_LITERAL(1, 14, 20), // "updateSerialSettings"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "SettingsDialog::Settings"
QT_MOC_LITERAL(4, 61, 8), // "settings"
QT_MOC_LITERAL(5, 70, 13), // "updateBallPos"
QT_MOC_LITERAL(6, 84, 7), // "Point2d"
QT_MOC_LITERAL(7, 92, 8), // "ball_pos"
QT_MOC_LITERAL(8, 101, 14), // "updateVisionUI"
QT_MOC_LITERAL(9, 116, 3), // "img"
QT_MOC_LITERAL(10, 120, 9), // "updateFPS"
QT_MOC_LITERAL(11, 130, 3), // "fps"
QT_MOC_LITERAL(12, 134, 15), // "updateMapPoints"
QT_MOC_LITERAL(13, 150, 7), // "pVector"
QT_MOC_LITERAL(14, 158, 8), // "map_area"
QT_MOC_LITERAL(15, 167, 15), // "updateAtkPoints"
QT_MOC_LITERAL(16, 183, 8), // "atk_area"
QT_MOC_LITERAL(17, 192, 15), // "updateDefPoints"
QT_MOC_LITERAL(18, 208, 8), // "def_area"
QT_MOC_LITERAL(19, 217, 16), // "updateRobotsInfo"
QT_MOC_LITERAL(20, 234, 7), // "rVector"
QT_MOC_LITERAL(21, 242, 6), // "robots"
QT_MOC_LITERAL(22, 249, 21), // "on_start_game_clicked"
QT_MOC_LITERAL(23, 271, 24), // "on_switch_fields_clicked"
QT_MOC_LITERAL(24, 296, 31), // "on_showAreasRadioButton_toggled"
QT_MOC_LITERAL(25, 328, 7), // "checked"
QT_MOC_LITERAL(26, 336, 26), // "on_read_parameters_clicked"
QT_MOC_LITERAL(27, 363, 18) // "on_iterate_clicked"

    },
    "soccer_window\0updateSerialSettings\0\0"
    "SettingsDialog::Settings\0settings\0"
    "updateBallPos\0Point2d\0ball_pos\0"
    "updateVisionUI\0img\0updateFPS\0fps\0"
    "updateMapPoints\0pVector\0map_area\0"
    "updateAtkPoints\0atk_area\0updateDefPoints\0"
    "def_area\0updateRobotsInfo\0rVector\0"
    "robots\0on_start_game_clicked\0"
    "on_switch_fields_clicked\0"
    "on_showAreasRadioButton_toggled\0checked\0"
    "on_read_parameters_clicked\0"
    "on_iterate_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_soccer_window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       5,    1,   82,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      10,    1,   88,    2, 0x0a /* Public */,
      12,    1,   91,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      17,    1,   97,    2, 0x0a /* Public */,
      19,    1,  100,    2, 0x0a /* Public */,
      22,    0,  103,    2, 0x08 /* Private */,
      23,    0,  104,    2, 0x08 /* Private */,
      24,    1,  105,    2, 0x08 /* Private */,
      26,    0,  108,    2, 0x08 /* Private */,
      27,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QImage,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   16,
    QMetaType::Void, 0x80000000 | 13,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void soccer_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        soccer_window *_t = static_cast<soccer_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSerialSettings((*reinterpret_cast< SettingsDialog::Settings(*)>(_a[1]))); break;
        case 1: _t->updateBallPos((*reinterpret_cast< const Point2d(*)>(_a[1]))); break;
        case 2: _t->updateVisionUI((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->updateFPS((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->updateMapPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 5: _t->updateAtkPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 6: _t->updateDefPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 7: _t->updateRobotsInfo((*reinterpret_cast< const rVector(*)>(_a[1]))); break;
        case 8: _t->on_start_game_clicked(); break;
        case 9: _t->on_switch_fields_clicked(); break;
        case 10: _t->on_showAreasRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_read_parameters_clicked(); break;
        case 12: _t->on_iterate_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject soccer_window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_soccer_window.data,
      qt_meta_data_soccer_window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *soccer_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *soccer_window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_soccer_window.stringdata0))
        return static_cast<void*>(const_cast< soccer_window*>(this));
    return QWidget::qt_metacast(_clname);
}

int soccer_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
