/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Configuration/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 29), // "on_checkBox_GrayImage_toggled"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7), // "checked"
QT_MOC_LITERAL(4, 50, 30), // "on_checkBox_MixedImage_toggled"
QT_MOC_LITERAL(5, 81, 15), // "on_ParamChanged"
QT_MOC_LITERAL(6, 97, 13), // "on_posChanged"
QT_MOC_LITERAL(7, 111, 3), // "top"
QT_MOC_LITERAL(8, 115, 6), // "bottom"
QT_MOC_LITERAL(9, 122, 4), // "left"
QT_MOC_LITERAL(10, 127, 5), // "right"
QT_MOC_LITERAL(11, 133, 5), // "exp_x"
QT_MOC_LITERAL(12, 139, 5), // "exp_y"
QT_MOC_LITERAL(13, 145, 21), // "on_groupBox_7_toggled"
QT_MOC_LITERAL(14, 167, 4), // "arg1"
QT_MOC_LITERAL(15, 172, 31), // "on_checkBox_FiltedImage_toggled"
QT_MOC_LITERAL(16, 204, 29), // "on_checkBox_EdgeImage_toggled"
QT_MOC_LITERAL(17, 234, 28) // "on_checkBox_AccImage_toggled"

    },
    "MainWindow\0on_checkBox_GrayImage_toggled\0"
    "\0checked\0on_checkBox_MixedImage_toggled\0"
    "on_ParamChanged\0on_posChanged\0top\0"
    "bottom\0left\0right\0exp_x\0exp_y\0"
    "on_groupBox_7_toggled\0arg1\0"
    "on_checkBox_FiltedImage_toggled\0"
    "on_checkBox_EdgeImage_toggled\0"
    "on_checkBox_AccImage_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    0,   60,    2, 0x08 /* Private */,
       6,    6,   61,    2, 0x08 /* Private */,
      13,    1,   74,    2, 0x08 /* Private */,
      15,    1,   77,    2, 0x08 /* Private */,
      16,    1,   80,    2, 0x08 /* Private */,
      17,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_checkBox_GrayImage_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_checkBox_MixedImage_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_ParamChanged(); break;
        case 3: _t->on_posChanged((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 4: _t->on_groupBox_7_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_checkBox_FiltedImage_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_checkBox_EdgeImage_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_checkBox_AccImage_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
