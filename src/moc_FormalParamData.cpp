/****************************************************************************
** Meta object code from reading C++ file 'FormalParamData.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data/FormalParamData.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FormalParamData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormalParamData[] = {

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
      17,   16,   16,   16, 0x09,
      37,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FormalParamData[] = {
    "FormalParamData\0\0on_delete_default()\0"
    "on_delete_extends()\0"
};

void FormalParamData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormalParamData *_t = static_cast<FormalParamData *>(_o);
        switch (_id) {
        case 0: _t->on_delete_default(); break;
        case 1: _t->on_delete_extends(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FormalParamData::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormalParamData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FormalParamData,
      qt_meta_data_FormalParamData, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormalParamData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormalParamData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormalParamData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormalParamData))
        return static_cast<void*>(const_cast< FormalParamData*>(this));
    return QObject::qt_metacast(_clname);
}

int FormalParamData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
