#ifndef MYCARDS_H
#define MYCARDS_H

#include <QLabel>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>

class myCards : public QLabel
{
public:
    Q_OBJECT
public:
    explicit myCards(QWidget *parent = nullptr);
    //static myCards* currentActiveCard;
    QString value = "suit";
    QString suit;
    int cardValue;
    double myStartX, myStartY, myEndX, myEndY;
    int lastX,lastY;
    QPixmap *pix;
    QPoint offset;
    bool isNew = true;
    bool isBlock = false;
    bool inDeck = true;
    bool onMove = false;
    void setValue(QString value);
    void distribution(double x0=0, double y0=0, double x1=0, double y1=0);

signals:
     void click();
     void moveCard();
     void stopCard();
     void movingGroup();

public slots:
    void setOpen();
    void setClosed();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYCARDS_H
