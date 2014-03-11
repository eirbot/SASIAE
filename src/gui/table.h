#ifndef TABLE_H
#define TABLE_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsItemAnimation>
#include <QtGui>
#include "item_robot.h"

class Table : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = 0);
    QTimeLine *timer;
    //QGraphicsRectItem * robotItem;
    //void startAnimation();
signals:

public slots:

private:
    //QRectF robot;
    ItemRobot * robot;
    //QPropertyAnimation * anim;
    //int duration;
};

#endif // TABLE_H
