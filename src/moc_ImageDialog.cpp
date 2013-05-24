/****************************************************************************
** Meta object code from reading C++ file 'ImageDialog.h'
**
** Created: Fri May 24 23:48:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog/ImageDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      22,   12,   12,   12, 0x09,
      31,   12,   12,   12, 0x09,
      47,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ImageDialog[] = {
    "ImageDialog\0\0accept()\0browse()\0"
    "root_relative()\0prj_relative()\0"
};

void ImageDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageDialog *_t = static_cast<ImageDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->browse(); break;
        case 2: _t->root_relative(); break;
        case 3: _t->prj_relative(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ImageDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImageDialog,
      qt_meta_data_ImageDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageDialog))
        return static_cast<void*>(const_cast< ImageDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ImageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
