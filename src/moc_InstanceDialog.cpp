/****************************************************************************
** Meta object code from reading C++ file 'InstanceDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/InstanceDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstanceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InstanceDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      28,   15,   15,   15, 0x09,
      37,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_InstanceDialog[] = {
    "InstanceDialog\0\0menu_type()\0polish()\0"
    "accept()\0"
};

void InstanceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InstanceDialog *_t = static_cast<InstanceDialog *>(_o);
        switch (_id) {
        case 0: _t->menu_type(); break;
        case 1: _t->polish(); break;
        case 2: _t->accept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InstanceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InstanceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InstanceDialog,
      qt_meta_data_InstanceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InstanceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InstanceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InstanceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InstanceDialog))
        return static_cast<void*>(const_cast< InstanceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InstanceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
