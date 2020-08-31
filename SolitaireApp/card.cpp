#include "card.h"

Card::Card(QWidget *parent) : QLabel(parent), QGraphicsItem()
{

}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    //this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    //this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
