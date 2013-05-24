/****************************************************************************
** Meta object code from reading C++ file 'EnvDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/EnvDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EnvDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EnvDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      20,   10,   10,   10, 0x08,
      29,   10,   10,   10, 0x08,
      42,   10,   10,   10, 0x08,
      61,   10,   10,   10, 0x08,
      79,   10,   10,   10, 0x08,
      95,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EnvDialog[] = {
    "EnvDialog\0\0accept()\0reject()\0doc_browse()\0"
    "navigator_browse()\0template_browse()\0"
    "editor_browse()\0lang_browse()\0"
};

void EnvDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EnvDialog *_t = static_cast<EnvDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->doc_browse(); break;
        case 3: _t->navigator_browse(); break;
        case 4: _t->template_browse(); break;
        case 5: _t->editor_browse(); break;
        case 6: _t->lang_browse(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData EnvDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EnvDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EnvDialog,
      qt_meta_data_EnvDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EnvDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EnvDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EnvDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EnvDialog))
        return static_cast<void*>(const_cast< EnvDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int EnvDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
