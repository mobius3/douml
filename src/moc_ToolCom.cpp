/****************************************************************************
** Meta object code from reading C++ file 'ToolCom.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tool/ToolCom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolCom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolCom[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      18,    8,    8,    8, 0x0a,
      38,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ToolCom[] = {
    "ToolCom\0\0closed()\0connexion_timeout()\0"
    "processFinished()\0"
};

void ToolCom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToolCom *_t = static_cast<ToolCom *>(_o);
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->connexion_timeout(); break;
        case 2: _t->processFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ToolCom::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ToolCom::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ToolCom,
      qt_meta_data_ToolCom, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolCom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolCom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolCom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolCom))
        return static_cast<void*>(const_cast< ToolCom*>(this));
    return QObject::qt_metacast(_clname);
}

int ToolCom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ToolCom::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
