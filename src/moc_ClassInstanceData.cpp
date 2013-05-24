/****************************************************************************
** Meta object code from reading C++ file 'ClassInstanceData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/ClassInstanceData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassInstanceData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassInstanceData[] = {

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
      19,   18,   18,   18, 0x0a,
      27,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClassInstanceData[] = {
    "ClassInstanceData\0\0check()\0check_rels()\0"
};

void ClassInstanceData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassInstanceData *_t = static_cast<ClassInstanceData *>(_o);
        switch (_id) {
        case 0: _t->check(); break;
        case 1: _t->check_rels(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClassInstanceData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassInstanceData::staticMetaObject = {
    { &SimpleData::staticMetaObject, qt_meta_stringdata_ClassInstanceData,
      qt_meta_data_ClassInstanceData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassInstanceData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassInstanceData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassInstanceData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassInstanceData))
        return static_cast<void*>(const_cast< ClassInstanceData*>(this));
    return SimpleData::qt_metacast(_clname);
}

int ClassInstanceData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SimpleData::qt_metacall(_c, _id, _a);
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
