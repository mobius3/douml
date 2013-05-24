/****************************************************************************
** Meta object code from reading C++ file 'ClipboardManager.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "misc/ClipboardManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClipboardManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClipboardManager[] = {

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
      18,   17,   17,   17, 0x0a,
      38,   17,   17,   17, 0x0a,
      70,   17,   17,   17, 0x0a,
     104,   17,   17,   17, 0x0a,
     127,   17,   17,   17, 0x0a,
     154,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClipboardManager[] = {
    "ClipboardManager\0\0OnClipboardUpdate()\0"
    "OnPutItemIntoClipboard(QString)\0"
    "OnPutItemIntoClipboardRequested()\0"
    "OnClipboardRequested()\0"
    "OnMoreClipboardRequested()\0"
    "OnLessClipboardRequested()\0"
};

void ClipboardManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClipboardManager *_t = static_cast<ClipboardManager *>(_o);
        switch (_id) {
        case 0: _t->OnClipboardUpdate(); break;
        case 1: _t->OnPutItemIntoClipboard((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->OnPutItemIntoClipboardRequested(); break;
        case 3: _t->OnClipboardRequested(); break;
        case 4: _t->OnMoreClipboardRequested(); break;
        case 5: _t->OnLessClipboardRequested(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClipboardManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClipboardManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClipboardManager,
      qt_meta_data_ClipboardManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClipboardManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClipboardManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClipboardManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClipboardManager))
        return static_cast<void*>(const_cast< ClipboardManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ClipboardManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
