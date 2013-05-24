/****************************************************************************
** Meta object code from reading C++ file 'ReferenceDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ReferenceDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReferenceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReferenceDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x09,
      26,   16,   16,   16, 0x09,
      36,   16,   16,   16, 0x09,
      45,   16,   16,   16, 0x09,
      59,   16,   16,   16, 0x09,
      73,   16,   16,   16, 0x09,
      85,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ReferenceDialog[] = {
    "ReferenceDialog\0\0polish()\0compute()\0"
    "select()\0selected(int)\0mark_unmark()\0"
    "mark_them()\0unmark_all()\0"
};

void ReferenceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReferenceDialog *_t = static_cast<ReferenceDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->compute(); break;
        case 2: _t->select(); break;
        case 3: _t->selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->mark_unmark(); break;
        case 5: _t->mark_them(); break;
        case 6: _t->unmark_all(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReferenceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReferenceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReferenceDialog,
      qt_meta_data_ReferenceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReferenceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReferenceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReferenceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReferenceDialog))
        return static_cast<void*>(const_cast< ReferenceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReferenceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
