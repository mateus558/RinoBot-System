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
    QByteArrayData data[19];
    char stringdata0[408];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_soccer_window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_soccer_window_t qt_meta_stringdata_soccer_window = {
    {
QT_MOC_LITERAL(0, 0, 13), // "soccer_window"
QT_MOC_LITERAL(1, 14, 20), // "updatePerceptionInfo"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 18), // "Vision::Perception"
QT_MOC_LITERAL(4, 55, 20), // "updateSerialSettings"
QT_MOC_LITERAL(5, 76, 24), // "SettingsDialog::Settings"
QT_MOC_LITERAL(6, 101, 14), // "updateVisionUI"
QT_MOC_LITERAL(7, 116, 21), // "receiveSerialSettings"
QT_MOC_LITERAL(8, 138, 9), // "updateFPS"
QT_MOC_LITERAL(9, 148, 21), // "on_start_game_clicked"
QT_MOC_LITERAL(10, 170, 24), // "on_switch_fields_clicked"
QT_MOC_LITERAL(11, 195, 26), // "on_read_parameters_clicked"
QT_MOC_LITERAL(12, 222, 14), // "on_CPH_clicked"
QT_MOC_LITERAL(13, 237, 36), // "on_show_field_areas_checkbox_..."
QT_MOC_LITERAL(14, 274, 7), // "checked"
QT_MOC_LITERAL(15, 282, 31), // "on_show_rnames_checkBox_toggled"
QT_MOC_LITERAL(16, 314, 35), // "on_show_rcentroids_checkbox_t..."
QT_MOC_LITERAL(17, 350, 35), // "on_show_visionlogs_checkbox_t..."
QT_MOC_LITERAL(18, 386, 21) // "on_pushButton_clicked"

    },
    "soccer_window\0updatePerceptionInfo\0\0"
    "Vision::Perception\0updateSerialSettings\0"
    "SettingsDialog::Settings\0updateVisionUI\0"
    "receiveSerialSettings\0updateFPS\0"
    "on_start_game_clicked\0on_switch_fields_clicked\0"
    "on_read_parameters_clicked\0on_CPH_clicked\0"
    "on_show_field_areas_checkbox_toggled\0"
    "checked\0on_show_rnames_checkBox_toggled\0"
    "on_show_rcentroids_checkbox_toggled\0"
    "on_show_visionlogs_checkbox_toggled\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_soccer_window[] = {

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
       4,    1,   87,    2, 0x0a /* Public */,
       6,    1,   90,    2, 0x0a /* Public */,
       7,    1,   93,    2, 0x0a /* Public */,
       8,    1,   96,    2, 0x0a /* Public */,
       9,    0,   99,    2, 0x08 /* Private */,
      10,    0,  100,    2, 0x08 /* Private */,
      11,    0,  101,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    1,  103,    2, 0x08 /* Private */,
      15,    1,  106,    2, 0x08 /* Private */,
      16,    1,  109,    2, 0x08 /* Private */,
      17,    1,  112,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void soccer_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        soccer_window *_t = static_cast<soccer_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updatePerceptionInfo((*reinterpret_cast< Vision::Perception(*)>(_a[1]))); break;
        case 1: _t->updateSerialSettings((*reinterpret_cast< SettingsDialog::Settings(*)>(_a[1]))); break;
        case 2: _t->updateVisionUI((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->receiveSerialSettings((*reinterpret_cast< SettingsDialog::Settings(*)>(_a[1]))); break;
        case 4: _t->updateFPS((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_start_game_clicked(); break;
        case 6: _t->on_switch_fields_clicked(); break;
        case 7: _t->on_read_parameters_clicked(); break;
        case 8: _t->on_CPH_clicked(); break;
        case 9: _t->on_show_field_areas_checkbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_show_rnames_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_show_rcentroids_checkbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_show_visionlogs_checkbox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_clicked(); break;
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
QT_END_MOC_NAMESPACE
