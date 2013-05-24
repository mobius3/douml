/****************************************************************************
** Meta object code from reading C++ file 'CodClassInstCanvas.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/CodClassInstCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CodClassInstCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CodClassInstCanvas[] = {

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
      20,   19,   19,   19, 0x08,
      31,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CodClassInstCanvas[] = {
    "CodClassInstCanvas\0\0modified()\0deleted()\0"
};

void CodClassInstCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodClassInstCanvas *_t = static_cast<CodClassInstCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CodClassInstCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodClassInstCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CodClassInstCanvas,
      qt_meta_data_CodClassInstCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodClassInstCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodClassInstCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodClassInstCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodClassInstCanvas))
        return static_cast<void*>(const_cast< CodClassInstCanvas*>(this));
    if (!strcmp(_clname, "CodObjCanvas"))
        return static_cast< CodObjCanvas*>(const_cast< CodClassInstCanvas*>(this));
    if (!strcmp(_clname, "ClassInstCanvas"))
        return static_cast< ClassInstCanvas*>(const_cast< CodClassInstCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int CodClassInstCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
