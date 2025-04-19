/****************************************************************************
** Meta object code from reading C++ file 'ButtonHandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/handler/ButtonHandler.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ButtonHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSButtonHandlerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSButtonHandlerENDCLASS = QtMocHelpers::stringData(
    "ButtonHandler",
    "serialPortsUpdated",
    "",
    "ports",
    "serialdataReceived",
    "data",
    "nwwdx_serialPortsUpdated",
    "nwwdx_serialdataReceived",
    "onSet_XJ_Charger_Id_Clicked",
    "uid",
    "onRead_XJ_Charger_Id_Clicked",
    "onSet_XJ_Username_Clicked",
    "username",
    "onSet_XJ_Password_Clicked",
    "password",
    "onRead_XJ_Password_Clicked",
    "onRelay_On_Clicked",
    "onAuto_Cal_Emu_Clicked",
    "onSet_Card_Uid_Clicked",
    "onRead_Card_Uid_Clicked",
    "onSerial_Port_Check_Clicked",
    "openSerialPort",
    "portName",
    "closeSerialPort",
    "readSerialData",
    "writeSerialData",
    "onTimerOut",
    "onNWWDX_Serial_Port_Check_Clicked",
    "openNWWDXSerialPort",
    "closeNWWDXSerialPort",
    "readNWWDXSerialData",
    "writeNWWDXSerialData",
    "onNWWDXTimerOut",
    "onSet_NWWDX_Charger_Id_Clicked",
    "onRead_NWWDX_Charger_Id_Clicked",
    "onSet_NWWDX_IP_Port_Clicked",
    "ip",
    "port",
    "onRead_NWWDX_IP_Port_Clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSButtonHandlerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  188,    2, 0x06,    1 /* Public */,
       4,    1,  191,    2, 0x06,    3 /* Public */,
       6,    1,  194,    2, 0x06,    5 /* Public */,
       7,    1,  197,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,  200,    2, 0x0a,    9 /* Public */,
      10,    0,  203,    2, 0x0a,   11 /* Public */,
      11,    1,  204,    2, 0x0a,   12 /* Public */,
      13,    1,  207,    2, 0x0a,   14 /* Public */,
      15,    0,  210,    2, 0x0a,   16 /* Public */,
      16,    0,  211,    2, 0x0a,   17 /* Public */,
      17,    0,  212,    2, 0x0a,   18 /* Public */,
      18,    1,  213,    2, 0x0a,   19 /* Public */,
      19,    0,  216,    2, 0x0a,   21 /* Public */,
      20,    0,  217,    2, 0x0a,   22 /* Public */,
      21,    1,  218,    2, 0x0a,   23 /* Public */,
      23,    1,  221,    2, 0x0a,   25 /* Public */,
      24,    0,  224,    2, 0x0a,   27 /* Public */,
      25,    1,  225,    2, 0x0a,   28 /* Public */,
      26,    0,  228,    2, 0x0a,   30 /* Public */,
      27,    0,  229,    2, 0x0a,   31 /* Public */,
      28,    1,  230,    2, 0x0a,   32 /* Public */,
      29,    1,  233,    2, 0x0a,   34 /* Public */,
      30,    0,  236,    2, 0x0a,   36 /* Public */,
      31,    1,  237,    2, 0x0a,   37 /* Public */,
      32,    0,  240,    2, 0x0a,   39 /* Public */,
      33,    1,  241,    2, 0x0a,   40 /* Public */,
      34,    0,  244,    2, 0x0a,   42 /* Public */,
      35,    2,  245,    2, 0x0a,   43 /* Public */,
      38,    0,  250,    2, 0x0a,   46 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   36,   37,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ButtonHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSButtonHandlerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSButtonHandlerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSButtonHandlerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ButtonHandler, std::true_type>,
        // method 'serialPortsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'serialdataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'nwwdx_serialPortsUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'nwwdx_serialdataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSet_XJ_Charger_Id_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRead_XJ_Charger_Id_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSet_XJ_Username_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSet_XJ_Password_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRead_XJ_Password_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRelay_On_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAuto_Cal_Emu_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSet_Card_Uid_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRead_Card_Uid_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSerial_Port_Check_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'closeSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'readSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'writeSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onTimerOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNWWDX_Serial_Port_Check_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openNWWDXSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'closeNWWDXSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'readNWWDXSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'writeNWWDXSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onNWWDXTimerOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSet_NWWDX_Charger_Id_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRead_NWWDX_Charger_Id_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSet_NWWDX_IP_Port_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onRead_NWWDX_IP_Port_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ButtonHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ButtonHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->serialPortsUpdated((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 1: _t->serialdataReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->nwwdx_serialPortsUpdated((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 3: _t->nwwdx_serialdataReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onSet_XJ_Charger_Id_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onRead_XJ_Charger_Id_Clicked(); break;
        case 6: _t->onSet_XJ_Username_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onSet_XJ_Password_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onRead_XJ_Password_Clicked(); break;
        case 9: _t->onRelay_On_Clicked(); break;
        case 10: _t->onAuto_Cal_Emu_Clicked(); break;
        case 11: _t->onSet_Card_Uid_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->onRead_Card_Uid_Clicked(); break;
        case 13: _t->onSerial_Port_Check_Clicked(); break;
        case 14: _t->openSerialPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->closeSerialPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->readSerialData(); break;
        case 17: _t->writeSerialData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->onTimerOut(); break;
        case 19: _t->onNWWDX_Serial_Port_Check_Clicked(); break;
        case 20: _t->openNWWDXSerialPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->closeNWWDXSerialPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->readNWWDXSerialData(); break;
        case 23: _t->writeNWWDXSerialData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 24: _t->onNWWDXTimerOut(); break;
        case 25: _t->onSet_NWWDX_Charger_Id_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->onRead_NWWDX_Charger_Id_Clicked(); break;
        case 27: _t->onSet_NWWDX_IP_Port_Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 28: _t->onRead_NWWDX_IP_Port_Clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ButtonHandler::*)(const QStringList & );
            if (_t _q_method = &ButtonHandler::serialPortsUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ButtonHandler::*)(const QString & );
            if (_t _q_method = &ButtonHandler::serialdataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ButtonHandler::*)(const QStringList & );
            if (_t _q_method = &ButtonHandler::nwwdx_serialPortsUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ButtonHandler::*)(const QString & );
            if (_t _q_method = &ButtonHandler::nwwdx_serialdataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *ButtonHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ButtonHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSButtonHandlerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ButtonHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void ButtonHandler::serialPortsUpdated(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ButtonHandler::serialdataReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ButtonHandler::nwwdx_serialPortsUpdated(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ButtonHandler::nwwdx_serialdataReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
