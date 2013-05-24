/****************************************************************************
** Meta object code from reading C++ file 'ActivityPartitionCanvas.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ActivityPartitionCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivityPartitionCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActivityPartitionCanvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      36,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ActivityPartitionCanvas[] = {
    "ActivityPartitionCanvas\0\0modified()\0"
    "deleted()\0"
};

void ActivityPartitionCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActivityPartitionCanvas *_t = static_cast<ActivityPartitionCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ActivityPartitionCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActivityPartitionCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ActivityPartitionCanvas,
      qt_meta_data_ActivityPartitionCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActivityPartitionCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActivityPartitionCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActivityPartitionCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityPartitionCanvas))
        return static_cast<void*>(const_cast< ActivityPartitionCanvas*>(this));
    if (!strcmp(_clname, "ActivityContainerCanvas"))
        return static_cast< ActivityContainerCanvas*>(const_cast< ActivityPartitionCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int ActivityPartitionCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
