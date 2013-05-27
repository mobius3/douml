/****************************************************************************
** Meta object code from reading C++ file 'DeploymentDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/DeploymentDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeploymentDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeploymentDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x09,
      39,   24,   24,   24, 0x09,
      54,   24,   24,   24, 0x09,
      75,   24,   24,   24, 0x09,
      91,   24,   24,   24, 0x09,
     106,   24,   24,   24, 0x09,
     120,   24,   24,   24, 0x09,
     134,   24,   24,   24, 0x09,
     144,   24,   24,   24, 0x09,
     162,   24,   24,   24, 0x09,
     179,   24,   24,   24, 0x09,
     190,   24,   24,   24, 0x09,
     203,   24,   24,   24, 0x09,
     214,   24,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DeploymentDiagramWindow[] = {
    "DeploymentDiagramWindow\0\0hit_package()\0"
    "hit_fragment()\0hit_deploymentnode()\0"
    "hit_component()\0hit_artifact()\0"
    "hit_inherit()\0hit_network()\0hit_hub()\0"
    "hit_association()\0hit_dependency()\0"
    "hit_note()\0hit_anchor()\0hit_text()\0"
    "hit_image()\0"
};

void DeploymentDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeploymentDiagramWindow *_t = static_cast<DeploymentDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_package(); break;
        case 1: _t->hit_fragment(); break;
        case 2: _t->hit_deploymentnode(); break;
        case 3: _t->hit_component(); break;
        case 4: _t->hit_artifact(); break;
        case 5: _t->hit_inherit(); break;
        case 6: _t->hit_network(); break;
        case 7: _t->hit_hub(); break;
        case 8: _t->hit_association(); break;
        case 9: _t->hit_dependency(); break;
        case 10: _t->hit_note(); break;
        case 11: _t->hit_anchor(); break;
        case 12: _t->hit_text(); break;
        case 13: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DeploymentDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeploymentDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_DeploymentDiagramWindow,
      qt_meta_data_DeploymentDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeploymentDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeploymentDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeploymentDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeploymentDiagramWindow))
        return static_cast<void*>(const_cast< DeploymentDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int DeploymentDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
