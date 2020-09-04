#ifndef PLACE_H
#define PLACE_H

#include <QLabel>

class Place : public QLabel
{
    Q_OBJECT
public:
    explicit Place(QWidget *parent = nullptr);
    bool isEmpty = true;

signals:

};

#endif // PLACE_H
