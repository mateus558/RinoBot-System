/****************************************************************************
** Meta object code from reading C++ file 'game_functions.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "game_functions.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game_functions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GAME_FUNCTIONS_t {
    QByteArrayData data[4];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GAME_FUNCTIONS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GAME_FUNCTIONS_t qt_meta_stringdata_GAME_FUNCTIONS = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GAME_FUNCTIONS"
QT_MOC_LITERAL(1, 15, 10), // "emitRobots"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8) // "Selector"

    },
    "GAME_FUNCTIONS\0emitRobots\0\0Selector"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GAME_FUNCTIONS[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void GAME_FUNCTIONS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GAME_FUNCTIONS *_t = static_cast<GAME_FUNCTIONS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitRobots((*reinterpret_cast< Selector(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GAME_FUNCTIONS::*_t)(Selector );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GAME_FUNCTIONS::emitRobots)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GAME_FUNCTIONS::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GAME_FUNCTIONS.data,
      qt_meta_data_GAME_FUNCTIONS,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GAME_FUNCTIONS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GAME_FUNCTIONS::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GAME_FUNCTIONS.stringdata0))
        return static_cast<void*>(const_cast< GAME_FUNCTIONS*>(this));
    return QThread::qt_metacast(_clname);
}

int GAME_FUNCTIONS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GAME_FUNCTIONS::emitRobots(Selector _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
