/****************************************************************************
** Meta object code from reading C++ file 'ActivityActionDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ActivityActionDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivityActionDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OpaqueDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,
      25,   13,   13,   13, 0x09,
      36,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_OpaqueDialog[] = {
    "OpaqueDialog\0\0edit_ocl()\0edit_cpp()\0"
    "edit_java()\0"
};

void OpaqueDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OpaqueDialog *_t = static_cast<OpaqueDialog *>(_o);
        switch (_id) {
        case 0: _t->edit_ocl(); break;
        case 1: _t->edit_cpp(); break;
        case 2: _t->edit_java(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OpaqueDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OpaqueDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OpaqueDialog,
      qt_meta_data_OpaqueDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OpaqueDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OpaqueDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OpaqueDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OpaqueDialog))
        return static_cast<void*>(const_cast< OpaqueDialog*>(this));
    if (!strcmp(_clname, "AnyActionDialog"))
        return static_cast< AnyActionDialog*>(const_cast< OpaqueDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int OpaqueDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_AccessVariableValueDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x09,
      45,   26,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AccessVariableValueDialog[] = {
    "AccessVariableValueDialog\0\0classChanged(int)\0"
    "menu_var()\0"
};

void AccessVariableValueDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AccessVariableValueDialog *_t = static_cast<AccessVariableValueDialog *>(_o);
        switch (_id) {
        case 0: _t->classChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->menu_var(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AccessVariableValueDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AccessVariableValueDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AccessVariableValueDialog,
      qt_meta_data_AccessVariableValueDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AccessVariableValueDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AccessVariableValueDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AccessVariableValueDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AccessVariableValueDialog))
        return static_cast<void*>(const_cast< AccessVariableValueDialog*>(this));
    if (!strcmp(_clname, "AnyActionDialog"))
        return static_cast< AnyActionDialog*>(const_cast< AccessVariableValueDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int AccessVariableValueDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CallBehaviorDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CallBehaviorDialog[] = {
    "CallBehaviorDialog\0\0menu_beh()\0"
};

void CallBehaviorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CallBehaviorDialog *_t = static_cast<CallBehaviorDialog *>(_o);
        switch (_id) {
        case 0: _t->menu_beh(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CallBehaviorDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CallBehaviorDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CallBehaviorDialog,
      qt_meta_data_CallBehaviorDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CallBehaviorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CallBehaviorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CallBehaviorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CallBehaviorDialog))
        return static_cast<void*>(const_cast< CallBehaviorDialog*>(this));
    if (!strcmp(_clname, "WithBehaviorDialog"))
        return static_cast< WithBehaviorDialog*>(const_cast< CallBehaviorDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int CallBehaviorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_CallOperationDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,
      39,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CallOperationDialog[] = {
    "CallOperationDialog\0\0classChanged(int)\0"
    "menu_oper()\0"
};

void CallOperationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CallOperationDialog *_t = static_cast<CallOperationDialog *>(_o);
        switch (_id) {
        case 0: _t->classChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->menu_oper(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CallOperationDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CallOperationDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CallOperationDialog,
      qt_meta_data_CallOperationDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CallOperationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CallOperationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CallOperationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CallOperationDialog))
        return static_cast<void*>(const_cast< CallOperationDialog*>(this));
    if (!strcmp(_clname, "AnyActionDialog"))
        return static_cast< AnyActionDialog*>(const_cast< CallOperationDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int CallOperationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_ValueSpecificationDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x09,
      37,   25,   25,   25, 0x09,
      48,   25,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ValueSpecificationDialog[] = {
    "ValueSpecificationDialog\0\0edit_ocl()\0"
    "edit_cpp()\0edit_java()\0"
};

void ValueSpecificationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ValueSpecificationDialog *_t = static_cast<ValueSpecificationDialog *>(_o);
        switch (_id) {
        case 0: _t->edit_ocl(); break;
        case 1: _t->edit_cpp(); break;
        case 2: _t->edit_java(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ValueSpecificationDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ValueSpecificationDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ValueSpecificationDialog,
      qt_meta_data_ValueSpecificationDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ValueSpecificationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ValueSpecificationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ValueSpecificationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ValueSpecificationDialog))
        return static_cast<void*>(const_cast< ValueSpecificationDialog*>(this));
    if (!strcmp(_clname, "AnyActionDialog"))
        return static_cast< AnyActionDialog*>(const_cast< ValueSpecificationDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int ValueSpecificationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_ReduceDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReduceDialog[] = {
    "ReduceDialog\0\0menu_beh()\0"
};

void ReduceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReduceDialog *_t = static_cast<ReduceDialog *>(_o);
        switch (_id) {
        case 0: _t->menu_beh(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ReduceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReduceDialog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReduceDialog,
      qt_meta_data_ReduceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReduceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReduceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReduceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReduceDialog))
        return static_cast<void*>(const_cast< ReduceDialog*>(this));
    if (!strcmp(_clname, "WithBehaviorDialog"))
        return static_cast< WithBehaviorDialog*>(const_cast< ReduceDialog*>(this));
    return QObject::qt_metacast(_clname);
}

int ReduceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ActivityActionDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x09,
      31,   21,   21,   21, 0x09,
      40,   21,   21,   21, 0x09,
      61,   21,   21,   21, 0x09,
      80,   21,   21,   21, 0x09,
      98,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ActivityActionDialog[] = {
    "ActivityActionDialog\0\0polish()\0accept()\0"
    "edTypeActivated(int)\0edit_description()\0"
    "edit_constraint()\0change_tabs(QWidget*)\0"
};

void ActivityActionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActivityActionDialog *_t = static_cast<ActivityActionDialog *>(_o);
        switch (_id) {
        case 0: _t->polish(); break;
        case 1: _t->accept(); break;
        case 2: _t->edTypeActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->edit_description(); break;
        case 4: _t->edit_constraint(); break;
        case 5: _t->change_tabs((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ActivityActionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActivityActionDialog::staticMetaObject = {
    { &Q3TabDialog::staticMetaObject, qt_meta_stringdata_ActivityActionDialog,
      qt_meta_data_ActivityActionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActivityActionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActivityActionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActivityActionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityActionDialog))
        return static_cast<void*>(const_cast< ActivityActionDialog*>(this));
    return Q3TabDialog::qt_metacast(_clname);
}

int ActivityActionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3TabDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
