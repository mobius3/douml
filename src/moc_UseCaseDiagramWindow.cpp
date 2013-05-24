/****************************************************************************
** Meta object code from reading C++ file 'UseCaseDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/UseCaseDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UseCaseDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UseCaseDiagramWindow[] = {

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
      22,   21,   21,   21, 0x09,
      34,   21,   21,   21, 0x09,
      48,   21,   21,   21, 0x09,
      62,   21,   21,   21, 0x09,
      77,   21,   21,   21, 0x09,
      91,   21,   21,   21, 0x09,
     109,   21,   21,   21, 0x09,
     138,   21,   21,   21, 0x09,
     155,   21,   21,   21, 0x09,
     169,   21,   21,   21, 0x09,
     180,   21,   21,   21, 0x09,
     193,   21,   21,   21, 0x09,
     204,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_UseCaseDiagramWindow[] = {
    "UseCaseDiagramWindow\0\0hit_class()\0"
    "hit_usecase()\0hit_package()\0hit_fragment()\0"
    "hit_subject()\0hit_association()\0"
    "hit_directionalassociation()\0"
    "hit_dependency()\0hit_inherit()\0"
    "hit_note()\0hit_anchor()\0hit_text()\0"
    "hit_image()\0"
};

void UseCaseDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UseCaseDiagramWindow *_t = static_cast<UseCaseDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_class(); break;
        case 1: _t->hit_usecase(); break;
        case 2: _t->hit_package(); break;
        case 3: _t->hit_fragment(); break;
        case 4: _t->hit_subject(); break;
        case 5: _t->hit_association(); break;
        case 6: _t->hit_directionalassociation(); break;
        case 7: _t->hit_dependency(); break;
        case 8: _t->hit_inherit(); break;
        case 9: _t->hit_note(); break;
        case 10: _t->hit_anchor(); break;
        case 11: _t->hit_text(); break;
        case 12: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData UseCaseDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UseCaseDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_UseCaseDiagramWindow,
      qt_meta_data_UseCaseDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UseCaseDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UseCaseDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UseCaseDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UseCaseDiagramWindow))
        return static_cast<void*>(const_cast< UseCaseDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int UseCaseDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
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
