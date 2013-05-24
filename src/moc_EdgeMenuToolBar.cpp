/****************************************************************************
** Meta object code from reading C++ file 'EdgeMenuToolBar.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CustomWidgets/EdgeMenuToolBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdgeMenuToolBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EdgeMenuToolBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   16,   16,   16, 0x0a,
      66,   16,   16,   16, 0x0a,
      91,   16,   16,   16, 0x0a,
     124,   16,   16,   16, 0x0a,
     138,   16,   16,   16, 0x0a,
     150,   16,   16,   16, 0x0a,
     173,   16,   16,   16, 0x0a,
     200,   16,   16,   16, 0x0a,
     227,   16,   16,   16, 0x0a,
     257,   16,   16,   16, 0x0a,
     277,   16,   16,   16, 0x0a,
     299,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EdgeMenuToolBar[] = {
    "EdgeMenuToolBar\0\0putIntoClipboard(QString)\0"
    "OnInitiateMove(QPoint)\0OnInitiateResize(QPoint)\0"
    "OnNewCoordinatesReceived(QPoint)\0"
    "OnEndResize()\0OnEndMove()\0"
    "OnClipboardRequested()\0"
    "OnMoreClipboardRequested()\0"
    "OnLessClipboardRequested()\0"
    "OnPutIntoClipboardRequested()\0"
    "OnDialogLostFocus()\0OnMenuHideRequested()\0"
    "OnMenuRepositionRequested(QPoint)\0"
};

void EdgeMenuToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EdgeMenuToolBar *_t = static_cast<EdgeMenuToolBar *>(_o);
        switch (_id) {
        case 0: _t->putIntoClipboard((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->OnInitiateMove((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->OnInitiateResize((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->OnNewCoordinatesReceived((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->OnEndResize(); break;
        case 5: _t->OnEndMove(); break;
        case 6: _t->OnClipboardRequested(); break;
        case 7: _t->OnMoreClipboardRequested(); break;
        case 8: _t->OnLessClipboardRequested(); break;
        case 9: _t->OnPutIntoClipboardRequested(); break;
        case 10: _t->OnDialogLostFocus(); break;
        case 11: _t->OnMenuHideRequested(); break;
        case 12: _t->OnMenuRepositionRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EdgeMenuToolBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EdgeMenuToolBar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_EdgeMenuToolBar,
      qt_meta_data_EdgeMenuToolBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EdgeMenuToolBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EdgeMenuToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EdgeMenuToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdgeMenuToolBar))
        return static_cast<void*>(const_cast< EdgeMenuToolBar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int EdgeMenuToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void EdgeMenuToolBar::putIntoClipboard(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
