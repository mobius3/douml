/****************************************************************************
** Meta object code from reading C++ file 'RelationCanvas.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/RelationCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RelationCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RelationCanvas[] = {

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
      16,   15,   15,   15, 0x08,
      27,   15,   15,   15, 0x08,
      46,   15,   15,   15, 0x08,
      56,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RelationCanvas[] = {
    "RelationCanvas\0\0modified()\0"
    "actuals_modified()\0deleted()\0"
    "drawing_settings_modified()\0"
};

void RelationCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RelationCanvas *_t = static_cast<RelationCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->actuals_modified(); break;
        case 2: _t->deleted(); break;
        case 3: _t->drawing_settings_modified(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RelationCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RelationCanvas::staticMetaObject = {
    { &ArrowCanvas::staticMetaObject, qt_meta_stringdata_RelationCanvas,
      qt_meta_data_RelationCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RelationCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RelationCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RelationCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RelationCanvas))
        return static_cast<void*>(const_cast< RelationCanvas*>(this));
    return ArrowCanvas::qt_metacast(_clname);
}

int RelationCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArrowCanvas::qt_metacall(_c, _id, _a);
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
