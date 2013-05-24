/****************************************************************************
** Meta object code from reading C++ file 'ActivityPartitionDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ActivityPartitionDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivityPartitionDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActivityPartitionDialog[] = {

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
      25,   24,   24,   24, 0x09,
      34,   24,   24,   24, 0x09,
      43,   24,   24,   24, 0x09,
      62,   24,   24,   24, 0x09,
      80,   24,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ActivityPartitionDialog[] = {
    "ActivityPartitionDialog\0\0polish()\0"
    "accept()\0edit_description()\0"
    "menu_represents()\0change_tabs(QWidget*)\0"
};

void ActivityPartitionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActivityPartitionDialog *_t = static_cast<ActivityPartitionDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        case 3: _t->menu_represents(); break;
        case 4: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ActivityPartitionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActivityPartitionDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ActivityPartitionDialog,
      qt_meta_data_ActivityPartitionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActivityPartitionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActivityPartitionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActivityPartitionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityPartitionDialog))
        return static_cast<void*>(const_cast< ActivityPartitionDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ActivityPartitionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
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
