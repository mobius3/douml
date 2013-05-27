/****************************************************************************
** Meta object code from reading C++ file 'ArrowCanvas.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ArrowCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArrowCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ArrowCanvas[] = {

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
      13,   12,   12,   12, 0x09,
      24,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ArrowCanvas[] = {
    "ArrowCanvas\0\0modified()\0"
    "drawing_settings_modified()\0"
};

void ArrowCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ArrowCanvas *_t = static_cast<ArrowCanvas *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->drawing_settings_modified(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ArrowCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ArrowCanvas::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ArrowCanvas,
      qt_meta_data_ArrowCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ArrowCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ArrowCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ArrowCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ArrowCanvas))
        return static_cast<void*>(const_cast< ArrowCanvas*>(this));
    if (!strcmp(_clname, "Q3CanvasPolygon"))
        return static_cast< Q3CanvasPolygon*>(const_cast< ArrowCanvas*>(this));
    if (!strcmp(_clname, "DiagramItem"))
        return static_cast< DiagramItem*>(const_cast< ArrowCanvas*>(this));
    return QObject::qt_metacast(_clname);
}

int ArrowCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
