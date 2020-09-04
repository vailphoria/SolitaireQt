#include "place.h"

Place::Place(QWidget *parent) : QLabel(parent)
{
    QPixmap pix(":/img/pictures/cards/place.png");
    this->setPixmap(pix);
    this->setFixedSize(143,200);
}
