#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycards.h"
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include "windows.h"
#include "math.h"
#include <unistd.h>
#include <QThread>
#include <QDebug>
//class myCards;

bool isFloorSet=0;

QString deck[52] = { "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "cJ", "cQ", "cK", "cA",
                     "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "dJ", "dQ", "dK", "dA",
                     "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "h10", "hJ", "hQ", "hK", "hA",
                     "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "sJ", "sQ", "sK", "sA"};




QList <myCards*> deckCards;


QList <QList <myCards*>> floorSets;
QList <QList <myCards*>> readySets;
QList <QLabel*> topSet;

QList <myCards*> openCards;
QList <QList <myCards*>*> openCardsSets;
QList <myCards*> openNearCards;
QList <QList <myCards*>*> openNearCardsSets;
QList<double> openNearCardsDistance;

//myCards *bestPlace=nullptr;

myCards* MainWindow::currentActiveCard=nullptr;
QList <myCards*> *activeCardSet;

myCards *repeatDeck;

int whichCardX = 0;
int whichCardY = 0;
int dnX, dnY, nowX, nowY;

int delay = 100;

//------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/img/pictures/background/bg.jpg");
    int w = this->width();
    int h = this->height();
    QLabel *bg = new QLabel(this);
    bg->setGeometry(0,0,w,h);
    bg->setPixmap(pix.scaled(w,h));

    repeatDeck = new myCards(this);
    pix.load(":/img/pictures/cards/backCards.png");
    repeatDeck->setGeometry(30,30,143,200);
    repeatDeck->setPixmap(pix);

    newGame();
    //gameplay();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame(){
    double x=30,y=30;
    //---------------shuffle-----------------
    srand(time(NULL));

    for (int i = 51; i >= 0; i--)
    {
        int j = rand() % (i + 1);
        QString tmp = deck[j];
        deck[j] = deck[i];
        deck[i] = tmp;
    }
    //-----------------------------------------
    repeatDeck->isNew=true;
    repeatDeck->value="backCards";
    repeatDeck->setOpen();
    connect(repeatDeck,SIGNAL(click()),this,SLOT(deckRange()));


    for (int i = 0; i < 52; i++) {
        deckCards.append(new myCards(this));
        deckCards[i]->move(x,y);
        deckCards[i]->setValue(deck[i]);
        connect(deckCards[i],SIGNAL(moveCard()),this,SLOT(saveParameter()));
        connect(deckCards[i],SIGNAL(stopCard()),this,SLOT(moveCardToBestPlace()));
        x-=0.5;
        y-=0.5;
    }
    //-------------------createSets----------------------
    for (int i = 0; i<7;i++){
        if (i<4) readySets.append(QList<myCards*>());
        floorSets.append(QList<myCards*>());
    }
    //----------------------Top--------------------------
    x = 540; y = 30;
    for (int i = 0; i < 4; i++) {
        topSet.append(new QLabel(this));
        topSet[i]->setGeometry(x,y,143,200);
        QPixmap pix(":/img/pictures/cards/place.png");
        topSet[i]->setPixmap(pix);

        x+=170;
    }
    createSets();

}

void MainWindow::createSets(){
    int arrSize = deckCards.length();
    for (int i = 0;i<7;i++){
        for (int j = 0;j<=i;j++){
            arrSize--;
            floorSets[i].append(deckCards[arrSize]);
            qDebug()<<i<<j<<floorSets[i][j]->value;
        }
    }
    while(deckCards.length()>24) deckCards.removeLast();
    nextCard();

}

void MainWindow::nextCard(){
    //i=x j=y
    int mlsDel=0, mlsMove = 500;
    for (int j = 0;j<floorSets.length();j++){
        dnY = 260 + j*20;
        //mlsDel+=400;
        //mlsMove=500;
        for (int i=j;i<floorSets.length();i++){
            dnX = 30 + i*170;
            floorSets[i][j]->raise();

            mlsDel+=90;
            //mlsMove-=20;

            anim1 = new QPropertyAnimation (floorSets[i][j], "geometry");
            anim1->setDuration(mlsDel);
            anim1->setStartValue(QRect(18, 18, 143, 200));
            anim1->setEndValue(QRect(18, 18, 143, 200));

            anim2 = new QPropertyAnimation (floorSets[i][j], "geometry");
            anim2->setDuration(mlsMove);
            anim2->setStartValue(QRect(18, 18, 143, 200));
            anim2->setEndValue(QRect(dnX,dnY, 143, 200));

            group = new QSequentialAnimationGroup;
            group->addAnimation(anim1);
            group->addAnimation(anim2);

            group->start();

            floorSets[i][j]->isNew = false;
            floorSets[i][j]->inDeck = false;
            if (i==j) connect(group,SIGNAL(finished()),floorSets[i][j],SLOT(setOpen()));
            else floorSets[i][j]->isBlock = true;

        }
    }
}

