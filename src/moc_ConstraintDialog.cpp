/****************************************************************************
** Meta object code from reading C++ file 'ConstraintDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ConstraintDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConstraintDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConstraintDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      29,   17,   17,   17, 0x09,
      40,   17,   17,   17, 0x09,
      57,   17,   17,   17, 0x09,
      66,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ConstraintDialog[] = {
    "ConstraintDialog\0\0show_all()\0hide_all()\0"
    "hide_inherited()\0accept()\0polish()\0"
};

void ConstraintDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConstraintDialog *_t = static_cast<ConstraintDialog *>(_o);
        switch (_id) {
        case 0: _t->show_all(); break;
        case 1: _t->hide_all(); break;
        case 2: _t->hide_inherited(); break;
        case 3: _t->accept(); break;
        case 4: _t->polish(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConstraintDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConstraintDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConstraintDialog,
      qt_meta_data_ConstraintDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConstraintDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConstraintDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConstraintDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConstraintDialog))
        return static_cast<void*>(const_cast< ConstraintDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConstraintDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_ConstraintTable[] = {

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
      41,   17,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ConstraintTable[] = {
    "ConstraintTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
};

void ConstraintTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConstraintTable *_t = static_cast<ConstraintTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConstraintTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConstraintTable::staticMetaObject = {
    { &Q3Table::staticMetaObject, qt_meta_stringdata_ConstraintTable,
      qt_meta_data_ConstraintTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConstraintTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConstraintTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConstraintTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConstraintTable))
        return static_cast<void*>(const_cast< ConstraintTable*>(this));
    return Q3Table::qt_metacast(_clname);
}

int ConstraintTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3Table::qt_metacall(_c, _id, _a);
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
