/****************************************************************************
** Meta object code from reading C++ file 'GreetingsDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/GreetingsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GreetingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GreetingsDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x09,
      44,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_GreetingsDialog[] = {
    "GreetingsDialog\0\0e\0closeEvent(QCloseEvent*)\0"
    "valid_ok()\0"
};

void GreetingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GreetingsDialog *_t = static_cast<GreetingsDialog *>(_o);
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->valid_ok(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GreetingsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GreetingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GreetingsDialog,
      qt_meta_data_GreetingsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GreetingsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GreetingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GreetingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GreetingsDialog))
        return static_cast<void*>(const_cast< GreetingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GreetingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
