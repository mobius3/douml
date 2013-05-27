/****************************************************************************
** Meta object code from reading C++ file 'DiagramView.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/DiagramView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiagramView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DiagramView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x09,
      41,   12,   12,   12, 0x08,
      69,   12,   12,   12, 0x08,
      91,   12,   12,   12, 0x08,
     113,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DiagramView[] = {
    "DiagramView\0\0e\0keyPressEvent(QKeyEvent*)\0"
    "keyReleaseEvent(QKeyEvent*)\0"
    "optimal_window_size()\0restore_window_size()\0"
    "update()\0"
};

void DiagramView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DiagramView *_t = static_cast<DiagramView *>(_o);
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->optimal_window_size(); break;
        case 3: _t->restore_window_size(); break;
        case 4: _t->update(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DiagramView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DiagramView::staticMetaObject = {
    { &Q3CanvasView::staticMetaObject, qt_meta_stringdata_DiagramView,
      qt_meta_data_DiagramView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DiagramView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DiagramView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DiagramView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DiagramView))
        return static_cast<void*>(const_cast< DiagramView*>(this));
    return Q3CanvasView::qt_metacast(_clname);
}

int DiagramView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3CanvasView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
