/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../paint_server/main_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_main_window_t {
    QByteArrayData data[12];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_main_window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_main_window_t qt_meta_stringdata_main_window = {
    {
QT_MOC_LITERAL(0, 0, 11), // "main_window"
QT_MOC_LITERAL(1, 12, 19), // "signal_send_message"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 2), // "to"
QT_MOC_LITERAL(4, 36, 3), // "msg"
QT_MOC_LITERAL(5, 40, 25), // "on_button_connect_clicked"
QT_MOC_LITERAL(6, 66, 22), // "on_putton_send_clicked"
QT_MOC_LITERAL(7, 89, 38), // "on_dialog_users_list_currentR..."
QT_MOC_LITERAL(8, 128, 10), // "currentRow"
QT_MOC_LITERAL(9, 139, 16), // "slot_new_message"
QT_MOC_LITERAL(10, 156, 20), // "slot_new_user_online"
QT_MOC_LITERAL(11, 177, 4) // "name"

    },
    "main_window\0signal_send_message\0\0to\0"
    "msg\0on_button_connect_clicked\0"
    "on_putton_send_clicked\0"
    "on_dialog_users_list_currentRowChanged\0"
    "currentRow\0slot_new_message\0"
    "slot_new_user_online\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_window[] = {

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
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       9,    2,   54,    2, 0x0a /* Public */,
      10,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void main_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        main_window *_t = static_cast<main_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_send_message((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->on_button_connect_clicked(); break;
        case 2: _t->on_putton_send_clicked(); break;
        case 3: _t->on_dialog_users_list_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_new_message((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->slot_new_user_online((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (main_window::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&main_window::signal_send_message)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject main_window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_main_window.data,
      qt_meta_data_main_window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *main_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_main_window.stringdata0))
        return static_cast<void*>(const_cast< main_window*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int main_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void main_window::signal_send_message(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
