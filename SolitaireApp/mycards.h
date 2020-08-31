#ifndef MYCARDS_H
#define MYCARDS_H

#include <QLabel>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>
//#include "mainwindow.h"

class myCards : public QLabel
{
    Q_OBJECT
public:
    QString value = "suit";
    double myStartX, myStartY, myEndX, myEndY;
    int lastX,lastY;
    QPixmap *pix;
    QPoint offset;
    bool isNew = true;
    bool isBlock = false;
    bool inDeck = true;
    explicit myCards(QWidget *parent = nullptr);
    void setValue(QString value);
    void distribution(double x0=0, double y0=0, double x1=0, double y1=0);
    void testPos();

signals:
     void click();

public slots:
    void step();
    void setOpen();
    void setClosed();
    void mousePressEvent(QMouseEvent *event);

private:
    void mouseMoveEvent(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYCARDS_H
