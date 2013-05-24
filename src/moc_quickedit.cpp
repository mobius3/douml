/****************************************************************************
** Meta object code from reading C++ file 'quickedit.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CustomWidgets/quickedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quickedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QuickEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      33,   10,   10,   10, 0x0a,
      42,   10,   10,   10, 0x0a,
      59,   10,   10,   10, 0x0a,
      76,   10,   10,   10, 0x0a,
      93,   10,   10,   10, 0x0a,
     121,   10,   10,   10, 0x0a,
     144,   10,   10,   10, 0x0a,
     167,   10,   10,   10, 0x0a,
     194,   10,   10,   10, 0x0a,
     214,   10,   10,   10, 0x0a,
     235,   10,   10,   10, 0x0a,
     252,   10,   10,   10, 0x0a,
     275,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QuickEdit[] = {
    "QuickEdit\0\0OnContextMenu(QPoint)\0"
    "OnShow()\0OnAddParameter()\0OnAddOperation()\0"
    "OnAddAttribute()\0OnPerformFiltering(QString)\0"
    "OnDecreaseOpenLevels()\0OnIncreaseOpenLevels()\0"
    "OnChangeColumnVisibility()\0"
    "OnMoveMarkedAfter()\0OnMoveMarkedBefore()\0"
    "OnRefreshTable()\0OnCollapseExpandSelf()\0"
    "OnCollapseExpandParent()\0"
};

void QuickEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QuickEdit *_t = static_cast<QuickEdit *>(_o);
        switch (_id) {
        case 0: _t->OnContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->OnShow(); break;
        case 2: _t->OnAddParameter(); break;
        case 3: _t->OnAddOperation(); break;
        case 4: _t->OnAddAttribute(); break;
        case 5: _t->OnPerformFiltering((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->OnDecreaseOpenLevels(); break;
        case 7: _t->OnIncreaseOpenLevels(); break;
        case 8: _t->OnChangeColumnVisibility(); break;
        case 9: _t->OnMoveMarkedAfter(); break;
        case 10: _t->OnMoveMarkedBefore(); break;
        case 11: _t->OnRefreshTable(); break;
        case 12: _t->OnCollapseExpandSelf(); break;
        case 13: _t->OnCollapseExpandParent(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QuickEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QuickEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QuickEdit,
      qt_meta_data_QuickEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QuickEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QuickEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QuickEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QuickEdit))
        return static_cast<void*>(const_cast< QuickEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int QuickEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
