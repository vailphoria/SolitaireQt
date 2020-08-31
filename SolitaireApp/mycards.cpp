#include "mycards.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <cmath>
#include <QDebug>

bool isOpen;

QString suit;
int cardValue;
QTimer *timer;

myCards::myCards(QWidget *parent) : QLabel(parent)
{
    timer = new QTimer(this);
    timer->start(1);
    pix = new QPixmap(":/img/pictures/cards/"+value+".png");
    this->setPixmap(*pix);
    this->setFixedSize(143,200);

    isOpen = false;
    isNew = true;
    isBlock = false;
    inDeck = true;


    //connect(this,SIGNAL(mousePressEvent),,SLOT(deckRange()));

}
void myCards::setOpen(){
    isOpen = true;
    pix=new QPixmap(":/img/pictures/cards/"+value+".png");
    this->setPixmap(*pix);

    testPos();
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
    qDebug()<<"mouse pressed"<<this->pos();
    if (isNew) {
        this->move(200,30);
        this->setOpen();
        this->raise();
        isNew = false;
        inDeck = true;
        click();
        testPos();

    }
    else {
        //this->move(mapToParent)
        inDeck = false;
    }

    offset = event->pos();
}
void myCards::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && isNew == false && !isBlock && !inDeck)
        {
            qDebug()<<"mm"<<this->pos();
            this->move(mapToParent(event->pos() - offset));
            this->raise(); //while not in group
        }
}

void myCards::distribution(double x0, double y0, double x1, double y1){
    myStartX = x0;
    myStartY = y0;
    myEndX = x1;
    myEndY = y1;
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    isNew = false;

}

void myCards::step(){
    if(fabs(myStartX-myEndX)<1&&fabs(myStartY-myEndY)<1){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(step()));
    }
    myStartX += (myEndX - (this->x()))/10;
    myStartY += (myEndY - (this->y()))/10;
    this->move(myStartX, myStartY);
}



void myCards::testPos(){
    qDebug()<<this->pos();
}


