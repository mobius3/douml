/****************************************************************************
** Meta object code from reading C++ file 'PackageDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/PackageDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PackageDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PackageDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      24,   14,   14,   14, 0x09,
      33,   14,   14,   14, 0x09,
      52,   14,   14,   14, 0x09,
      83,   14,   14,   14, 0x09,
      99,   14,   14,   14, 0x09,
     113,   14,   14,   14, 0x09,
     127,   14,   14,   14, 0x09,
     140,   14,   14,   14, 0x09,
     156,   14,   14,   14, 0x09,
     169,   14,   14,   14, 0x09,
     187,   14,   14,   14, 0x09,
     203,   14,   14,   14, 0x09,
     219,   14,   14,   14, 0x09,
     234,   14,   14,   14, 0x09,
     252,   14,   14,   14, 0x09,
     267,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PackageDialog[] = {
    "PackageDialog\0\0polish()\0accept()\0"
    "edit_description()\0edStereotypeActivated(QString)\0"
    "cppsrc_browse()\0cpph_browse()\0"
    "java_browse()\0php_browse()\0python_browse()\0"
    "idl_browse()\0cppsrc_relative()\0"
    "cpph_relative()\0java_relative()\0"
    "php_relative()\0python_relative()\0"
    "idl_relative()\0change_tabs(QWidget*)\0"
};

void PackageDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PackageDialog *_t = static_cast<PackageDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        case 3: _t->edStereotypeActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->cppsrc_browse(); break;
        case 5: _t->cpph_browse(); break;
        case 6: _t->java_browse(); break;
        case 7: _t->php_browse(); break;
        case 8: _t->python_browse(); break;
        case 9: _t->idl_browse(); break;
        case 10: _t->cppsrc_relative(); break;
        case 11: _t->cpph_relative(); break;
        case 12: _t->java_relative(); break;
        case 13: _t->php_relative(); break;
        case 14: _t->python_relative(); break;
        case 15: _t->idl_relative(); break;
        case 16: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PackageDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PackageDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_PackageDialog,
      qt_meta_data_PackageDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PackageDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PackageDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PackageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PackageDialog))
        return static_cast<void*>(const_cast< PackageDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int PackageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
