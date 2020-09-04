#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "mycards.h"
#include "place.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static myCards* currentActiveCard;

public slots:
    void deckRange();

signals:

private slots:
    void newGame();
    void nextCard();
    void gameplay();
    void createSets();
    void saveParameter();
    void whatCardsHere();
    void isThisCardOpen();
    void moveCardToBestPlace();
    void bestPlace();
    void fromWhatPlace();
    void emptyPlaces();
    void openNextFloorCard();


private:
    Ui::MainWindow *ui;

    QPropertyAnimation *anim1;
    QPropertyAnimation *anim2;

    QSequentialAnimationGroup *group;
};
#endif // MAINWINDOW_H
