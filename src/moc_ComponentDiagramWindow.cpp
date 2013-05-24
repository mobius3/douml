/****************************************************************************
** Meta object code from reading C++ file 'ComponentDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ComponentDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComponentDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ComponentDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x09,
      40,   23,   23,   23, 0x09,
      54,   23,   23,   23, 0x09,
      69,   23,   23,   23, 0x09,
      83,   23,   23,   23, 0x09,
     100,   23,   23,   23, 0x09,
     115,   23,   23,   23, 0x09,
     130,   23,   23,   23, 0x09,
     141,   23,   23,   23, 0x09,
     154,   23,   23,   23, 0x09,
     165,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ComponentDiagramWindow[] = {
    "ComponentDiagramWindow\0\0hit_component()\0"
    "hit_package()\0hit_fragment()\0hit_inherit()\0"
    "hit_dependency()\0hit_required()\0"
    "hit_provided()\0hit_note()\0hit_anchor()\0"
    "hit_text()\0hit_image()\0"
};

void ComponentDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComponentDiagramWindow *_t = static_cast<ComponentDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_component(); break;
        case 1: _t->hit_package(); break;
        case 2: _t->hit_fragment(); break;
        case 3: _t->hit_inherit(); break;
        case 4: _t->hit_dependency(); break;
        case 5: _t->hit_required(); break;
        case 6: _t->hit_provided(); break;
        case 7: _t->hit_note(); break;
        case 8: _t->hit_anchor(); break;
        case 9: _t->hit_text(); break;
        case 10: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ComponentDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ComponentDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_ComponentDiagramWindow,
      qt_meta_data_ComponentDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ComponentDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ComponentDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ComponentDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ComponentDiagramWindow))
        return static_cast<void*>(const_cast< ComponentDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int ComponentDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
