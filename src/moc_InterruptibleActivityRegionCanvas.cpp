/****************************************************************************
** Meta object code from reading C++ file 'InterruptibleActivityRegionCanvas.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/InterruptibleActivityRegionCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterruptibleActivityRegionCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterruptibleActivityRegionCanvas[] = {

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
      35,   34,   34,   34, 0x08,
      46,   34,   34,   34, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InterruptibleActivityRegionCanvas[] = {
    "InterruptibleActivityRegionCanvas\0\0"
    "modified()\0deleted()\0"
};

void InterruptibleActivityRegionCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InterruptibleActivityRegionCanvas *_t = static_cast<InterruptibleActivityRegionCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InterruptibleActivityRegionCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InterruptibleActivityRegionCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InterruptibleActivityRegionCanvas,
      qt_meta_data_InterruptibleActivityRegionCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InterruptibleActivityRegionCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InterruptibleActivityRegionCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InterruptibleActivityRegionCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterruptibleActivityRegionCanvas))
        return static_cast<void*>(const_cast< InterruptibleActivityRegionCanvas*>(this));
    if (!strcmp(_clname, "ActivityContainerCanvas"))
        return static_cast< ActivityContainerCanvas*>(const_cast< InterruptibleActivityRegionCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int InterruptibleActivityRegionCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
