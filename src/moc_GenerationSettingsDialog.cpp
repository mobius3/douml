/****************************************************************************
** Meta object code from reading C++ file 'GenerationSettingsDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/GenerationSettingsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerationSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GenerationSettingsDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x09,
      35,   25,   25,   25, 0x09,
      44,   25,   25,   25, 0x09,
      53,   25,   25,   25, 0x09,
      70,   25,   25,   25, 0x09,
      88,   25,   25,   25, 0x09,
     105,   25,   25,   25, 0x09,
     125,   25,   25,   25, 0x09,
     142,   25,   25,   25, 0x09,
     157,   25,   25,   25, 0x09,
     173,   25,   25,   25, 0x09,
     188,   25,   25,   25, 0x09,
     206,   25,   25,   25, 0x09,
     221,   25,   25,   25, 0x09,
     248,   25,   25,   25, 0x09,
     275,   25,   25,   25, 0x09,
     301,   25,   25,   25, 0x09,
     327,   25,   25,   25, 0x09,
     349,   25,   25,   25, 0x09,
     371,   25,   25,   25, 0x09,
     394,   25,   25,   25, 0x09,
     417,   25,   25,   25, 0x09,
     439,   25,   25,   25, 0x09,
     461,   25,   25,   25, 0x09,
     486,   25,   25,   25, 0x09,
     511,   25,   25,   25, 0x09,
     533,   25,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_GenerationSettingsDialog[] = {
    "GenerationSettingsDialog\0\0polish()\0"
    "accept()\0reject()\0cpproot_browse()\0"
    "javaroot_browse()\0phproot_browse()\0"
    "pythonroot_browse()\0idlroot_browse()\0"
    "cpp_relative()\0java_relative()\0"
    "php_relative()\0python_relative()\0"
    "idl_relative()\0java_get_visi_changed(int)\0"
    "java_set_visi_changed(int)\0"
    "php_get_visi_changed(int)\0"
    "php_set_visi_changed(int)\0"
    "follow_cpp_get_name()\0follow_cpp_set_name()\0"
    "follow_java_get_name()\0follow_java_set_name()\0"
    "follow_php_get_name()\0follow_php_set_name()\0"
    "follow_python_get_name()\0"
    "follow_python_set_name()\0follow_idl_get_name()\0"
    "follow_idl_set_name()\0"
};

void GenerationSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GenerationSettingsDialog *_t = static_cast<GenerationSettingsDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->reject(); break;
        case 3: _t->cpproot_browse(); break;
        case 4: _t->javaroot_browse(); break;
        case 5: _t->phproot_browse(); break;
        case 6: _t->pythonroot_browse(); break;
        case 7: _t->idlroot_browse(); break;
        case 8: _t->cpp_relative(); break;
        case 9: _t->java_relative(); break;
        case 10: _t->php_relative(); break;
        case 11: _t->python_relative(); break;
        case 12: _t->idl_relative(); break;
        case 13: _t->java_get_visi_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->java_set_visi_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->php_get_visi_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->php_set_visi_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->follow_cpp_get_name(); break;
        case 18: _t->follow_cpp_set_name(); break;
        case 19: _t->follow_java_get_name(); break;
        case 20: _t->follow_java_set_name(); break;
        case 21: _t->follow_php_get_name(); break;
        case 22: _t->follow_php_set_name(); break;
        case 23: _t->follow_python_get_name(); break;
        case 24: _t->follow_python_set_name(); break;
        case 25: _t->follow_idl_get_name(); break;
        case 26: _t->follow_idl_set_name(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GenerationSettingsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GenerationSettingsDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_GenerationSettingsDialog,
      qt_meta_data_GenerationSettingsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GenerationSettingsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GenerationSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GenerationSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GenerationSettingsDialog))
        return static_cast<void*>(const_cast< GenerationSettingsDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int GenerationSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
