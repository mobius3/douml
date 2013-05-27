/****************************************************************************
** Meta object code from reading C++ file 'SourceDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/SourceDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SourceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NumberedMultiLineEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   23,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_NumberedMultiLineEdit[] = {
    "NumberedMultiLineEdit\0\0l,c\0"
    "cursorMoved(int,int)\0"
};

void NumberedMultiLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NumberedMultiLineEdit *_t = static_cast<NumberedMultiLineEdit *>(_o);
        switch (_id) {
        case 0: _t->cursorMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NumberedMultiLineEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NumberedMultiLineEdit::staticMetaObject = {
    { &MultiLineEdit::staticMetaObject, qt_meta_stringdata_NumberedMultiLineEdit,
      qt_meta_data_NumberedMultiLineEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NumberedMultiLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NumberedMultiLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NumberedMultiLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NumberedMultiLineEdit))
        return static_cast<void*>(const_cast< NumberedMultiLineEdit*>(this));
    return MultiLineEdit::qt_metacast(_clname);
}

int NumberedMultiLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MultiLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void NumberedMultiLineEdit::cursorMoved(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_SourceDialog[] = {

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
      14,   13,   13,   13, 0x09,
      25,   21,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SourceDialog[] = {
    "SourceDialog\0\0edit()\0l,c\0"
    "updateCursorPos(int,int)\0"
};

void SourceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SourceDialog *_t = static_cast<SourceDialog *>(_o);
        switch (_id) {
        case 0: _t->edit(); break;
        case 1: _t->updateCursorPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SourceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SourceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SourceDialog,
      qt_meta_data_SourceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SourceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SourceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SourceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SourceDialog))
        return static_cast<void*>(const_cast< SourceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SourceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
