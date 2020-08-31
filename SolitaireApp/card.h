#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Card : public QLabel, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr);

signals:

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};

#endif // CARD_H
