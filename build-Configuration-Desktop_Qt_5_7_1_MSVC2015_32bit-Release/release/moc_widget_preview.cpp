/****************************************************************************
** Meta object code from reading C++ file 'widget_preview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Configuration/glwidget/widget_preview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_preview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WidgetPreview_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WidgetPreview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WidgetPreview_t qt_meta_stringdata_WidgetPreview = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WidgetPreview"
QT_MOC_LITERAL(1, 14, 14), // "visableChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "isVisable"
QT_MOC_LITERAL(4, 40, 7), // "cleanup"
QT_MOC_LITERAL(5, 48, 12), // "receiveImage"
QT_MOC_LITERAL(6, 61, 5), // "image"
QT_MOC_LITERAL(7, 67, 8), // "maxValue"
QT_MOC_LITERAL(8, 76, 13), // "turnOnDisplay"
QT_MOC_LITERAL(9, 90, 14), // "turnOffDisplay"
QT_MOC_LITERAL(10, 105, 22) // "isDisplayAlreadyTurnOn"

    },
    "WidgetPreview\0visableChanged\0\0isVisable\0"
    "cleanup\0receiveImage\0image\0maxValue\0"
    "turnOnDisplay\0turnOffDisplay\0"
    "isDisplayAlreadyTurnOn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WidgetPreview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x0a /* Public */,
       5,    2,   48,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x0a /* Public */,
       9,    0,   54,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage, QMetaType::Double,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void WidgetPreview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WidgetPreview *_t = static_cast<WidgetPreview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->cleanup(); break;
        case 2: _t->receiveImage((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->turnOnDisplay(); break;
        case 4: _t->turnOffDisplay(); break;
        case 5: { bool _r = _t->isDisplayAlreadyTurnOn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WidgetPreview::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WidgetPreview::visableChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject WidgetPreview::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_WidgetPreview.data,
      qt_meta_data_WidgetPreview,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WidgetPreview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidgetPreview::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetPreview.stringdata0))
        return static_cast<void*>(const_cast< WidgetPreview*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< WidgetPreview*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int WidgetPreview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WidgetPreview::visableChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
