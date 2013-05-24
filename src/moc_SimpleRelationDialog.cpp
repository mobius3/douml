/****************************************************************************
** Meta object code from reading C++ file 'SimpleRelationDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/SimpleRelationDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleRelationDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleRelationDialog[] = {

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
      22,   21,   21,   21, 0x09,
      31,   21,   21,   21, 0x09,
      40,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SimpleRelationDialog[] = {
    "SimpleRelationDialog\0\0polish()\0accept()\0"
    "edit_description()\0"
};

void SimpleRelationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimpleRelationDialog *_t = static_cast<SimpleRelationDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SimpleRelationDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimpleRelationDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_SimpleRelationDialog,
      qt_meta_data_SimpleRelationDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleRelationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleRelationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleRelationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleRelationDialog))
        return static_cast<void*>(const_cast< SimpleRelationDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int SimpleRelationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
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
