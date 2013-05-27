/****************************************************************************
** Meta object code from reading C++ file 'CodSelfLinkCanvas.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/CodSelfLinkCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CodSelfLinkCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CodSelfLinkCanvas[] = {

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
      19,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CodSelfLinkCanvas[] = {
    "CodSelfLinkCanvas\0\0modified()\0"
};

void CodSelfLinkCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodSelfLinkCanvas *_t = static_cast<CodSelfLinkCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CodSelfLinkCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodSelfLinkCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CodSelfLinkCanvas,
      qt_meta_data_CodSelfLinkCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodSelfLinkCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodSelfLinkCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodSelfLinkCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodSelfLinkCanvas))
        return static_cast<void*>(const_cast< CodSelfLinkCanvas*>(this));
    if (!strcmp(_clname, "DiagramCanvas"))
        return static_cast< DiagramCanvas*>(const_cast< CodSelfLinkCanvas*>(this));
    if (!strcmp(_clname, "CodMsgSupport"))
        return static_cast< CodMsgSupport*>(const_cast< CodSelfLinkCanvas*>(this));
    if (!strcmp(_clname, "MultipleDependency<BasicData>"))
        return static_cast< MultipleDependency<BasicData>*>(const_cast< CodSelfLinkCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int CodSelfLinkCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
