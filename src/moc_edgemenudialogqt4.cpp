/****************************************************************************
** Meta object code from reading C++ file 'edgemenudialogqt4.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/edgemenudialogqt4.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edgemenudialogqt4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EdgeMenuDialogQt4[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      43,   18,   18,   18, 0x05,
      55,   18,   18,   18, 0x05,
      70,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   18,   18,   18, 0x0a,
     113,   18,   18,   18, 0x0a,
     137,   18,   18,   18, 0x0a,
     160,   18,   18,   18, 0x0a,
     185,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EdgeMenuDialogQt4[] = {
    "EdgeMenuDialogQt4\0\0edgeMenuRequested(uint)\0"
    "lostFocus()\0hideEdgeMenu()\0"
    "repositionMenu(QPoint)\0OnPickNextSibling()\0"
    "OnPickPreviousSibling()\0OnInitiateMove(QPoint)\0"
    "OnInitiateResize(QPoint)\0"
    "OnNewCoordinatesReceived(QPoint)\0"
};

void EdgeMenuDialogQt4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EdgeMenuDialogQt4 *_t = static_cast<EdgeMenuDialogQt4 *>(_o);
        switch (_id) {
        case 0: _t->edgeMenuRequested((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->lostFocus(); break;
        case 2: _t->hideEdgeMenu(); break;
        case 3: _t->repositionMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->OnPickNextSibling(); break;
        case 5: _t->OnPickPreviousSibling(); break;
        case 6: _t->OnInitiateMove((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 7: _t->OnInitiateResize((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 8: _t->OnNewCoordinatesReceived((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EdgeMenuDialogQt4::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EdgeMenuDialogQt4::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EdgeMenuDialogQt4,
      qt_meta_data_EdgeMenuDialogQt4, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EdgeMenuDialogQt4::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EdgeMenuDialogQt4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EdgeMenuDialogQt4::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdgeMenuDialogQt4))
        return static_cast<void*>(const_cast< EdgeMenuDialogQt4*>(this));
    if (!strcmp(_clname, "EdgeMenuDialogBase"))
        return static_cast< EdgeMenuDialogBase*>(const_cast< EdgeMenuDialogQt4*>(this));
    return QDialog::qt_metacast(_clname);
}

int EdgeMenuDialogQt4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EdgeMenuDialogQt4::edgeMenuRequested(uint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdgeMenuDialogQt4::lostFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EdgeMenuDialogQt4::hideEdgeMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void EdgeMenuDialogQt4::repositionMenu(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
