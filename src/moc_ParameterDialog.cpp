/****************************************************************************
** Meta object code from reading C++ file 'ParameterDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ParameterDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParameterDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParameterDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
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
      66,   16,   16,   16, 0x09,
      87,   16,   16,   16, 0x09,
     108,   16,   16,   16, 0x09,
     130,   16,   16,   16, 0x09,
     142,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ParameterDialog[] = {
    "ParameterDialog\0\0polish()\0accept()\0"
    "edit_init()\0edit_description()\0"
    "edit_uml_selection()\0edit_cpp_selection()\0"
    "edit_java_selection()\0menu_type()\0"
    "change_tabs(QWidget*)\0"
};

void ParameterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParameterDialog *_t = static_cast<ParameterDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_init(); break;
        case 3: _t->edit_description(); break;
        case 4: _t->edit_uml_selection(); break;
        case 5: _t->edit_cpp_selection(); break;
        case 6: _t->edit_java_selection(); break;
        case 7: _t->menu_type(); break;
        case 8: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParameterDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParameterDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ParameterDialog,
      qt_meta_data_ParameterDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParameterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParameterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParameterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParameterDialog))
        return static_cast<void*>(const_cast< ParameterDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ParameterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
