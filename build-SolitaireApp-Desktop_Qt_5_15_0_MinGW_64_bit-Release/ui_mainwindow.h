/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "mycards.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    myCards *repeatDeck;
    QLabel *link;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1250, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        repeatDeck = new myCards(centralwidget);
        repeatDeck->setObjectName(QString::fromUtf8("repeatDeck"));
        repeatDeck->setGeometry(QRect(30, 30, 143, 200));
        repeatDeck->setPixmap(QPixmap(QString::fromUtf8("pictures/cards/backCards.png")));
        link = new QLabel(centralwidget);
        link->setObjectName(QString::fromUtf8("link"));
        link->setGeometry(QRect(455, 320, 340, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Niagara Solid"));
        font.setPointSize(82);
        link->setFont(font);
        link->setStyleSheet(QString::fromUtf8("color:rgb(202, 0, 0);"));
        link->setTextFormat(Qt::AutoText);
        link->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1250, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        repeatDeck->setText(QString());
        link->setText(QCoreApplication::translate("MainWindow", "You Win!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
