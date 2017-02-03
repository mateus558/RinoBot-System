/****************************************************************************
** Meta object code from reading C++ file 'vision.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vision.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vision.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Vision_t {
    QByteArrayData data[20];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vision_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vision_t qt_meta_stringdata_Vision = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Vision"
QT_MOC_LITERAL(1, 7, 7), // "ballPos"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 7), // "Point2d"
QT_MOC_LITERAL(4, 24, 4), // "ball"
QT_MOC_LITERAL(5, 29, 10), // "robotsInfo"
QT_MOC_LITERAL(6, 40, 7), // "rVector"
QT_MOC_LITERAL(7, 48, 6), // "robots"
QT_MOC_LITERAL(8, 55, 14), // "processedImage"
QT_MOC_LITERAL(9, 70, 5), // "image"
QT_MOC_LITERAL(10, 76, 15), // "framesPerSecond"
QT_MOC_LITERAL(11, 92, 3), // "FPS"
QT_MOC_LITERAL(12, 96, 9), // "mapPoints"
QT_MOC_LITERAL(13, 106, 7), // "pVector"
QT_MOC_LITERAL(14, 114, 10), // "map_points"
QT_MOC_LITERAL(15, 125, 9), // "atkPoints"
QT_MOC_LITERAL(16, 135, 10), // "atk_points"
QT_MOC_LITERAL(17, 146, 9), // "defPoints"
QT_MOC_LITERAL(18, 156, 10), // "def_points"
QT_MOC_LITERAL(19, 167, 9) // "ballFound"

    },
    "Vision\0ballPos\0\0Point2d\0ball\0robotsInfo\0"
    "rVector\0robots\0processedImage\0image\0"
    "framesPerSecond\0FPS\0mapPoints\0pVector\0"
    "map_points\0atkPoints\0atk_points\0"
    "defPoints\0def_points\0ballFound"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vision[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       8,    1,   60,    2, 0x06 /* Public */,
      10,    1,   63,    2, 0x06 /* Public */,
      12,    1,   66,    2, 0x06 /* Public */,
      15,    1,   69,    2, 0x06 /* Public */,
      17,    1,   72,    2, 0x06 /* Public */,
      19,    1,   75,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QImage,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   16,
    QMetaType::Void, 0x80000000 | 13,   18,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void Vision::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vision *_t = static_cast<Vision *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ballPos((*reinterpret_cast< const Point2d(*)>(_a[1]))); break;
        case 1: _t->robotsInfo((*reinterpret_cast< const rVector(*)>(_a[1]))); break;
        case 2: _t->processedImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 3: _t->framesPerSecond((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->mapPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 5: _t->atkPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 6: _t->defPoints((*reinterpret_cast< const pVector(*)>(_a[1]))); break;
        case 7: _t->ballFound((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Vision::*_t)(const Point2d & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::ballPos)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const rVector & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::robotsInfo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::processedImage)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::framesPerSecond)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const pVector & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::mapPoints)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const pVector & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::atkPoints)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const pVector & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::defPoints)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::ballFound)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject Vision::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Vision.data,
      qt_meta_data_Vision,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Vision::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vision::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Vision.stringdata0))
        return static_cast<void*>(const_cast< Vision*>(this));
    return QThread::qt_metacast(_clname);
}

int Vision::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Vision::ballPos(const Point2d & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Vision::robotsInfo(const rVector & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Vision::processedImage(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Vision::framesPerSecond(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Vision::mapPoints(const pVector & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Vision::atkPoints(const pVector & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Vision::defPoints(const pVector & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Vision::ballFound(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
