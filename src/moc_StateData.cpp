/****************************************************************************
** Meta object code from reading C++ file 'StateData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/StateData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateData[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StateData[] = {
    "StateData\0\0on_delete()\0"
};

void StateData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateData *_t = static_cast<StateData *>(_o);
        switch (_id) {
        case 0: _t->on_delete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StateData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateData::staticMetaObject = {
    { &SimpleData::staticMetaObject, qt_meta_stringdata_StateData,
      qt_meta_data_StateData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateData))
        return static_cast<void*>(const_cast< StateData*>(this));
    return SimpleData::qt_metacast(_clname);
}

int StateData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SimpleData::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
