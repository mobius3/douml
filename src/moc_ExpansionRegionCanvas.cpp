/****************************************************************************
** Meta object code from reading C++ file 'ExpansionRegionCanvas.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ExpansionRegionCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExpansionRegionCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExpansionRegionCanvas[] = {

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
      23,   22,   22,   22, 0x08,
      34,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ExpansionRegionCanvas[] = {
    "ExpansionRegionCanvas\0\0modified()\0"
    "deleted()\0"
};

void ExpansionRegionCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExpansionRegionCanvas *_t = static_cast<ExpansionRegionCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ExpansionRegionCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExpansionRegionCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ExpansionRegionCanvas,
      qt_meta_data_ExpansionRegionCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExpansionRegionCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExpansionRegionCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExpansionRegionCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExpansionRegionCanvas))
        return static_cast<void*>(const_cast< ExpansionRegionCanvas*>(this));
    if (!strcmp(_clname, "ActivityContainerCanvas"))
        return static_cast< ActivityContainerCanvas*>(const_cast< ExpansionRegionCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int ExpansionRegionCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
