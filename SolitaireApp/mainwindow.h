#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mycards.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void deckRange();

public slots:
    void deckRange();
    void test();

signals:

private slots:
    void newGame();
    void nextCard();
    void gameplay();
    void createSets();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H