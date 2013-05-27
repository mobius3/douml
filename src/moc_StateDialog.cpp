/****************************************************************************
** Meta object code from reading C++ file 'StateDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/StateDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      22,   12,   12,   12, 0x09,
      31,   12,   12,   12, 0x09,
      52,   12,   12,   12, 0x09,
      69,   12,   12,   12, 0x09,
      88,   12,   12,   12, 0x09,
     105,   12,   12,   12, 0x09,
     121,   12,   12,   12, 0x09,
     141,   12,   12,   12, 0x09,
     158,   12,   12,   12, 0x09,
     174,   12,   12,   12, 0x09,
     194,   12,   12,   12, 0x09,
     212,   12,   12,   12, 0x09,
     229,   12,   12,   12, 0x09,
     250,   12,   12,   12, 0x09,
     272,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StateDialog[] = {
    "StateDialog\0\0polish()\0accept()\0"
    "menu_specification()\0menu_reference()\0"
    "edit_description()\0edit_uml_entry()\0"
    "edit_uml_exit()\0edit_uml_activity()\0"
    "edit_cpp_entry()\0edit_cpp_exit()\0"
    "edit_cpp_activity()\0edit_java_entry()\0"
    "edit_java_exit()\0edit_java_activity()\0"
    "change_tabs(QWidget*)\0ed_ref_activated(int)\0"
};

void StateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateDialog *_t = static_cast<StateDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->menu_specification(); break;
        case 3: _t->menu_reference(); break;
        case 4: _t->edit_description(); break;
        case 5: _t->edit_uml_entry(); break;
        case 6: _t->edit_uml_exit(); break;
        case 7: _t->edit_uml_activity(); break;
        case 8: _t->edit_cpp_entry(); break;
        case 9: _t->edit_cpp_exit(); break;
        case 10: _t->edit_cpp_activity(); break;
        case 11: _t->edit_java_entry(); break;
        case 12: _t->edit_java_exit(); break;
        case 13: _t->edit_java_activity(); break;
        case 14: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 15: _t->ed_ref_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StateDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_StateDialog,
      qt_meta_data_StateDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateDialog))
        return static_cast<void*>(const_cast< StateDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int StateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
