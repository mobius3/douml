/****************************************************************************
** Meta object code from reading C++ file 'DeploymentNodeCanvas.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/DeploymentNodeCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeploymentNodeCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeploymentNodeCanvas[] = {

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
      22,   21,   21,   21, 0x08,
      33,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DeploymentNodeCanvas[] = {
    "DeploymentNodeCanvas\0\0modified()\0"
    "deleted()\0"
};

void DeploymentNodeCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeploymentNodeCanvas *_t = static_cast<DeploymentNodeCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->deleted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DeploymentNodeCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeploymentNodeCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DeploymentNodeCanvas,
      qt_meta_data_DeploymentNodeCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeploymentNodeCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeploymentNodeCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeploymentNodeCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeploymentNodeCanvas))
        return static_cast<void*>(const_cast< DeploymentNodeCanvas*>(this));
    if (!strcmp(_clname, "DiagramCanvas"))
        return static_cast< DiagramCanvas*>(const_cast< DeploymentNodeCanvas*>(this));
    if (!strcmp(_clname, "Instance"))
        return static_cast< Instance*>(const_cast< DeploymentNodeCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int DeploymentNodeCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
