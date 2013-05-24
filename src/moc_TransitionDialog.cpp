/****************************************************************************
** Meta object code from reading C++ file 'TransitionDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/TransitionDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransitionDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransitionDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      27,   17,   17,   17, 0x09,
      36,   17,   17,   17, 0x09,
      55,   17,   17,   17, 0x09,
      74,   17,   17,   17, 0x09,
      91,   17,   17,   17, 0x09,
     107,   17,   17,   17, 0x09,
     126,   17,   17,   17, 0x09,
     143,   17,   17,   17, 0x09,
     159,   17,   17,   17, 0x09,
     179,   17,   17,   17, 0x09,
     197,   17,   17,   17, 0x09,
     214,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TransitionDialog[] = {
    "TransitionDialog\0\0polish()\0accept()\0"
    "edit_description()\0edit_uml_trigger()\0"
    "edit_uml_guard()\0edit_uml_expr()\0"
    "edit_cpp_trigger()\0edit_cpp_guard()\0"
    "edit_cpp_expr()\0edit_java_trigger()\0"
    "edit_java_guard()\0edit_java_expr()\0"
    "change_tabs(QWidget*)\0"
};

void TransitionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TransitionDialog *_t = static_cast<TransitionDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        case 3: _t->edit_uml_trigger(); break;
        case 4: _t->edit_uml_guard(); break;
        case 5: _t->edit_uml_expr(); break;
        case 6: _t->edit_cpp_trigger(); break;
        case 7: _t->edit_cpp_guard(); break;
        case 8: _t->edit_cpp_expr(); break;
        case 9: _t->edit_java_trigger(); break;
        case 10: _t->edit_java_guard(); break;
        case 11: _t->edit_java_expr(); break;
        case 12: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TransitionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TransitionDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_TransitionDialog,
      qt_meta_data_TransitionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransitionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransitionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransitionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransitionDialog))
        return static_cast<void*>(const_cast< TransitionDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int TransitionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
