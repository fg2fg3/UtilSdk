/****************************************************************************
** Meta object code from reading C++ file 'UtilGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UtilGui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UtilGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UtilGui_t {
    QByteArrayData data[10];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UtilGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UtilGui_t qt_meta_stringdata_UtilGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "UtilGui"
QT_MOC_LITERAL(1, 8, 25), // "OnBtChineseSupportClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "OnBtCompareClicked"
QT_MOC_LITERAL(4, 54, 19), // "OnBtJoyStickClicked"
QT_MOC_LITERAL(5, 74, 21), // "OnBtOpencvDemoClicked"
QT_MOC_LITERAL(6, 96, 18), // "OnBtZipFileClicked"
QT_MOC_LITERAL(7, 115, 20), // "OnBtUnzipFileClicked"
QT_MOC_LITERAL(8, 136, 17), // "OnBtSqliteClicked"
QT_MOC_LITERAL(9, 154, 13) // "OnBtHexString"

    },
    "UtilGui\0OnBtChineseSupportClicked\0\0"
    "OnBtCompareClicked\0OnBtJoyStickClicked\0"
    "OnBtOpencvDemoClicked\0OnBtZipFileClicked\0"
    "OnBtUnzipFileClicked\0OnBtSqliteClicked\0"
    "OnBtHexString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UtilGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UtilGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UtilGui *_t = static_cast<UtilGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnBtChineseSupportClicked(); break;
        case 1: _t->OnBtCompareClicked(); break;
        case 2: _t->OnBtJoyStickClicked(); break;
        case 3: _t->OnBtOpencvDemoClicked(); break;
        case 4: _t->OnBtZipFileClicked(); break;
        case 5: _t->OnBtUnzipFileClicked(); break;
        case 6: _t->OnBtSqliteClicked(); break;
        case 7: _t->OnBtHexString(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UtilGui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UtilGui.data,
      qt_meta_data_UtilGui,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UtilGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UtilGui::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UtilGui.stringdata0))
        return static_cast<void*>(const_cast< UtilGui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UtilGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
