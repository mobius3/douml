/****************************************************************************
** Meta object code from reading C++ file 'StateDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/StateDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
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
      78,   19,   19,   19, 0x09,
      94,   19,   19,   19, 0x09,
     108,   19,   19,   19, 0x09,
     120,   19,   19,   19, 0x09,
     136,   19,   19,   19, 0x09,
     154,   19,   19,   19, 0x09,
     175,   19,   19,   19, 0x09,
     190,   19,   19,   19, 0x09,
     203,   19,   19,   19, 0x09,
     214,   19,   19,   19, 0x09,
     225,   19,   19,   19, 0x09,
     238,   19,   19,   19, 0x09,
     251,   19,   19,   19, 0x09,
     266,   19,   19,   19, 0x09,
     282,   19,   19,   19, 0x09,
     299,   19,   19,   19, 0x09,
     310,   19,   19,   19, 0x09,
     323,   19,   19,   19, 0x09,
     334,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StateDiagramWindow[] = {
    "StateDiagramWindow\0\0hit_state()\0"
    "hit_package()\0hit_fragment()\0"
    "hit_entryPoint()\0hit_exitPoint()\0"
    "hit_initial()\0hit_final()\0hit_terminate()\0"
    "hit_deepHistory()\0hit_shallowHistory()\0"
    "hit_junction()\0hit_choice()\0hit_fork()\0"
    "hit_join()\0hit_region()\0hit_action()\0"
    "hit_signalin()\0hit_signalout()\0"
    "hit_transition()\0hit_note()\0hit_anchor()\0"
    "hit_text()\0hit_image()\0"
};

void StateDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateDiagramWindow *_t = static_cast<StateDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_state(); break;
        case 1: _t->hit_package(); break;
        case 2: _t->hit_fragment(); break;
        case 3: _t->hit_entryPoint(); break;
        case 4: _t->hit_exitPoint(); break;
        case 5: _t->hit_initial(); break;
        case 6: _t->hit_final(); break;
        case 7: _t->hit_terminate(); break;
        case 8: _t->hit_deepHistory(); break;
        case 9: _t->hit_shallowHistory(); break;
        case 10: _t->hit_junction(); break;
        case 11: _t->hit_choice(); break;
        case 12: _t->hit_fork(); break;
        case 13: _t->hit_join(); break;
        case 14: _t->hit_region(); break;
        case 15: _t->hit_action(); break;
        case 16: _t->hit_signalin(); break;
        case 17: _t->hit_signalout(); break;
        case 18: _t->hit_transition(); break;
        case 19: _t->hit_note(); break;
        case 20: _t->hit_anchor(); break;
        case 21: _t->hit_text(); break;
        case 22: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StateDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_StateDiagramWindow,
      qt_meta_data_StateDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateDiagramWindow))
        return static_cast<void*>(const_cast< StateDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int StateDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
