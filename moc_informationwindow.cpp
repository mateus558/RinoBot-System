/****************************************************************************
** Meta object code from reading C++ file 'informationwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "informationwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'informationwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InformationWindow_t {
    QByteArrayData data[13];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InformationWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InformationWindow_t qt_meta_stringdata_InformationWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "InformationWindow"
QT_MOC_LITERAL(1, 18, 5), // "close"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "updateData"
QT_MOC_LITERAL(4, 36, 14), // "InfoParameters"
QT_MOC_LITERAL(5, 51, 4), // "data"
QT_MOC_LITERAL(6, 56, 31), // "on_valueFilterchangebtn_clicked"
QT_MOC_LITERAL(7, 88, 25), // "on_startFilterbtn_clicked"
QT_MOC_LITERAL(8, 114, 32), // "on_velocityMaxGandalfbtn_clicked"
QT_MOC_LITERAL(9, 147, 30), // "on_velocityMaxLeonabtn_clicked"
QT_MOC_LITERAL(10, 178, 31), // "on_velocityMaxPrestobtn_clicked"
QT_MOC_LITERAL(11, 210, 17), // "on_pidbtn_clicked"
QT_MOC_LITERAL(12, 228, 22) // "on_strategybtn_clicked"

    },
    "InformationWindow\0close\0\0updateData\0"
    "InfoParameters\0data\0on_valueFilterchangebtn_clicked\0"
    "on_startFilterbtn_clicked\0"
    "on_velocityMaxGandalfbtn_clicked\0"
    "on_velocityMaxLeonabtn_clicked\0"
    "on_velocityMaxPrestobtn_clicked\0"
    "on_pidbtn_clicked\0on_strategybtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InformationWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   60,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InformationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InformationWindow *_t = static_cast<InformationWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->close(); break;
        case 1: _t->updateData((*reinterpret_cast< InfoParameters(*)>(_a[1]))); break;
        case 2: _t->on_valueFilterchangebtn_clicked(); break;
        case 3: _t->on_startFilterbtn_clicked(); break;
        case 4: _t->on_velocityMaxGandalfbtn_clicked(); break;
        case 5: _t->on_velocityMaxLeonabtn_clicked(); break;
        case 6: _t->on_velocityMaxPrestobtn_clicked(); break;
        case 7: _t->on_pidbtn_clicked(); break;
        case 8: _t->on_strategybtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InformationWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InformationWindow::close)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject InformationWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InformationWindow.data,
      qt_meta_data_InformationWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InformationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InformationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InformationWindow.stringdata0))
        return static_cast<void*>(const_cast< InformationWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int InformationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void InformationWindow::close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
