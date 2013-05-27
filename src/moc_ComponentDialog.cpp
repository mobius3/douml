/****************************************************************************
** Meta object code from reading C++ file 'ComponentDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ComponentDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComponentDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ComponentDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x09,
      26,   16,   16,   16, 0x09,
      35,   16,   16,   16, 0x09,
      57,   54,   16,   16, 0x09,
      95,   54,   16,   16, 0x09,
     133,   54,   16,   16, 0x09,
     171,   16,   16,   16, 0x09,
     185,   16,   16,   16, 0x09,
     201,   16,   16,   16, 0x09,
     215,   16,   16,   16, 0x09,
     231,   16,   16,   16, 0x09,
     245,   16,   16,   16, 0x09,
     261,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ComponentDialog[] = {
    "ComponentDialog\0\0polish()\0accept()\0"
    "edit_description()\0st\0"
    "rq_stereotypeFilterActivated(QString)\0"
    "pr_stereotypeFilterActivated(QString)\0"
    "rz_stereotypeFilterActivated(QString)\0"
    "require_cls()\0unrequire_cls()\0"
    "provide_cls()\0unprovide_cls()\0"
    "realize_cls()\0unrealize_cls()\0"
    "change_tabs(QWidget*)\0"
};

void ComponentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComponentDialog *_t = static_cast<ComponentDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edit_description(); break;
        case 3: _t->rq_stereotypeFilterActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->pr_stereotypeFilterActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->rz_stereotypeFilterActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->require_cls(); break;
        case 7: _t->unrequire_cls(); break;
        case 8: _t->provide_cls(); break;
        case 9: _t->unprovide_cls(); break;
        case 10: _t->realize_cls(); break;
        case 11: _t->unrealize_cls(); break;
        case 12: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ComponentDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ComponentDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ComponentDialog,
      qt_meta_data_ComponentDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ComponentDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ComponentDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ComponentDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ComponentDialog))
        return static_cast<void*>(const_cast< ComponentDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ComponentDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
