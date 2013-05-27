/****************************************************************************
** Meta object code from reading C++ file 'ClassData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/ClassData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassData[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   10,   10,   10, 0x08,
      46,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClassData[] = {
    "ClassData\0\0actuals_changed()\0"
    "update_actuals()\0on_delete()\0"
};

void ClassData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassData *_t = static_cast<ClassData *>(_o);
        switch (_id) {
        case 0: _t->actuals_changed(); break;
        case 1: _t->update_actuals(); break;
        case 2: _t->on_delete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClassData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassData::staticMetaObject = {
    { &BasicData::staticMetaObject, qt_meta_stringdata_ClassData,
      qt_meta_data_ClassData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassData))
        return static_cast<void*>(const_cast< ClassData*>(this));
    return BasicData::qt_metacast(_clname);
}

int ClassData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicData::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ClassData::actuals_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
