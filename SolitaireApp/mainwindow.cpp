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
bool isGroup = 0;

QString deck[52] = { "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "cJ", "cQ", "cK", "cA",
                     "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "dJ", "dQ", "dK", "dA",
                     "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "h10", "hJ", "hQ", "hK", "hA",
                     "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "sJ", "sQ", "sK", "sA"};




QList <myCards*> deckCards;
QList <myCards*> newGroup;

QList <QList <myCards*>> floorSets;
QList <QList <myCards*>> readySets;
QList <Place*> floorPlaces;
QList <Place*> readyPlaces;


QList <Place*> openCardPlaces;
QList <QList <myCards*>*> openCardPlacesSets;
QList <Place*> openNearCardPlaces;
QList <QList <myCards*>*> openNearCardPlacesSets;
QList<double> openNearCardPlacesDistance;

QList <myCards*> openCards;
QList <QList <myCards*>*> openCardsSets;
QList <myCards*> openNearCards;
QList <QList <myCards*>*> openNearCardsSets;
QList<double> openNearCardsDistance;


QList <myCards*> readyCards;
QList <QList <myCards*>*> readyCardsSets;
QList <myCards*> readyNearCards;
QList <QList <myCards*>*> readyNearCardsSets;
QList<double> readyNearCardsDistance;

myCards* MainWindow::currentActiveCard=nullptr;
QList <myCards*> *activeCardSet = nullptr;

myCards *repeatDeck;

bool isTheReadyEmpty = false, isTheFloorEmpty = false;

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
        connect(deckCards[i],SIGNAL(movingGroup()),this,SLOT(moveGroup()));
        x-=0.5;
        y-=0.5;
    }
    //-------------------createSets----------------------
    for (int i = 0; i<7;i++){
        if (i<4) readySets.append(QList<myCards*>());
        floorSets.append(QList<myCards*>());
    }
    //----------------------Top--------------------------
    x = 30;
    for (int i = 0; i < 7; i++) {
        if (i>2){
            readyPlaces.append(new Place(this));
            readyPlaces.last()->move(x,30);
        }
        floorPlaces.append(new Place(this));
        floorPlaces[i]->move(x,260);

        x+=170;
    }
    createSets();
    emptyPlaces();

}

