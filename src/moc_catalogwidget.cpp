/****************************************************************************
** Meta object code from reading C++ file 'catalogwidget.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/catalogwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'catalogwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CatalogWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      43,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   14,   14,   14, 0x0a,
      96,   14,   14,   14, 0x0a,
     123,   14,   14,   14, 0x0a,
     159,  154,   14,   14, 0x0a,
     196,   14,   14,   14, 0x0a,
     236,   14,   14,   14, 0x0a,
     261,   15,   14,   14, 0x0a,
     306,   14,   14,   14, 0x0a,
     342,   14,   14,   14, 0x0a,
     374,   14,   14,   14, 0x0a,
     403,   14,   14,   14, 0x0a,
     441,  435,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CatalogWidget[] = {
    "CatalogWidget\0\0,\0markedRemove(QString,int)\0"
    "allMarkedRemove()\0OnPerformVisitedFiltering(QString)\0"
    "OnPerformMarkedFiltering()\0"
    "OnPerformFavouritesFiltering()\0item\0"
    "OnUpdateVisitedView(Q3ListViewItem*)\0"
    "OnUpdateMarkedView(QList<BrowserNode*>)\0"
    "OnUpdateFavoutitesView()\0"
    "OnSelectedInVisited(QModelIndex,QModelIndex)\0"
    "OnRemoveCurrentItemFromFavourites()\0"
    "OnRemoveCurrentItemFromMarked()\0"
    "OnRemoveAllItemsFromMarked()\0"
    "OnFavouritesContextMenu(QPoint)\0point\0"
    "OnMarkedContextMenu(QPoint)\0"
};

void CatalogWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CatalogWidget *_t = static_cast<CatalogWidget *>(_o);
        switch (_id) {
        case 0: _t->markedRemove((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->allMarkedRemove(); break;
        case 2: _t->OnPerformVisitedFiltering((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->OnPerformMarkedFiltering(); break;
        case 4: _t->OnPerformFavouritesFiltering(); break;
        case 5: _t->OnUpdateVisitedView((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 6: _t->OnUpdateMarkedView((*reinterpret_cast< QList<BrowserNode*>(*)>(_a[1]))); break;
        case 7: _t->OnUpdateFavoutitesView(); break;
        case 8: _t->OnSelectedInVisited((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 9: _t->OnRemoveCurrentItemFromFavourites(); break;
        case 10: _t->OnRemoveCurrentItemFromMarked(); break;
        case 11: _t->OnRemoveAllItemsFromMarked(); break;
        case 12: _t->OnFavouritesContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 13: _t->OnMarkedContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CatalogWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CatalogWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CatalogWidget,
      qt_meta_data_CatalogWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CatalogWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CatalogWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CatalogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CatalogWidget))
        return static_cast<void*>(const_cast< CatalogWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CatalogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void CatalogWidget::markedRemove(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CatalogWidget::allMarkedRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
