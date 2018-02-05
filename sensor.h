#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "global.h"
class Sensor : public QGraphicsLineItem
{
public:
    Sensor(qreal sX, qreal sY, qreal eX, qreal eY, int l, int numberPoints, QGraphicsItem* parent = 0);
    void setPosition(qreal sX, qreal sY, qreal eX, qreal eY);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int length;
    std::vector<CollisionCheckPoint*> vec_senCheckPoints;
};

#endif // SENSOR_H
