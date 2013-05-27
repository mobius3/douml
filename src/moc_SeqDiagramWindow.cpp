/****************************************************************************
** Meta object code from reading C++ file 'SeqDiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/SeqDiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SeqDiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SeqDiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      30,   17,   17,   17, 0x09,
      50,   17,   17,   17, 0x09,
      69,   17,   17,   17, 0x09,
      84,   17,   17,   17, 0x09,
      98,   17,   17,   17, 0x09,
     113,   17,   17,   17, 0x09,
     132,   17,   17,   17, 0x09,
     152,   17,   17,   17, 0x09,
     170,   17,   17,   17, 0x09,
     189,   17,   17,   17, 0x09,
     207,   17,   17,   17, 0x09,
     226,   17,   17,   17, 0x09,
     242,   17,   17,   17, 0x09,
     262,   17,   17,   17, 0x09,
     273,   17,   17,   17, 0x09,
     286,   17,   17,   17, 0x09,
     297,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SeqDiagramWindow[] = {
    "SeqDiagramWindow\0\0hit_class()\0"
    "hit_classinstance()\0hit_continuation()\0"
    "hit_fragment()\0hit_syncmsg()\0"
    "hit_asyncmsg()\0hit_foundsyncmsg()\0"
    "hit_foundasyncmsg()\0hit_lostsyncmsg()\0"
    "hit_lostasyncmsg()\0hit_syncselfmsg()\0"
    "hit_asyncselfmsg()\0hit_returnmsg()\0"
    "hit_selfreturnmsg()\0hit_note()\0"
    "hit_anchor()\0hit_text()\0hit_image()\0"
};

void SeqDiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SeqDiagramWindow *_t = static_cast<SeqDiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->hit_class(); break;
        case 1: _t->hit_classinstance(); break;
        case 2: _t->hit_continuation(); break;
        case 3: _t->hit_fragment(); break;
        case 4: _t->hit_syncmsg(); break;
        case 5: _t->hit_asyncmsg(); break;
        case 6: _t->hit_foundsyncmsg(); break;
        case 7: _t->hit_foundasyncmsg(); break;
        case 8: _t->hit_lostsyncmsg(); break;
        case 9: _t->hit_lostasyncmsg(); break;
        case 10: _t->hit_syncselfmsg(); break;
        case 11: _t->hit_asyncselfmsg(); break;
        case 12: _t->hit_returnmsg(); break;
        case 13: _t->hit_selfreturnmsg(); break;
        case 14: _t->hit_note(); break;
        case 15: _t->hit_anchor(); break;
        case 16: _t->hit_text(); break;
        case 17: _t->hit_image(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SeqDiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SeqDiagramWindow::staticMetaObject = {
    { &DiagramWindow::staticMetaObject, qt_meta_stringdata_SeqDiagramWindow,
      qt_meta_data_SeqDiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SeqDiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SeqDiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SeqDiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SeqDiagramWindow))
        return static_cast<void*>(const_cast< SeqDiagramWindow*>(this));
    return DiagramWindow::qt_metacast(_clname);
}

int SeqDiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
