/****************************************************************************
** Meta object code from reading C++ file 'ClassDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ClassDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x09,
      32,   19,   19,   19, 0x09,
      46,   19,   19,   19, 0x09,
      61,   19,   19,   19, 0x09,
      75,   19,   19,   19, 0x09,
      92,   19,   19,   19, 0x09,
     110,   19,   19,   19, 0x09,
     139,   19,   19,   19, 0x09,
     157,   19,   19,   19, 0x09,
     182,   19,   19,   19, 0x09,
     211,   19,   19,   19, 0x09,
     247,   19,   19,   19, 0x09,
     261,   19,   19,   19, 0x09,
     272,   19,   19,   19, 0x09,
     285,   19,   19,   19, 0x09,
     296,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ClassDiagramWindow[] = {
    "ClassDiagramWindow\0\0hit_class()\0"
    "hit_package()\0hit_fragment()\0hit_inherit()\0"
    "hit_dependency()\0hit_association()\0"
    "hit_directionalassociation()\0"
    "hit_aggregation()\0hit_aggregationbyvalue()\0"
    "hit_directionalaggregation()\0"
    "hit_directionalaggregationbyvalue()\0"
    "hit_realize()\0hit_note()\0hit_anchor()\0"
    "hit_text()\0hit_image()\0"
};

void ClassDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassDiagramWindow *_t = static_cast<ClassDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_class(); break;
        case 1: _t->hit_package(); break;
        case 2: _t->hit_fragment(); break;
        case 3: _t->hit_inherit(); break;
        case 4: _t->hit_dependency(); break;
        case 5: _t->hit_association(); break;
        case 6: _t->hit_directionalassociation(); break;
        case 7: _t->hit_aggregation(); break;
        case 8: _t->hit_aggregationbyvalue(); break;
        case 9: _t->hit_directionalaggregation(); break;
        case 10: _t->hit_directionalaggregationbyvalue(); break;
        case 11: _t->hit_realize(); break;
        case 12: _t->hit_note(); break;
        case 13: _t->hit_anchor(); break;
        case 14: _t->hit_text(); break;
        case 15: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClassDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_ClassDiagramWindow,
      qt_meta_data_ClassDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassDiagramWindow))
        return static_cast<void*>(const_cast< ClassDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int ClassDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
