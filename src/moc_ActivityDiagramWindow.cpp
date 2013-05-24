/****************************************************************************
** Meta object code from reading C++ file 'ActivityDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/ActivityDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivityDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActivityDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      38,   22,   22,   22, 0x09,
      72,   22,   22,   22, 0x09,
      94,   22,   22,   22, 0x09,
     118,   22,   22,   22, 0x09,
     132,   22,   22,   22, 0x09,
     152,   22,   22,   22, 0x09,
     168,   22,   22,   22, 0x09,
     183,   22,   22,   22, 0x09,
     195,   22,   22,   22, 0x09,
     206,   22,   22,   22, 0x09,
     217,   22,   22,   22, 0x09,
     230,   22,   22,   22, 0x09,
     243,   22,   22,   22, 0x09,
     254,   22,   22,   22, 0x09,
     271,   22,   22,   22, 0x09,
     285,   22,   22,   22, 0x09,
     300,   22,   22,   22, 0x09,
     311,   22,   22,   22, 0x09,
     324,   22,   22,   22, 0x09,
     335,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ActivityDiagramWindow[] = {
    "ActivityDiagramWindow\0\0hit_activity()\0"
    "hit_interruptibleactivityregion()\0"
    "hit_expansionregion()\0hit_activitypartition()\0"
    "hit_initial()\0hit_activityfinal()\0"
    "hit_flowfinal()\0hit_decision()\0"
    "hit_merge()\0hit_fork()\0hit_join()\0"
    "hit_action()\0hit_object()\0hit_flow()\0"
    "hit_dependency()\0hit_package()\0"
    "hit_fragment()\0hit_note()\0hit_anchor()\0"
    "hit_text()\0hit_image()\0"
};

void ActivityDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActivityDiagramWindow *_t = static_cast<ActivityDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_activity(); break;
        case 1: _t->hit_interruptibleactivityregion(); break;
        case 2: _t->hit_expansionregion(); break;
        case 3: _t->hit_activitypartition(); break;
        case 4: _t->hit_initial(); break;
        case 5: _t->hit_activityfinal(); break;
        case 6: _t->hit_flowfinal(); break;
        case 7: _t->hit_decision(); break;
        case 8: _t->hit_merge(); break;
        case 9: _t->hit_fork(); break;
        case 10: _t->hit_join(); break;
        case 11: _t->hit_action(); break;
        case 12: _t->hit_object(); break;
        case 13: _t->hit_flow(); break;
        case 14: _t->hit_dependency(); break;
        case 15: _t->hit_package(); break;
        case 16: _t->hit_fragment(); break;
        case 17: _t->hit_note(); break;
        case 18: _t->hit_anchor(); break;
        case 19: _t->hit_text(); break;
        case 20: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ActivityDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ActivityDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_ActivityDiagramWindow,
      qt_meta_data_ActivityDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActivityDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActivityDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActivityDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityDiagramWindow))
        return static_cast<void*>(const_cast< ActivityDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int ActivityDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