void MainWindow::deckRange(){
    double x=30,y=30;
    for (int i=0;i<deckCards.length()-1;i++) {
        deckCards[i]->move(x,y);
        deckCards[i]->raise();
        x-=0.5;
        y-=0.5;

        deckCards[i]->setClosed();
    }
    repeatDeck->move(30,30);
    repeatDeck->isNew=true;
}
void MainWindow::gameplay(){

}

//сохранение начальных X и Y
void MainWindow::saveParameter(){
    if(currentActiveCard){
        whichCardX = currentActiveCard->x();
        whichCardY = currentActiveCard->y();
        qDebug()<<whichCardX<<whichCardY;
        fromWhatPlace();
    }
}

void MainWindow::moveCardToBestPlace(){
    if(currentActiveCard){
        nowX = currentActiveCard->x(), nowY = currentActiveCard->y();//текущее местоположение
        whatCardsHere();//открытые карты, которые находятся в диапазоне "прикосновения"
        if(openNearCards.isEmpty()==0) bestPlace();//поиск ближайшей карты
        else currentActiveCard->move(whichCardX,whichCardY);

        //-------------удаление временных массивов------------
        openCards.clear();
        openCardsSets.clear();
        openNearCards.clear();
        openNearCardsSets.clear();
        openNearCardsDistance.clear();
    }
}

void MainWindow::whatCardsHere(){
    isThisCardOpen();//все открытые карты

    for (int i = 0; i < openCards.length(); i++) {
        int thX = openCards[i]->x(), thY = openCards[i]->y();
        if(abs(thX-nowX)<=143&&abs(thY-nowY)<=200){
            openNearCards.append(openCards[i]);
            openNearCardsSets.append(openCardsSets[i]);
            openNearCardsDistance.append(sqrt((thX-nowX)*(thX-nowX)+(thY-nowY)*(thY-nowY)));
        }
        openNearCards.removeAll(currentActiveCard);
        openNearCardsSets.removeAll(activeCardSet);
    }
}
void MainWindow::isThisCardOpen(){
    for (int i = 0; i<floorSets.length();i++){
        if(floorSets[i].isEmpty()==0){
            openCards.append(floorSets[i].last());
            openCardsSets.append(&floorSets[i]);
        }
    }
}
//1111111111111111111111111111111111111111111111111111111111111111111
void MainWindow::bestPlace(){
    int bestCard=0;
    for (int i = 1;i<openNearCards.length();i++) {
        if(openNearCardsDistance[bestCard]>openNearCardsDistance[i])bestCard=i;
    }

    qDebug()<<openNearCards[bestCard]->value;
    qDebug()<<openNearCards[bestCard]->x()<<openNearCards[bestCard]->y();
    //currentActiveCard->move(openNearCards[bestCard]->x(),openNearCards[bestCard]->y()+40);
    openNearCardsSets[bestCard]->append(currentActiveCard);
    openNearCardsSets[bestCard]->last()->move(openNearCards[bestCard]->x(),openNearCards[bestCard]->y()+40);
    activeCardSet->removeAll(currentActiveCard);

    if(!activeCardSet->isEmpty()&&isFloorSet){
        activeCardSet->last()->setOpen();
        activeCardSet->last()->isBlock = false;
    }

}
//1111111111111111111111111111111111111111111111111111111111111111111


void MainWindow::fromWhatPlace(){
    isFloorSet=0;

    int n = deckCards.length();
    if(n<floorSets.length()) n = floorSets.length();
    if(n<readySets.length()) n = readySets.length();

    for (int i = 0;i<deckCards.length();i++) {
        if(i<readySets.length()&& !readySets[i].isEmpty()&&
                readySets[i].last()==currentActiveCard){
            activeCardSet=&readySets[i];
            qDebug()<<"readySets"<<i+1;
        }
        else if(i<floorSets.length()&& !floorSets[i].isEmpty()&&
                floorSets[i].last()==currentActiveCard){
            activeCardSet=&floorSets[i];
            isFloorSet=1;
            qDebug()<<"floorSets"<<i+1;
        }
        else if(i<deckCards.length()&& !deckCards.isEmpty()&&
                deckCards[i]==currentActiveCard){
            activeCardSet=&deckCards;
            qDebug()<<"deckCards"<<i+1;
        }
    }
}


