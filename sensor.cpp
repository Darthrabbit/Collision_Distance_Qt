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

void Sensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsLineItem::paint(painter, option, widget);
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    for(auto &it : vec_senCheckPoints)
    {
        pen.setColor((it->state == AKTIV ? Qt::red : Qt::black));
        painter->setPen(pen);
        painter->drawEllipse(QPoint(it->x, it->y), 1,1);
    }
}
