/****************************************************************************
** Meta object code from reading C++ file 'ConstraintCanvas.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ConstraintCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConstraintCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConstraintCanvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConstraintCanvas[] = {
    "ConstraintCanvas\0\0update()\0"
};

void ConstraintCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConstraintCanvas *_t = static_cast<ConstraintCanvas *>(_o);
        switch (_id) {
        case 0: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConstraintCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConstraintCanvas::staticMetaObject = {
    { &NoteCanvas::staticMetaObject, qt_meta_stringdata_ConstraintCanvas,
      qt_meta_data_ConstraintCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConstraintCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConstraintCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConstraintCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConstraintCanvas))
        return static_cast<void*>(const_cast< ConstraintCanvas*>(this));
    return NoteCanvas::qt_metacast(_clname);
}

int ConstraintCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteCanvas::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
