/****************************************************************************
** Meta object code from reading C++ file 'ActivityCanvas.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ActivityCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivityCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActivityCanvas[] = {

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
      16,   15,   15,   15, 0x08,
      27,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ActivityCanvas[] = {
    "ActivityCanvas\0\0modified()\0deleted()\0"
};

void ActivityCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActivityCanvas *_t = static_cast<ActivityCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ActivityCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActivityCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ActivityCanvas,
      qt_meta_data_ActivityCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActivityCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActivityCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActivityCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityCanvas))
        return static_cast<void*>(const_cast< ActivityCanvas*>(this));
    if (!strcmp(_clname, "ActivityContainerCanvas"))
        return static_cast< ActivityContainerCanvas*>(const_cast< ActivityCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int ActivityCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
