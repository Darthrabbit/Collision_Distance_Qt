#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "collisionPoint.h"
class Sensor : public QGraphicsLineItem
{
public:
    Sensor(qreal sX, qreal sY, qreal eX, qreal eY, int l, int numberPoints, QGraphicsItem* parent = 0);
    void setPosition(qreal sX, qreal sY, qreal eX, qreal eY);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    CollisionCheckPoint *checkCollision();
private:
    int length;
    std::vector<CollisionCheckPoint*> vec_senCheckPoints;
    CollisionCheckPoint* sensorCollosionPoint = nullptr;
};

#endif // SENSOR_H
