/****************************************************************************
** Meta object code from reading C++ file 'ObjectLinkDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ObjectLinkDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ObjectLinkDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjectLinkDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      27,   17,   17,   17, 0x09,
      36,   17,   17,   17, 0x09,
      47,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ObjectLinkDialog[] = {
    "ObjectLinkDialog\0\0polish()\0accept()\0"
    "unselect()\0create()\0"
};

void ObjectLinkDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ObjectLinkDialog *_t = static_cast<ObjectLinkDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->unselect(); break;
        case 3: _t->create(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ObjectLinkDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ObjectLinkDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ObjectLinkDialog,
      qt_meta_data_ObjectLinkDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ObjectLinkDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ObjectLinkDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ObjectLinkDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectLinkDialog))
        return static_cast<void*>(const_cast< ObjectLinkDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ObjectLinkDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
