/****************************************************************************
** Meta object code from reading C++ file 'ShortcutDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ShortcutDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShortcutDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShortcutDialog[] = {

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
      16,   15,   15,   15, 0x09,
      25,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ShortcutDialog[] = {
    "ShortcutDialog\0\0polish()\0accept()\0"
};

void ShortcutDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShortcutDialog *_t = static_cast<ShortcutDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ShortcutDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShortcutDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ShortcutDialog,
      qt_meta_data_ShortcutDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShortcutDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShortcutDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShortcutDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShortcutDialog))
        return static_cast<void*>(const_cast< ShortcutDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ShortcutDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_ShortcutTable[] = {

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
      39,   15,   14,   14, 0x09,
      82,   74,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ShortcutTable[] = {
    "ShortcutTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
    "row,col\0value_changed(int,int)\0"
};

void ShortcutTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShortcutTable *_t = static_cast<ShortcutTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        case 1: _t->value_changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShortcutTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShortcutTable::staticMetaObject = {
    { &MyTable::staticMetaObject, qt_meta_stringdata_ShortcutTable,
      qt_meta_data_ShortcutTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShortcutTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShortcutTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShortcutTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShortcutTable))
        return static_cast<void*>(const_cast< ShortcutTable*>(this));
    return MyTable::qt_metacast(_clname);
}

int ShortcutTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyTable::qt_metacall(_c, _id, _a);
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
