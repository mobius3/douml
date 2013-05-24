/****************************************************************************
** Meta object code from reading C++ file 'BasicData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/BasicData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BasicData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BasicData[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      21,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   10,   10,   10, 0x09,
      43,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BasicData[] = {
    "BasicData\0\0changed()\0deleted()\0"
    "on_delete()\0modified()\0"
};

void BasicData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BasicData *_t = static_cast<BasicData *>(_o);
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->deleted(); break;
        case 2: _t->on_delete(); break;
        case 3: _t->modified(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BasicData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BasicData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BasicData,
      qt_meta_data_BasicData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BasicData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BasicData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BasicData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicData))
        return static_cast<void*>(const_cast< BasicData*>(this));
    return QObject::qt_metacast(_clname);
}

int BasicData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BasicData::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BasicData::deleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
