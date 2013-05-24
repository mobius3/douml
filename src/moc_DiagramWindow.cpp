/****************************************************************************
** Meta object code from reading C++ file 'DiagramWindow.h'
**
** Created: Fri May 24 23:48:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diagram/DiagramWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiagramWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DiagramWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      30,   14,   14,   14, 0x0a,
      42,   14,   14,   14, 0x0a,
      64,   14,   14,   14, 0x0a,
      86,   14,   14,   14, 0x0a,
      98,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DiagramWindow[] = {
    "DiagramWindow\0\0new_scale(int)\0fit_scale()\0"
    "optimal_window_size()\0session_window_size()\0"
    "call_menu()\0hit_select()\0"
};

void DiagramWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DiagramWindow *_t = static_cast<DiagramWindow *>(_o);
        switch (_id) {
        case 0: _t->new_scale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->fit_scale(); break;
        case 2: _t->optimal_window_size(); break;
        case 3: _t->session_window_size(); break;
        case 4: _t->call_menu(); break;
        case 5: _t->hit_select(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DiagramWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DiagramWindow::staticMetaObject = {
    { &Q3MainWindow::staticMetaObject, qt_meta_stringdata_DiagramWindow,
      qt_meta_data_DiagramWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DiagramWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DiagramWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DiagramWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DiagramWindow))
        return static_cast<void*>(const_cast< DiagramWindow*>(this));
    return Q3MainWindow::qt_metacast(_clname);
}

int DiagramWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
