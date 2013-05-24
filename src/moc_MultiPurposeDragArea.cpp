/****************************************************************************
** Meta object code from reading C++ file 'MultiPurposeDragArea.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CustomWidgets/MultiPurposeDragArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultiPurposeDragArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultiPurposeDragArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      43,   21,   21,   21, 0x05,
      66,   21,   21,   21, 0x05,
      78,   21,   21,   21, 0x05,
      88,   21,   21,   21, 0x05,
     111,   21,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MultiPurposeDragArea[] = {
    "MultiPurposeDragArea\0\0initiateMove(QPoint)\0"
    "initiateResize(QPoint)\0endResize()\0"
    "endMove()\0newCoordinates(QPoint)\0"
    "changeTab(int)\0"
};

void MultiPurposeDragArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultiPurposeDragArea *_t = static_cast<MultiPurposeDragArea *>(_o);
        switch (_id) {
        case 0: _t->initiateMove((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->initiateResize((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->endResize(); break;
        case 3: _t->endMove(); break;
        case 4: _t->newCoordinates((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->changeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultiPurposeDragArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultiPurposeDragArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MultiPurposeDragArea,
      qt_meta_data_MultiPurposeDragArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultiPurposeDragArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultiPurposeDragArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultiPurposeDragArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultiPurposeDragArea))
        return static_cast<void*>(const_cast< MultiPurposeDragArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int MultiPurposeDragArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MultiPurposeDragArea::initiateMove(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultiPurposeDragArea::initiateResize(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultiPurposeDragArea::endResize()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MultiPurposeDragArea::endMove()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MultiPurposeDragArea::newCoordinates(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MultiPurposeDragArea::changeTab(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
