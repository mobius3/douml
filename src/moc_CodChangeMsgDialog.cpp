/****************************************************************************
** Meta object code from reading C++ file 'CodChangeMsgDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/CodChangeMsgDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CodChangeMsgDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CodChangeMsgDialog[] = {

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
      20,   19,   19,   19, 0x09,
      30,   19,   19,   19, 0x09,
      39,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CodChangeMsgDialog[] = {
    "CodChangeMsgDialog\0\0menu_op()\0polish()\0"
    "accept()\0"
};

void CodChangeMsgDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodChangeMsgDialog *_t = static_cast<CodChangeMsgDialog *>(_o);
        switch (_id) {
        case 0: _t->menu_op(); break;
        case 1: _t->polish(); break;
        case 2: _t->accept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CodChangeMsgDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodChangeMsgDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CodChangeMsgDialog,
      qt_meta_data_CodChangeMsgDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodChangeMsgDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodChangeMsgDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodChangeMsgDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodChangeMsgDialog))
        return static_cast<void*>(const_cast< CodChangeMsgDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CodChangeMsgDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
