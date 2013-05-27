/****************************************************************************
** Meta object code from reading C++ file 'GenerationSettingsBuiltinTable.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/GenerationSettingsBuiltinTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerationSettingsBuiltinTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BuiltinTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      31,   13,   13,   13, 0x0a,
      44,   13,   13,   13, 0x0a,
      58,   13,   13,   13, 0x0a,
      70,   13,   13,   13, 0x0a,
      81,   13,   13,   13, 0x0a,
     108,   13,   13,   13, 0x0a,
     135,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BuiltinTable[] = {
    "BuiltinTable\0\0OnInsertNewRow()\0"
    "OnPasteRow()\0OnDeleteRow()\0OnCopyRow()\0"
    "OnCutRow()\0OnCallRowMenu(QModelIndex)\0"
    "OnSetParameterVisibility()\0"
    "OnFilterTable(QString)\0"
};

void BuiltinTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BuiltinTable *_t = static_cast<BuiltinTable *>(_o);
        switch (_id) {
        case 0: _t->OnInsertNewRow(); break;
        case 1: _t->OnPasteRow(); break;
        case 2: _t->OnDeleteRow(); break;
        case 3: _t->OnCopyRow(); break;
        case 4: _t->OnCutRow(); break;
        case 5: _t->OnCallRowMenu((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->OnSetParameterVisibility(); break;
        case 7: _t->OnFilterTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BuiltinTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BuiltinTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BuiltinTable,
      qt_meta_data_BuiltinTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BuiltinTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BuiltinTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BuiltinTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BuiltinTable))
        return static_cast<void*>(const_cast< BuiltinTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int BuiltinTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
