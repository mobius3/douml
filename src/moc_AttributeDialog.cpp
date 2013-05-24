/****************************************************************************
** Meta object code from reading C++ file 'AttributeDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/AttributeDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AttributeDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AttributeDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x09,
      26,   16,   16,   16, 0x09,
      35,   16,   16,   16, 0x09,
      47,   16,   16,   16, 0x09,
      69,   16,   16,   16, 0x09,
      88,   16,   16,   16, 0x09,
     106,   16,   16,   16, 0x09,
     118,   16,   16,   16, 0x09,
     140,   16,   16,   16, 0x09,
     154,   16,   16,   16, 0x09,
     169,   16,   16,   16, 0x09,
     182,   16,   16,   16, 0x09,
     197,   16,   16,   16, 0x09,
     217,   16,   16,   16, 0x09,
     233,   16,   16,   16, 0x09,
     247,   16,   16,   16, 0x09,
     270,   16,   16,   16, 0x09,
     284,   16,   16,   16, 0x09,
     299,   16,   16,   16, 0x09,
     312,   16,   16,   16, 0x09,
     329,   16,   16,   16, 0x09,
     347,   16,   16,   16, 0x09,
     363,   16,   16,   16, 0x09,
     377,   16,   16,   16, 0x09,
     397,   16,   16,   16, 0x09,
     420,   16,   16,   16, 0x09,
     435,   16,   16,   16, 0x09,
     448,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AttributeDialog[] = {
    "AttributeDialog\0\0polish()\0accept()\0"
    "edit_init()\0default_description()\0"
    "edit_description()\0edit_constraint()\0"
    "menu_type()\0derived_changed(bool)\0"
    "cpp_default()\0cpp_unmapped()\0cpp_update()\0"
    "java_default()\0java_default_item()\0"
    "java_unmapped()\0java_update()\0"
    "java_edit_annotation()\0php_default()\0"
    "php_unmapped()\0php_update()\0"
    "python_default()\0python_unmapped()\0"
    "python_update()\0idl_default()\0"
    "idl_default_state()\0idl_default_constant()\0"
    "idl_unmapped()\0idl_update()\0"
    "update_all_tabs(QWidget*)\0"
};

void AttributeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AttributeDialog *_t = static_cast<AttributeDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_init(); break;
        case 3: _t->default_description(); break;
        case 4: _t->edit_description(); break;
        case 5: _t->edit_constraint(); break;
        case 6: _t->menu_type(); break;
        case 7: _t->derived_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->cpp_default(); break;
        case 9: _t->cpp_unmapped(); break;
        case 10: _t->cpp_update(); break;
        case 11: _t->java_default(); break;
        case 12: _t->java_default_item(); break;
        case 13: _t->java_unmapped(); break;
        case 14: _t->java_update(); break;
        case 15: _t->java_edit_annotation(); break;
        case 16: _t->php_default(); break;
        case 17: _t->php_unmapped(); break;
        case 18: _t->php_update(); break;
        case 19: _t->python_default(); break;
        case 20: _t->python_unmapped(); break;
        case 21: _t->python_update(); break;
        case 22: _t->idl_default(); break;
        case 23: _t->idl_default_state(); break;
        case 24: _t->idl_default_constant(); break;
        case 25: _t->idl_unmapped(); break;
        case 26: _t->idl_update(); break;
        case 27: _t->update_all_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AttributeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AttributeDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_AttributeDialog,
      qt_meta_data_AttributeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AttributeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AttributeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AttributeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AttributeDialog))
        return static_cast<void*>(const_cast< AttributeDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int AttributeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
