/****************************************************************************
** Meta object code from reading C++ file 'vision.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vision.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vision.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Vision_t {
    QByteArrayData data[11];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vision_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vision_t qt_meta_stringdata_Vision = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Vision"
QT_MOC_LITERAL(1, 7, 13), // "infoPercepted"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 18), // "Vision::Perception"
QT_MOC_LITERAL(4, 41, 14), // "processedImage"
QT_MOC_LITERAL(5, 56, 5), // "image"
QT_MOC_LITERAL(6, 62, 15), // "framesPerSecond"
QT_MOC_LITERAL(7, 78, 3), // "FPS"
QT_MOC_LITERAL(8, 82, 17), // "updateFuzzyRobots"
QT_MOC_LITERAL(9, 100, 18), // "std::vector<Robot>"
QT_MOC_LITERAL(10, 119, 17) // "updateMoverRobots"

    },
    "Vision\0infoPercepted\0\0Vision::Perception\0"
    "processedImage\0image\0framesPerSecond\0"
    "FPS\0updateFuzzyRobots\0std::vector<Robot>\0"
    "updateMoverRobots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vision[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QImage,    5,
    QMetaType::Void, QMetaType::Double,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void Vision::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vision *_t = static_cast<Vision *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->infoPercepted((*reinterpret_cast< Vision::Perception(*)>(_a[1]))); break;
        case 1: _t->processedImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->framesPerSecond((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->updateFuzzyRobots((*reinterpret_cast< std::vector<Robot>(*)>(_a[1]))); break;
        case 4: _t->updateMoverRobots((*reinterpret_cast< std::vector<Robot>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Vision::*_t)(Vision::Perception );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::infoPercepted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::processedImage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Vision::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vision::framesPerSecond)) {
                *result = 2;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Vision::infoPercepted(Vision::Perception _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Vision::processedImage(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Vision::framesPerSecond(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
