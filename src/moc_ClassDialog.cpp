/****************************************************************************
** Meta object code from reading C++ file 'ClassDialog.h'
**
** Created: Sat May 25 00:24:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ClassDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      22,   12,   12,   12, 0x09,
      31,   12,   12,   12, 0x09,
      53,   12,   12,   12, 0x09,
      72,   12,   12,   12, 0x09,
      90,   12,   12,   12, 0x09,
     121,   12,   12,   12, 0x09,
     135,   12,   12,   12, 0x09,
     156,   12,   12,   12, 0x09,
     176,   12,   12,   12, 0x09,
     202,   12,   12,   12, 0x09,
     220,   12,   12,   12, 0x09,
     239,   12,   12,   12, 0x09,
     259,   12,   12,   12, 0x09,
     278,   12,   12,   12, 0x09,
     298,   12,   12,   12, 0x09,
     319,   12,   12,   12, 0x09,
     342,   12,   12,   12, 0x09,
     360,   12,   12,   12, 0x09,
     379,   12,   12,   12, 0x09,
     399,   12,   12,   12, 0x09,
     420,   12,   12,   12, 0x09,
     442,   12,   12,   12, 0x09,
     465,   12,   12,   12, 0x09,
     483,   12,   12,   12, 0x09,
     502,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ClassDialog[] = {
    "ClassDialog\0\0polish()\0accept()\0"
    "default_description()\0edit_description()\0"
    "edit_constraint()\0edStereotypeActivated(QString)\0"
    "icon_browse()\0icon_root_relative()\0"
    "icon_prj_relative()\0update_all_tabs(QWidget*)\0"
    "cpp_update_decl()\0cpp_default_decl()\0"
    "cpp_unmapped_decl()\0java_update_decl()\0"
    "java_default_decl()\0java_unmapped_decl()\0"
    "java_edit_annotation()\0php_update_decl()\0"
    "php_default_decl()\0php_unmapped_decl()\0"
    "python_update_decl()\0python_default_decl()\0"
    "python_unmapped_decl()\0idl_update_decl()\0"
    "idl_default_decl()\0idl_unmapped_decl()\0"
};

void ClassDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassDialog *_t = static_cast<ClassDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->default_description(); break;
        case 3: _t->edit_description(); break;
        case 4: _t->edit_constraint(); break;
        case 5: _t->edStereotypeActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->icon_browse(); break;
        case 7: _t->icon_root_relative(); break;
        case 8: _t->icon_prj_relative(); break;
        case 9: _t->update_all_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 10: _t->cpp_update_decl(); break;
        case 11: _t->cpp_default_decl(); break;
        case 12: _t->cpp_unmapped_decl(); break;
        case 13: _t->java_update_decl(); break;
        case 14: _t->java_default_decl(); break;
        case 15: _t->java_unmapped_decl(); break;
        case 16: _t->java_edit_annotation(); break;
        case 17: _t->php_update_decl(); break;
        case 18: _t->php_default_decl(); break;
        case 19: _t->php_unmapped_decl(); break;
        case 20: _t->python_update_decl(); break;
        case 21: _t->python_default_decl(); break;
        case 22: _t->python_unmapped_decl(); break;
        case 23: _t->idl_update_decl(); break;
        case 24: _t->idl_default_decl(); break;
        case 25: _t->idl_unmapped_decl(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClassDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassDialog::staticMetaObject = {
    { &EdgeMenuDialog::staticMetaObject, qt_meta_stringdata_ClassDialog,
      qt_meta_data_ClassDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassDialog))
        return static_cast<void*>(const_cast< ClassDialog*>(this));
    return EdgeMenuDialog::qt_metacast(_clname);
}

int ClassDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EdgeMenuDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
static const uint qt_meta_data_FormalParamsTable[] = {

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
      43,   19,   18,   18, 0x09,
      86,   78,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FormalParamsTable[] = {
    "FormalParamsTable\0\0row,col,button,mousePos\0"
    "button_pressed(int,int,int,QPoint)\0"
    "row,col\0value_changed(int,int)\0"
};

void FormalParamsTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormalParamsTable *_t = static_cast<FormalParamsTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        case 1: _t->value_changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormalParamsTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormalParamsTable::staticMetaObject = {
    { &MyTable::staticMetaObject, qt_meta_stringdata_FormalParamsTable,
      qt_meta_data_FormalParamsTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormalParamsTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormalParamsTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormalParamsTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormalParamsTable))
        return static_cast<void*>(const_cast< FormalParamsTable*>(this));
    return MyTable::qt_metacast(_clname);
}

int FormalParamsTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_ApplicableOnTable[] = {

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
      29,   19,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ApplicableOnTable[] = {
    "ApplicableOnTable\0\0row,col,,\0"
    "button_pressed(int,int,int,QPoint)\0"
};

void ApplicableOnTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplicableOnTable *_t = static_cast<ApplicableOnTable *>(_o);
        switch (_id) {
        case 0: _t->button_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplicableOnTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplicableOnTable::staticMetaObject = {
    { &MyTable::staticMetaObject, qt_meta_stringdata_ApplicableOnTable,
      qt_meta_data_ApplicableOnTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicableOnTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicableOnTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicableOnTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicableOnTable))
        return static_cast<void*>(const_cast< ApplicableOnTable*>(this));
    return MyTable::qt_metacast(_clname);
}

int ApplicableOnTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
