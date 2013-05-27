/****************************************************************************
** Meta object code from reading C++ file 'ColMsgTable.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ColMsgTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColMsgTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColMsgTable[] = {

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
      37,   13,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ColMsgTable[] = {
    "ColMsgTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
};

void ColMsgTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColMsgTable *_t = static_cast<ColMsgTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ColMsgTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ColMsgTable::staticMetaObject = {
    { &MyTable::staticMetaObject, qt_meta_stringdata_ColMsgTable,
      qt_meta_data_ColMsgTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColMsgTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColMsgTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColMsgTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColMsgTable))
        return static_cast<void*>(const_cast< ColMsgTable*>(this));
    return MyTable::qt_metacast(_clname);
}

int ColMsgTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTable::qt_metacall(_c, _id, _a);
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
