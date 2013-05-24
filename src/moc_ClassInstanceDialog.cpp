/****************************************************************************
** Meta object code from reading C++ file 'ClassInstanceDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ClassInstanceDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassInstanceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RelTable[] = {

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
      34,   10,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RelTable[] = {
    "RelTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
};

void RelTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RelTable *_t = static_cast<RelTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RelTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RelTable::staticMetaObject = {
    { &MyTable::staticMetaObject, qt_meta_stringdata_RelTable,
      qt_meta_data_RelTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RelTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RelTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RelTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RelTable))
        return static_cast<void*>(const_cast< RelTable*>(this));
    return MyTable::qt_metacast(_clname);
}

int RelTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_ClassInstanceDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,
      30,   20,   20,   20, 0x09,
      39,   20,   20,   20, 0x09,
      58,   20,   20,   20, 0x09,
      76,   20,   20,   20, 0x09,
      89,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ClassInstanceDialog[] = {
    "ClassInstanceDialog\0\0polish()\0accept()\0"
    "edit_description()\0type_changed(int)\0"
    "menu_class()\0update_all_tabs(QWidget*)\0"
};

void ClassInstanceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassInstanceDialog *_t = static_cast<ClassInstanceDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        case 3: _t->type_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->menu_class(); break;
        case 5: _t->update_all_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClassInstanceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassInstanceDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ClassInstanceDialog,
      qt_meta_data_ClassInstanceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassInstanceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassInstanceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassInstanceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassInstanceDialog))
        return static_cast<void*>(const_cast< ClassInstanceDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ClassInstanceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
