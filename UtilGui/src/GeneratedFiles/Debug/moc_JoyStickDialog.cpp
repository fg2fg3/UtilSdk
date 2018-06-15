/****************************************************************************
** Meta object code from reading C++ file 'JoyStickDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../JoyStickDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JoyStickDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JoyStickDialog_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JoyStickDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JoyStickDialog_t qt_meta_stringdata_JoyStickDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "JoyStickDialog"
QT_MOC_LITERAL(1, 15, 18), // "OnBtCaptureClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "OnBtOpenComClicked"
QT_MOC_LITERAL(4, 54, 19) // "OnBtCloseComClicked"

    },
    "JoyStickDialog\0OnBtCaptureClicked\0\0"
    "OnBtOpenComClicked\0OnBtCloseComClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JoyStickDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void JoyStickDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JoyStickDialog *_t = static_cast<JoyStickDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnBtCaptureClicked(); break;
        case 1: _t->OnBtOpenComClicked(); break;
        case 2: _t->OnBtCloseComClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject JoyStickDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JoyStickDialog.data,
      qt_meta_data_JoyStickDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JoyStickDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JoyStickDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JoyStickDialog.stringdata0))
        return static_cast<void*>(const_cast< JoyStickDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int JoyStickDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
