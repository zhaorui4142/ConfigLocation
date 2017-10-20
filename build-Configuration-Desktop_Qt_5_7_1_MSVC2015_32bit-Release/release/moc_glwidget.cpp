/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Configuration/glwidget/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GlWidget_t {
    QByteArrayData data[25];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlWidget_t qt_meta_stringdata_GlWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GlWidget"
QT_MOC_LITERAL(1, 9, 14), // "visableChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "isVisable"
QT_MOC_LITERAL(4, 35, 10), // "posChanged"
QT_MOC_LITERAL(5, 46, 3), // "top"
QT_MOC_LITERAL(6, 50, 6), // "bottom"
QT_MOC_LITERAL(7, 57, 4), // "left"
QT_MOC_LITERAL(8, 62, 5), // "right"
QT_MOC_LITERAL(9, 68, 5), // "exp_x"
QT_MOC_LITERAL(10, 74, 5), // "exp_y"
QT_MOC_LITERAL(11, 80, 7), // "cleanup"
QT_MOC_LITERAL(12, 88, 12), // "receiveFrame"
QT_MOC_LITERAL(13, 101, 18), // "FrameRawDataStruct"
QT_MOC_LITERAL(14, 120, 5), // "frame"
QT_MOC_LITERAL(15, 126, 13), // "receiveResult"
QT_MOC_LITERAL(16, 140, 18), // "DetectResultStruct"
QT_MOC_LITERAL(17, 159, 6), // "result"
QT_MOC_LITERAL(18, 166, 30), // "receiveGrayscaledImageInResult"
QT_MOC_LITERAL(19, 197, 26), // "receiveBluredImageInResult"
QT_MOC_LITERAL(20, 224, 24), // "receiveEdgeImageInResult"
QT_MOC_LITERAL(21, 249, 25), // "receiveHoughImageInResult"
QT_MOC_LITERAL(22, 275, 13), // "turnOnDisplay"
QT_MOC_LITERAL(23, 289, 14), // "turnOffDisplay"
QT_MOC_LITERAL(24, 304, 22) // "isDisplayAlreadyTurnOn"

    },
    "GlWidget\0visableChanged\0\0isVisable\0"
    "posChanged\0top\0bottom\0left\0right\0exp_x\0"
    "exp_y\0cleanup\0receiveFrame\0"
    "FrameRawDataStruct\0frame\0receiveResult\0"
    "DetectResultStruct\0result\0"
    "receiveGrayscaledImageInResult\0"
    "receiveBluredImageInResult\0"
    "receiveEdgeImageInResult\0"
    "receiveHoughImageInResult\0turnOnDisplay\0"
    "turnOffDisplay\0isDisplayAlreadyTurnOn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    6,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   90,    2, 0x0a /* Public */,
      12,    1,   91,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      18,    1,   97,    2, 0x0a /* Public */,
      19,    1,  100,    2, 0x0a /* Public */,
      20,    1,  103,    2, 0x0a /* Public */,
      21,    1,  106,    2, 0x0a /* Public */,
      22,    0,  109,    2, 0x0a /* Public */,
      23,    0,  110,    2, 0x0a /* Public */,
      24,    0,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,    5,    6,    7,    8,    9,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void GlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GlWidget *_t = static_cast<GlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->posChanged((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 2: _t->cleanup(); break;
        case 3: _t->receiveFrame((*reinterpret_cast< FrameRawDataStruct(*)>(_a[1]))); break;
        case 4: _t->receiveResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 5: _t->receiveGrayscaledImageInResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 6: _t->receiveBluredImageInResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 7: _t->receiveEdgeImageInResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 8: _t->receiveHoughImageInResult((*reinterpret_cast< DetectResultStruct(*)>(_a[1]))); break;
        case 9: _t->turnOnDisplay(); break;
        case 10: _t->turnOffDisplay(); break;
        case 11: { bool _r = _t->isDisplayAlreadyTurnOn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GlWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlWidget::visableChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GlWidget::*_t)(qreal , qreal , qreal , qreal , qreal , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlWidget::posChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GlWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_GlWidget.data,
      qt_meta_data_GlWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GlWidget.stringdata0))
        return static_cast<void*>(const_cast< GlWidget*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< GlWidget*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int GlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void GlWidget::visableChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GlWidget::posChanged(qreal _t1, qreal _t2, qreal _t3, qreal _t4, qreal _t5, qreal _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
