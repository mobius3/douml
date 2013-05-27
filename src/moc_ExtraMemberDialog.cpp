/****************************************************************************
** Meta object code from reading C++ file 'ExtraMemberDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ExtraMemberDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExtraMemberDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExtraMemberDialog[] = {

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
      19,   18,   18,   18, 0x09,
      28,   18,   18,   18, 0x09,
      37,   18,   18,   18, 0x09,
      53,   18,   18,   18, 0x09,
      68,   18,   18,   18, 0x09,
      85,   18,   18,   18, 0x09,
     101,   18,   18,   18, 0x09,
     120,   18,   18,   18, 0x09,
     136,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ExtraMemberDialog[] = {
    "ExtraMemberDialog\0\0polish()\0accept()\0"
    "edit_cpp_decl()\0edit_cpp_def()\0"
    "edit_java_decl()\0edit_php_decl()\0"
    "edit_python_decl()\0edit_idl_decl()\0"
    "edit_description()\0"
};

void ExtraMemberDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExtraMemberDialog *_t = static_cast<ExtraMemberDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_cpp_decl(); break;
        case 3: _t->edit_cpp_def(); break;
        case 4: _t->edit_java_decl(); break;
        case 5: _t->edit_php_decl(); break;
        case 6: _t->edit_python_decl(); break;
        case 7: _t->edit_idl_decl(); break;
        case 8: _t->edit_description(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ExtraMemberDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExtraMemberDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ExtraMemberDialog,
      qt_meta_data_ExtraMemberDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExtraMemberDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExtraMemberDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExtraMemberDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExtraMemberDialog))
        return static_cast<void*>(const_cast< ExtraMemberDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ExtraMemberDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