void MainWindow::createSets(){
    int arrSize = deckCards.length();
    for (int i = 0;i<7;i++){
        for (int j = 0;j<=i;j++){
            arrSize--;
            floorSets[i].append(deckCards[arrSize]);
            //qDebug()<<i<<j<<floorSets[i][j]->value;
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
    for (int i=0;i<deckCards.length();i++) {
        deckCards[i]->move(x,y);
        deckCards[i]->raise();
        x-=0.5;
        y-=0.5;

        deckCards[i]->setClosed();
    }
    repeatDeck->move(30,30);
    repeatDeck->isNew=true;
}

void MainWindow::haveWeNextStep(){
    bool isGameOver = true;
    for (int i = 0; i < readySets.length(); i++) {
        if (!readySets[i].isEmpty()&&readySets[i].last()->cardValue==13) continue;
        else{
            isGameOver = false;
            break;
        }
    }
    if(isGameOver)gameOver();
}
void MainWindow::gameOver(){
    qDebug()<<"GameOver";
}

//сохранение начальных X и Y
void MainWindow::saveParameter(){
    if(currentActiveCard){
        whichCardX = currentActiveCard->x();
        whichCardY = currentActiveCard->y();
        //qDebug()<<whichCardX<<whichCardY;
        fromWhatPlace();

        if(isGroup) realizeGroup();      
    }
}
//---не входит
void MainWindow::moveCardToBestPlace(){
    if(currentActiveCard){
        qDebug()<<"---------------------------------------------------";
        nowX = currentActiveCard->x(), nowY = currentActiveCard->y();//текущее местоположение
        whatCardsHere();//открытые карты, которые находятся в диапазоне "прикосновения"
        if(!openNearCards.isEmpty()&&!newGroup.isEmpty())bestGroupPlace();
        else if(!openNearCards.isEmpty()||!readyNearCards.isEmpty()||!openNearCardPlaces.isEmpty()) bestPlace();//поиск ближайшей карты
        else currentActiveCard->move(whichCardX,whichCardY);

        stopGroup();
        //-------------удаление временных массивов------------
        emptyPlaces();

        //floor
        openCards.clear();
        openCardsSets.clear();
        openNearCards.clear();
        openNearCardsSets.clear();
        openNearCardsDistance.clear();
        //places
        openCardPlaces.clear();
        openCardPlacesSets.clear();
        openNearCardPlaces.clear();
        openNearCardPlacesSets.clear();
        openNearCardPlacesDistance.clear();
        //ready
        readyCards.clear();
        readyCardsSets.clear();
        readyNearCards.clear();
        readyNearCardsSets.clear();
        readyNearCardsDistance.clear();

        activeCardSet = nullptr;
        newGroup.clear();

        haveWeNextStep();
    }
}
//---не входит
void MainWindow::whatCardsHere(){
    isThisCardOpen();//все открытые карты
    //----------------------Places-------------------------
    if(!openCardPlaces.isEmpty()){
        for (int i = 0; i < openCardPlaces.length(); i++) {
            int thX = openCardPlaces[i]->x(), thY = openCardPlaces[i]->y();
            if(abs(thX-nowX)<=143&&abs(thY-nowY)<=200){
                openNearCardPlaces.append(openCardPlaces[i]);
                openNearCardPlacesSets.append(openCardPlacesSets[i]);
                openNearCardPlacesDistance.append(sqrt((thX-nowX)*(thX-nowX)+(thY-nowY)*(thY-nowY)));
            }
            //openNearCards.removeAll(currentActiveCard);
            openNearCardPlacesSets.removeAll(activeCardSet);
        }

    }
    //-----------------------Cards-------------------------
    if(!openCards.isEmpty()){
        for (int i = 0; i < openCards.length(); i++) {
            int thX = openCards[i]->x(), thY = openCards[i]->y();
            if(abs(thX-nowX)<=143&&abs(thY-nowY)<=200&&openCards[i]->cardValue-currentActiveCard->cardValue==1&&
                    (((openCards[i]->suit=="h"||openCards[i]->suit=="d")&&(currentActiveCard->suit=="s"||currentActiveCard->suit=="c"))||
                     ((openCards[i]->suit=="s"||openCards[i]->suit=="c")&&(currentActiveCard->suit=="h"||currentActiveCard->suit=="d")))){
                openNearCards.append(openCards[i]);
                openNearCardsSets.append(openCardsSets[i]);
                openNearCardsDistance.append(sqrt((thX-nowX)*(thX-nowX)+(thY-nowY)*(thY-nowY)));
            }
            openNearCards.removeAll(currentActiveCard);
            openNearCardsSets.removeAll(activeCardSet);
        }
    }
    if(!readyCards.isEmpty()){
        for (int i = 0; i < readyCards.length(); i++) {
            int thX = readyCards[i]->x(), thY = readyCards[i]->y();
            if(abs(thX-nowX)<=143&&abs(thY-nowY)<=200&&currentActiveCard->cardValue-readyCards[i]->cardValue==1&&
                    readyCards[i]->suit==currentActiveCard->suit){

                qDebug()<<currentActiveCard->suit<<"this";
                readyNearCards.append(readyCards[i]);
                readyNearCardsSets.append(readyCardsSets[i]);
                readyNearCardsDistance.append(sqrt((thX-nowX)*(thX-nowX)+(thY-nowY)*(thY-nowY)));
            }
            readyNearCards.removeAll(currentActiveCard);
            readyNearCardsSets.removeAll(activeCardSet);
        }
    }
}

void MainWindow::isThisCardOpen(){
    for (int i = 0; i<floorSets.length();i++){
        if(floorSets[i].isEmpty()==0){
            openCards.append(floorSets[i].last());
            openCardsSets.append(&floorSets[i]);
        }      
    }
    for (int i = 0; i<readySets.length();i++){
        if(readySets[i].isEmpty()==0){
            readyCards.append(readySets[i].last());
            readyCardsSets.append(&readySets[i]);
        }
    }
    //----------------------------------------------------------
    if(currentActiveCard->cardValue==1){
        for(int i=0;i<readyPlaces.length();i++){
            if(readySets[i].isEmpty()){
                openCardPlaces.append(readyPlaces[i]);
                openCardPlacesSets.append(&readySets[i]);
            }
        }
    }
    if(currentActiveCard->cardValue==13){
        for(int i=0;i<floorPlaces.length();i++){
            if(floorSets[i].isEmpty()){
                openCardPlaces.append(floorPlaces[i]);
                openCardPlacesSets.append(&floorSets[i]);
            }
        }
    }
    qDebug()<<openCardPlaces.length();
}

void MainWindow::bestPlace(){
    int bestPlace=0,bestCard=0,bestRCard=0;
    //--------------Place--------------
    if(!openNearCardPlaces.isEmpty()){
        for(int i = 1;i<openNearCardPlaces.length();i++) {
            if(openNearCardPlacesDistance[bestPlace]>openNearCardPlacesDistance[i])
            {
                bestPlace=i;
                qDebug()<<"bestPlace";
            }
            qDebug()<<"bestPlace";
        }
    }
    qDebug()<<openNearCardPlaces.length();
    //--------------Card---------------
    if(!openNearCards.isEmpty()){
        for (int i = 1;i<openNearCards.length();i++) {
            if(openNearCardsDistance[bestCard]>openNearCardsDistance[i])bestCard=i;
        }
    }
    if(!readyNearCards.isEmpty()){
        for (int i = 1;i<readyNearCards.length();i++) {
            if(readyNearCardsDistance[bestRCard]>readyNearCardsDistance[i])bestRCard=i;
        }
    }

    //-----------------Mooving to best of all-------------------------

    QString goTo ="";
    if(!openNearCards.isEmpty()){
        goTo = "openNearCards";
        if(!readyNearCards.isEmpty()){
            if(!openNearCardPlaces.isEmpty()&&bestPlace != -1){
                //openNearCards VS readyNearCards VS openNearCardPlaces
                if(openNearCardsDistance[bestCard]>readyNearCardsDistance[bestRCard]){
                    goTo = "readyNearCards";
                    if(readyNearCardsDistance[bestRCard]>openNearCardPlacesDistance[bestPlace]){
                        goTo = "openNearCardPlaces";
                    }
                }
            }else{
                //openNearCards VS readyNearCards
                if(openNearCardsDistance[bestCard]>readyNearCardsDistance[bestRCard]){
                    goTo = "readyNearCards";
                }
            }
        }else{
            if(!openNearCardPlaces.isEmpty()&&bestPlace != -1){
                //openNearCards VS openNearCardPlaces
                if(openNearCardsDistance[bestCard]>openNearCardPlacesDistance[bestPlace]){
                    goTo = "openNearCardPlaces";
                }
            }else{
                //openNearCards
            }
        }
    }else{
        if(!readyNearCards.isEmpty()){
            goTo = "readyNearCards";
            if(!openNearCardPlaces.isEmpty()&&bestPlace != -1){
                //readyNearCards VS openNearCardPlaces
                if(readyNearCardsDistance[bestRCard]>openNearCardPlacesDistance[bestPlace]){
                    goTo = "openNearCardPlaces";
                }
            }else{
                //readyNearCards
            }
        }else{
            if(!openNearCardPlaces.isEmpty()&&bestPlace != -1){
                //openNearCardPlaces
                goTo = "openNearCardPlaces";
            }else{
                //empty
                goTo ="";
            }
        }
    }

    qDebug()<<goTo<<bestPlace;
    if(goTo !=""){
        if(goTo=="openNearCards"){
            qDebug()<<"!";
            currentActiveCard->move(openNearCards[bestCard]->x(),openNearCards[bestCard]->y()+40);
            openNearCardsSets[bestCard]->append(currentActiveCard);
        }else if(goTo =="readyNearCards"){
            currentActiveCard->move(readyNearCards[bestRCard]->x(),readyNearCards[bestRCard]->y());
            readyNearCardsSets[bestRCard]->append(currentActiveCard);
        }else{
            currentActiveCard->move(openNearCardPlaces[bestPlace]->x(),openNearCardPlaces[bestPlace]->y());
            openNearCardPlacesSets[bestPlace]->append(currentActiveCard);
            if(!newGroup.isEmpty()){
                for (int i = 0;i<newGroup.length();i++){
                    openNearCardPlacesSets[bestPlace]->append(newGroup[i]);
                    activeCardSet->removeAll(newGroup[i]);
                }
                stopGroup();
            }
        }
        activeCardSet->removeAll(currentActiveCard);
        openNextFloorCard();
    }else{
        currentActiveCard->move(whichCardX,whichCardY);
    }
}

void MainWindow::bestGroupPlace(){
    qDebug()<<"here";

    int bestCard=0;
    for (int i = 1;i<openNearCards.length();i++) {
        if(openNearCardsDistance[bestCard]>openNearCardsDistance[i])bestCard=i;
    }
    currentActiveCard->move(openNearCards[bestCard]->x(),openNearCards[bestCard]->y()+40);
    openNearCardsSets[bestCard]->append(currentActiveCard);
    for (int i = 0;i<newGroup.length();i++){
        openNearCardsSets[bestCard]->append(newGroup[i]);
        activeCardSet->removeAll(newGroup[i]);
    }
    stopGroup();
    activeCardSet->removeAll(currentActiveCard);
    openNextFloorCard();
}

void MainWindow::openNextFloorCard(){
    if(!activeCardSet->isEmpty()&&isFloorSet){
        activeCardSet->last()->setOpen();
        activeCardSet->last()->isBlock = false;
    }
}

void MainWindow::fromWhatPlace(){
    isFloorSet = 0;
    isGroup = 0;

    int n = deckCards.length();
    if(n<floorSets.length()) n = floorSets.length();
    else if(n<readySets.length()) n = readySets.length();

    for (int i = 0;i<n;i++) {
        if(i<readySets.length()&& !readySets[i].isEmpty()&&
                readySets[i].last()==currentActiveCard){
            activeCardSet=&readySets[i];
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
        }
    }
    if(activeCardSet==nullptr){
        for (int i = 0;i<floorSets.length();i++){
            if(floorSets[i].isEmpty())continue;
            for (int j = 0;j<floorSets[i].length();j++){
                if(floorSets[i][j]==currentActiveCard){
                    activeCardSet=&floorSets[i];
                    isFloorSet=1;
                    isGroup=1;
                }
            }
        }
    }
}

void MainWindow::emptyPlaces(){
}
//------------------ForGroups------------------

void MainWindow::realizeGroup(){
    qDebug()<<"groupFunction";

    QList <myCards*> thisCardSet = *activeCardSet;
    bool currentCardInGroup = false;

    for(int i = 0;i<activeCardSet->length();i++){
        if (!currentCardInGroup&&thisCardSet[i]==currentActiveCard)currentCardInGroup=true;
        else if(currentCardInGroup){
            newGroup.append(thisCardSet[i]);
        }
    }
}

void MainWindow::moveGroup(){
    if(!newGroup.isEmpty()){
        int x =currentActiveCard->x(),y=currentActiveCard->y();
        for(int i = 0;i<newGroup.length();i++){
            int plus = 20 + i*20;
            newGroup[i]->move(x,y+plus);
            newGroup[i]->raise();
        }
    }
}

void MainWindow::stopGroup(){
    if(!newGroup.isEmpty()){
        int x =currentActiveCard->x(),y=currentActiveCard->y();
        for(int i = 0;i<newGroup.length();i++){
            int plus = 40 + i*40;
            newGroup[i]->move(x,y+plus);
        }
    }
}
