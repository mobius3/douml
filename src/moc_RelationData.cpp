/****************************************************************************
** Meta object code from reading C++ file 'RelationData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/RelationData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RelationData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RelationData[] = {

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
      14,   13,   13,   13, 0x09,
      28,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RelationData[] = {
    "RelationData\0\0end_deleted()\0on_delete()\0"
};

void RelationData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RelationData *_t = static_cast<RelationData *>(_o);
        switch (_id) {
        case 0: _t->end_deleted(); break;
        case 1: _t->on_delete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RelationData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RelationData::staticMetaObject = {
    { &ClassMemberData::staticMetaObject, qt_meta_stringdata_RelationData,
      qt_meta_data_RelationData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RelationData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RelationData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RelationData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RelationData))
        return static_cast<void*>(const_cast< RelationData*>(this));
    if (!strcmp(_clname, "Labeled<RelationData>"))
        return static_cast< Labeled<RelationData>*>(const_cast< RelationData*>(this));
    return ClassMemberData::qt_metacast(_clname);
}

int RelationData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClassMemberData::qt_metacall(_c, _id, _a);
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
