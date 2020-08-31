#include "clickablelabel.h"

QPoint offset;

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

ClickableLabel:: ~ClickableLabel() {}




void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->moveEvent()
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
     //При нажатии мышью на графический элемент
     //заменяем курсор на руку, которая держит этот элемента

    //this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
     //При отпускании мышью элемента
     //заменяем на обычный курсор стрелку

    //this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}


/*void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
    offset = event->pos()

}

void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->move(100,100);
}*/

