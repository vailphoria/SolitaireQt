#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycards.h"
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include "windows.h"
//#include <QTest>
#include <unistd.h>
#include <QThread>
#include <QPropertyAnimation>
#include <QDebug>
//class myCards;



QString deck[52] = { "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "cJ", "cQ", "cK", "cA",
                     "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "dJ", "dQ", "dK", "dA",
                     "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "h10", "hJ", "hQ", "hK", "hA",
                     "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "sJ", "sQ", "sK", "sA"};




QList <myCards*> deckCards;

QList <QList <myCards*>> floorSets;
QList <QList <myCards*>> readySets;

myCards* MainWindow::currentActiveCard;

int whichCardX = 0;
int whichCardY = 0;
int dnX, dnY;

//------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
    ui->repeatDeck->isNew=true;
    ui->repeatDeck->value="backCards";
    ui->repeatDeck->setOpen();
    connect(ui->repeatDeck,SIGNAL(click()),this,SLOT(deckRange()));


    for (int i = 0; i < 52; i++) {
        deckCards.append(new myCards(this));
        deckCards[i]->move(x,y);
        deckCards[i]->setValue(deck[i]);
        connect(deckCards[i],SIGNAL(moveCard()),this,SLOT(gameplay()));
        x-=0.5;
        y-=0.5;
    }
    //-------------------createSets----------------------
    for (int i = 0; i<7;i++){
        if (i<4) readySets.append(QList<myCards*>());
        floorSets.append(QList<myCards*>());
    }
    //---------------------------------------------------
    createSets();
    nextCard();
}

void MainWindow::createSets(){
    int arrSize = deckCards.length()-1;
    for (int i = 0;i<7;i++){
        for (int j = i;j<7;j++){
            floorSets[j].append(deckCards[arrSize]);
            arrSize--;
        }
    }
}

void MainWindow::nextCard(){
    dnY = 260 + whichCardY*20;
    dnX = 30 + whichCardX*170;
    QPropertyAnimation *animation = new QPropertyAnimation(deckCards[deckCards.length()-1], "geometry");

    animation->setDuration(1000);
    animation->setStartValue(QRect(30, 30, 100, 30));
    animation->setEndValue(QRect(dnX, dnY, 100, 30));
    animation->start();

    deckCards[deckCards.length()-1]->raise();
    deckCards[deckCards.length()-1]->isNew = false;
    deckCards[deckCards.length()-1]->inDeck = false;
    if (whichCardX==whichCardY) connect(animation,SIGNAL(finished()),deckCards[deckCards.length()-1],SLOT(setOpen()));
    else deckCards[deckCards.length()-1]->isBlock = true;

    whichCardX++;
    if(whichCardX%7==0){
        whichCardY++;
        whichCardX=whichCardY;
    }

    if((deckCards.length()-1)>24){
        deckCards.removeLast();

        QTimer::singleShot(100,this,SLOT(nextCard()));
    }
}

void MainWindow::gameplay(){
    qDebug()<<currentActiveCard;
    currentActiveCard->move(40,40);
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
    ui->repeatDeck->move(30,30);
    ui->repeatDeck->isNew=true;
}
