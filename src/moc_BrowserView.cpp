/****************************************************************************
** Meta object code from reading C++ file 'BrowserView.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/BrowserView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BrowserView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrowserView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   12,   12,   12, 0x09,
      72,   12,   12,   12, 0x09,
     102,   12,   12,   12, 0x09,
     131,   12,   12,   12, 0x09,
     140,  138,   12,   12, 0x09,
     179,  138,   12,   12, 0x09,
     210,  138,   12,   12, 0x09,
     247,  138,   12,   12, 0x09,
     285,  138,   12,   12, 0x09,
     325,   12,   12,   12, 0x0a,
     341,   12,   12,   12, 0x0a,
     358,   12,   12,   12, 0x0a,
     374,   12,   12,   12, 0x0a,
     393,   12,   12,   12, 0x0a,
     419,  409,   12,   12, 0x0a,
     445,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BrowserView[] = {
    "BrowserView\0\0marked_list(QList<BrowserNode*>)\0"
    "selected(Q3ListViewItem*)\0"
    "rightPressed(Q3ListViewItem*)\0"
    "doubleClick(Q3ListViewItem*)\0menu()\0"
    "e\0contentsDragMoveEvent(QDragMoveEvent*)\0"
    "contentsDropEvent(QDropEvent*)\0"
    "contentsMouseMoveEvent(QMouseEvent*)\0"
    "contentsMousePressEvent(QMouseEvent*)\0"
    "contentsMouseReleaseEvent(QMouseEvent*)\0"
    "OnGenerateCpp()\0OnGenerateJava()\0"
    "OnGeneratePhp()\0OnGeneratePython()\0"
    "OnGenerateIdl()\0name,type\0"
    "OnUnmarkItem(QString,int)\0OnUnmarkAll()\0"
};

void BrowserView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrowserView *_t = static_cast<BrowserView *>(_o);
        switch (_id) {
        case 0: _t->marked_list((*reinterpret_cast< QList<BrowserNode*>(*)>(_a[1]))); break;
        case 1: _t->selected((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 2: _t->rightPressed((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 3: _t->doubleClick((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 4: _t->menu(); break;
        case 5: _t->contentsDragMoveEvent((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 6: _t->contentsDropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 7: _t->contentsMouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->contentsMousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->contentsMouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 10: _t->OnGenerateCpp(); break;
        case 11: _t->OnGenerateJava(); break;
        case 12: _t->OnGeneratePhp(); break;
        case 13: _t->OnGeneratePython(); break;
        case 14: _t->OnGenerateIdl(); break;
        case 15: _t->OnUnmarkItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->OnUnmarkAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrowserView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrowserView::staticMetaObject = {
    { &Q3ListView::staticMetaObject, qt_meta_stringdata_BrowserView,
      qt_meta_data_BrowserView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrowserView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrowserView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrowserView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrowserView))
        return static_cast<void*>(const_cast< BrowserView*>(this));
    return Q3ListView::qt_metacast(_clname);
}

int BrowserView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3ListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void BrowserView::marked_list(QList<BrowserNode*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
