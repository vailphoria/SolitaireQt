#include "mycards.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <cmath>
#include <QDebug>

bool isOpen;

//QString suit;
//int cardValue;
QTimer *timer;

myCards::myCards(QWidget *parent) : QLabel(parent)
{
    //timer = new QTimer(this);
    //timer->start(1);
    pix = new QPixmap(":/img/pictures/cards/"+value+".png");
    this->setPixmap(*pix);
    this->setFixedSize(143,200);

    isOpen = false;
    isNew = true;
    isBlock = false;
    inDeck = true;
    onMove = false;

}
void myCards::setOpen(){
    isOpen = true;
    pix=new QPixmap(":/img/pictures/cards/"+value+".png");
    this->setPixmap(*pix);
}
void myCards::setClosed(){
    isOpen = false;
    pix=new QPixmap(":/img/pictures/cards/suit.png");
    this->setPixmap(*pix);
    this->isNew = true;
    this->inDeck = true;
}
void myCards::setValue(QString val1){
    value = val1;

    suit = value[0];

    if(value[1] == "A") cardValue = 1;
    else if(value[1] == "2") cardValue = 2;
    else if(value[1] == "3") cardValue = 3;
    else if(value[1] == "4") cardValue = 4;
    else if(value[1] == "5") cardValue = 5;
    else if(value[1] == "6") cardValue = 6;
    else if(value[1] == "7") cardValue = 7;
    else if(value[1] == "8") cardValue = 8;
    else if(value[1] == "9") cardValue = 9;
    else if(value[1] == "1") cardValue = 10;
    else if(value[1] == "J") cardValue = 11;
    else if(value[1] == "Q") cardValue = 12;
    else if(value[1] == "K") cardValue = 13;
}


void myCards::mousePressEvent(QMouseEvent *event)
{
    MainWindow::currentActiveCard = nullptr;
    if (isNew) {
        this->move(200,30);
        this->setOpen();
        this->raise();
        isNew = false;
        inDeck = true;
        click();

    }
    else {
        inDeck = false;
    }

    offset = event->pos();
}
void myCards::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton && isNew == false && !isBlock && !inDeck)
        {
        if(MainWindow::currentActiveCard!=this){
            MainWindow::currentActiveCard = this;
            moveCard();
            this->raise();
        }
        this->move(mapToParent(event->pos() - offset));
        this->raise();
        movingGroup();
        }
}
void myCards::mouseReleaseEvent(QMouseEvent *event){
    stopCard();
}


