#include "begrenzung.h"
#include "sensor.h"
#include <QDebug>
#include <QtMath>
Sensor::Sensor(qreal sX, qreal sY, qreal eX, qreal eY, int l, int numberPoints, QGraphicsItem *parent)
    : QGraphicsLineItem(sX,sY,eX,eY, parent), length(l)
{
    qreal distX = eX - sX;
    qreal gradient = (distX != 0 ? (eY -sY) / distX : 0);
    qreal b = sY - gradient * sX;

    for(int i = 1; i <= numberPoints; i++)
    {
        CollisionCheckPoint* temp = new CollisionCheckPoint;

        temp->x = sX + i / static_cast<double>(numberPoints) * (eX - sX);
        temp->y = (distX != 0 ? temp->x * gradient : temp->x + i / static_cast<double>(numberPoints) * (eY - sY)) + b;
        vec_senCheckPoints.push_back(temp);
    }
    setPos(0,0);
}

void Sensor::setPosition(qreal sX, qreal sY, qreal eX, qreal eY)
{
    qreal distX = eX - sX;
    qreal gradient = (distX != 0 ? (eY -sY) / distX : 0);
    qreal b = sY - gradient * sX;

    setLine(sX, sY, eX, eY);
    double size = vec_senCheckPoints.size();

    for(unsigned i = 1; i <= size; i++)
    {
        CollisionCheckPoint* current = vec_senCheckPoints[i - 1];
        current->x = sX + i / size * (eX - sX);
        current->y = (distX != 0 ?  current->x * gradient : current->x + i / size * (eY - sY)) + b;
    }
}

void Sensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    for(auto &it : vec_senCheckPoints)
    {
        if(it->state == AKTIV)
        {
            //painter->setOpacity(.5);
            //QGraphicsLineItem::paint(painter, nullptr, nullptr);
            //pen.setColor((it->state == AKTIV ? Qt::red : Qt::black));
            QPen pen;
            QBrush brush;

            pen.setWidth(3);
            brush.setStyle(Qt::SolidPattern);
            pen.setColor(Qt::red);
            brush.setColor(pen.color());
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawEllipse(QPoint(it->x, it->y), 1,1);
        }
    }
}

CollisionCheckPoint *Sensor::checkCollision()
{
    if(sensorCollosionPoint)
    {
        sensorCollosionPoint->state = INAKTIV;
        sensorCollosionPoint = nullptr;
    }

    CollisionCheckPoint* nearestCollisionPoint = nullptr;
    for(auto &it : collidingItems())
    {
        Begrenzung* collision = qgraphicsitem_cast<Begrenzung*>(it);
        if(collision)
        {
            qreal minDistance = 99999;
            for(auto &vec_sen : vec_senCheckPoints)
            {
                for(auto &vec_beg : collision->boundCheckPoints())
                {
                    QPointF mappedCoordinates = this->mapFromItem(vec_beg->parent, QPointF(vec_beg->x, vec_beg->y));

                    qreal tempDistance = qSqrt((vec_sen->x - mappedCoordinates.x()) * (vec_sen->x - mappedCoordinates.x()) +
                                               (vec_sen->y - mappedCoordinates.y()) * (vec_sen->y - mappedCoordinates.y()));
                    if(tempDistance < minDistance)
                    {
                        minDistance = tempDistance;
                        nearestCollisionPoint = vec_beg;
                        sensorCollosionPoint = vec_sen;
                    }
                }
            }
        }
    }

    if(sensorCollosionPoint)
    {
        sensorCollosionPoint->state = AKTIV;
    }
    return nearestCollisionPoint;
}
