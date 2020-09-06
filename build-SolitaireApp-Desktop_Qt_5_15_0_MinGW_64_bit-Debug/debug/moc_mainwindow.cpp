/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SolitaireApp/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "deckRange"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "newGame"
QT_MOC_LITERAL(4, 30, 8), // "nextCard"
QT_MOC_LITERAL(5, 39, 14), // "haveWeNextStep"
QT_MOC_LITERAL(6, 54, 8), // "gameOver"
QT_MOC_LITERAL(7, 63, 10), // "createSets"
QT_MOC_LITERAL(8, 74, 13), // "saveParameter"
QT_MOC_LITERAL(9, 88, 13), // "whatCardsHere"
QT_MOC_LITERAL(10, 102, 14), // "isThisCardOpen"
QT_MOC_LITERAL(11, 117, 19), // "moveCardToBestPlace"
QT_MOC_LITERAL(12, 137, 9), // "bestPlace"
QT_MOC_LITERAL(13, 147, 13), // "fromWhatPlace"
QT_MOC_LITERAL(14, 161, 11), // "emptyPlaces"
QT_MOC_LITERAL(15, 173, 17), // "openNextFloorCard"
QT_MOC_LITERAL(16, 191, 12), // "realizeGroup"
QT_MOC_LITERAL(17, 204, 9), // "moveGroup"
QT_MOC_LITERAL(18, 214, 9), // "stopGroup"
QT_MOC_LITERAL(19, 224, 14) // "bestGroupPlace"

    },
    "MainWindow\0deckRange\0\0newGame\0nextCard\0"
    "haveWeNextStep\0gameOver\0createSets\0"
    "saveParameter\0whatCardsHere\0isThisCardOpen\0"
    "moveCardToBestPlace\0bestPlace\0"
    "fromWhatPlace\0emptyPlaces\0openNextFloorCard\0"
    "realizeGroup\0moveGroup\0stopGroup\0"
    "bestGroupPlace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deckRange(); break;
        case 1: _t->newGame(); break;
        case 2: _t->nextCard(); break;
        case 3: _t->haveWeNextStep(); break;
        case 4: _t->gameOver(); break;
        case 5: _t->createSets(); break;
        case 6: _t->saveParameter(); break;
        case 7: _t->whatCardsHere(); break;
        case 8: _t->isThisCardOpen(); break;
        case 9: _t->moveCardToBestPlace(); break;
        case 10: _t->bestPlace(); break;
        case 11: _t->fromWhatPlace(); break;
        case 12: _t->emptyPlaces(); break;
        case 13: _t->openNextFloorCard(); break;
        case 14: _t->realizeGroup(); break;
        case 15: _t->moveGroup(); break;
        case 16: _t->stopGroup(); break;
        case 17: _t->bestGroupPlace(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
