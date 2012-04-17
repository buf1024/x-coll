/****************************************************************************
** Meta object code from reading C++ file 'ctrlsrv.h'
**
** Created: Tue Apr 17 21:42:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ctrlsrv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctrlsrv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CtrlSrv[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,    9,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CtrlSrv[] = {
    "CtrlSrv\0\0id,mod,key\0onHotKeyGenerated(int,int,int)\0"
};

void CtrlSrv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CtrlSrv *_t = static_cast<CtrlSrv *>(_o);
        switch (_id) {
        case 0: _t->onHotKeyGenerated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CtrlSrv::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CtrlSrv::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CtrlSrv,
      qt_meta_data_CtrlSrv, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CtrlSrv::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CtrlSrv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CtrlSrv::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CtrlSrv))
        return static_cast<void*>(const_cast< CtrlSrv*>(this));
    return QWidget::qt_metacast(_clname);
}

int CtrlSrv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
