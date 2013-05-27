/****************************************************************************
** Meta object code from reading C++ file 'ColDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ColDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      30,   17,   17,   17, 0x09,
      50,   17,   17,   17, 0x09,
      64,   17,   17,   17, 0x09,
      79,   17,   17,   17, 0x09,
      90,   17,   17,   17, 0x09,
     105,   17,   17,   17, 0x09,
     116,   17,   17,   17, 0x09,
     129,   17,   17,   17, 0x09,
     140,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ColDiagramWindow[] = {
    "ColDiagramWindow\0\0hit_class()\0"
    "hit_classinstance()\0hit_package()\0"
    "hit_fragment()\0hit_link()\0hit_selflink()\0"
    "hit_note()\0hit_anchor()\0hit_text()\0"
    "hit_image()\0"
};

void ColDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColDiagramWindow *_t = static_cast<ColDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_class(); break;
        case 1: _t->hit_classinstance(); break;
        case 2: _t->hit_package(); break;
        case 3: _t->hit_fragment(); break;
        case 4: _t->hit_link(); break;
        case 5: _t->hit_selflink(); break;
        case 6: _t->hit_note(); break;
        case 7: _t->hit_anchor(); break;
        case 8: _t->hit_text(); break;
        case 9: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ColDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ColDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_ColDiagramWindow,
      qt_meta_data_ColDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColDiagramWindow))
        return static_cast<void*>(const_cast< ColDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int ColDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
