/****************************************************************************
** Meta object code from reading C++ file 'ToolDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ToolDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolDialog[] = {

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
      12,   11,   11,   11, 0x09,
      21,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ToolDialog[] = {
    "ToolDialog\0\0accept()\0polish()\0"
};

void ToolDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToolDialog *_t = static_cast<ToolDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->polish(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ToolDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToolDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ToolDialog,
      qt_meta_data_ToolDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolDialog))
        return static_cast<void*>(const_cast< ToolDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ToolDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_ToolTable[] = {

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
      35,   11,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ToolTable[] = {
    "ToolTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
};

void ToolTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToolTable *_t = static_cast<ToolTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ToolTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToolTable::staticMetaObject = {
    { &StringTable::staticMetaObject, qt_meta_stringdata_ToolTable,
      qt_meta_data_ToolTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolTable))
        return static_cast<void*>(const_cast< ToolTable*>(this));
    return StringTable::qt_metacast(_clname);
}

int ToolTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StringTable::qt_metacall(_c, _id, _a);
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
