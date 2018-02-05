#include "fahrzeug.h"
#include <QtMath>
#include <QPainter>
#include <QDebug>
Fahrzeug::Fahrzeug(qreal posX, qreal posY, int anzSensors)
    : QGraphicsEllipseItem(posX, posY, rad,rad)
{
    setPos(posX, posY);
    setX(posX);
    setY(posY);
    for(int i = 0; i < anzSensors; i++)
    {
        vec_vehSensors.push_back(new Sensor(0, rad, 0, rad + sensorLength, sensorLength, 5, this));
        rotateSensor(vec_vehSensors[i], i * M_PI / (anzSensors - 1));
    }
}

void Fahrzeug::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(5);
    painter->setPen(pen);
    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->drawEllipse(QPoint(0,0), rad, rad);
}

void Fahrzeug::move()
{
    if(direction != newDirection)
        rotate(newDirection - direction);
    if(speed > 0)
    {
        setX(x() + qCos(direction) * speed);
        setY(y() + qSin(direction) * speed);
    }
}

void Fahrzeug::changeDirection(double alpha)
{
    newDirection += alpha;
}

void Fahrzeug::advance(int phase)
{
    if(phase == 0)
    {
        return;
    }
    move();
}

void Fahrzeug::rotate(double alpha)
{
    for(auto &it : vec_vehSensors)
    {
        rotateSensor(it, alpha);
    }
    direction = newDirection;
}

void Fahrzeug::accelerate(int tempSpeed)
{
    speed = tempSpeed;
}

std::vector<Sensor *>Fahrzeug::vec_Sensors() const
{
    return vec_vehSensors;
}

void Fahrzeug::setNewDirection(double newDir)
{
    newDirection = newDir;
}

void Fahrzeug::rotateSensor(Sensor *sensor, double alpha)
{
    qreal newXStart = qCos(alpha) * sensor->line().x1() - qSin(alpha) * sensor->line().y1();
    qreal newXEnd = qCos(alpha) * sensor->line().x2() - qSin(alpha) * sensor->line().y2();

    qreal newYStart = qSin(alpha) * sensor->line().x1() + qCos(alpha) * sensor->line().y1();
    qreal newYEnd = qSin(alpha) * sensor->line().x2() + qCos(alpha) * sensor->line().y2();

    sensor->setPosition(newXStart, newYStart, newXEnd, newYEnd);
}

/*
CollisionCheckPoint &Fahrzeug::checkCollisions()
{

}
*/
