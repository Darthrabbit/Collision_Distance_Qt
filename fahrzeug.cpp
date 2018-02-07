#include "fahrzeug.h"
#include <QtMath>
#include <QPainter>
#include <QDebug>
#include <QElapsedTimer>
Fahrzeug::Fahrzeug(qreal posX, qreal posY, int anzSensors)
    : QObject(0), QGraphicsEllipseItem(QRectF(posX, posY, rad,rad), 0)
{
    setPos(posX, posY);
    for(int i = 0; i < anzSensors; i++)
    {
        vec_vehSensors.push_back(new Sensor(0, rad, 0, rad + sensorLength, sensorLength, 20, this));
        rotateSensor(vec_vehSensors[i], i * 2  * M_PI / (anzSensors - 1));
    }
}

void Fahrzeug::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawEllipse(boundingRect());

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawEllipse(front, rad/5.0, rad/5.0);

    if(nearestCollision)
    {
        QPointF mappedCoordinates = this->mapFromItem(nearestCollision->parent,
                                                      QPointF(nearestCollision->x, nearestCollision->y));
        painter->drawText(QPointF(sensorLength + 10, 0),QString::number(collisionDistance - rad));
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawLine(QPointF(0,0), mappedCoordinates);
    }
}

void Fahrzeug::move()
{

    rotate();
    if(speed != 0)
    {
        setX(x() + qCos(direction) * speed);
        setY(y() + qSin(direction) * speed);
    }
}

void Fahrzeug::changeDirection(double sign)
{
    newDirection += sign * rotation;
}

void Fahrzeug::checkSensors()
{
    if(nearestCollision)
    {
        nearestCollision->state = INAKTIV;
        nearestCollision = nullptr;
        collisionDistance = -1.0;
    }
    qreal minDist = 9999.0;

    for(auto &it : vec_vehSensors)
    {
        CollisionCheckPoint* temp = it->checkCollision();
        if(temp)
        {
            QPointF mappedCoordinates = this->mapToParent(this->mapFromItem(temp->parent,QPointF(temp->x, temp->y)));
            qreal tempDistance = (x() - mappedCoordinates.x()) * (x() - mappedCoordinates.x()) +
                                       (y() - mappedCoordinates.y()) * (y() - mappedCoordinates.y());
            if(tempDistance < minDist)
            {
                minDist = tempDistance;
                nearestCollision = temp;
            }
        }
    }
    if(nearestCollision)
    {
        nearestCollision->state = AKTIV;
        collisionDistance = qSqrt(minDist);
    }
}

void Fahrzeug::advance(int phase)
{
    if(phase == 0)
    {
        return;
    }
    move();

}

QRectF Fahrzeug::boundingRect() const
{
    int shrink = 4;
    int diameter = 2 * rad;
    return QRectF(-rad + shrink, -rad + shrink, diameter - 2 * shrink, diameter- 2 * shrink);
}

QPainterPath Fahrzeug::shape() const
{
    QGraphicsEllipseItem temp(boundingRect(),0);
    return temp.shape();
}


void Fahrzeug::accelerate()
{
    speed = maxSpeed;
}

void Fahrzeug::stop()
{
    speed = 0;
}

void Fahrzeug::reverse()
{
    speed = -maxSpeed;
}

std::vector<Sensor *>Fahrzeug::vec_Sensors() const
{
    return vec_vehSensors;
}

void Fahrzeug::setNewDirection(double newDir)
{
    newDirection = newDir;
}

int Fahrzeug::type() const
{
    return Type;
}
void Fahrzeug::rotate()
{
    qreal alpha = newDirection - direction;
    if(alpha != 0)
    {
        if(2 * M_PI / static_cast<double>(vec_vehSensors.size()) >  rotation)
        {
            for(auto &it : vec_vehSensors)
            {
                rotateSensor(it, alpha);
            }
        }
        rotateFront();
        direction = newDirection;
    }
}
void Fahrzeug::rotateSensor(Sensor *sensor, qreal alpha)
{
    qreal newXStart = qCos(alpha) * sensor->line().x1() - qSin(alpha) * sensor->line().y1();
    qreal newXEnd = qCos(alpha) * sensor->line().x2() - qSin(alpha) * sensor->line().y2();

    qreal newYStart = qSin(alpha) * sensor->line().x1() + qCos(alpha) * sensor->line().y1();
    qreal newYEnd = qSin(alpha) * sensor->line().x2() + qCos(alpha) * sensor->line().y2();

    sensor->setPosition(newXStart, newYStart, newXEnd, newYEnd);
}

void Fahrzeug::rotateFront()
{
    qreal alpha = newDirection - direction;
    if(alpha != 0)
    {
        qreal newX = qCos(alpha) * front.x() - qSin(alpha) * front.y();
        qreal newY = qSin(alpha) * front.x() + qCos(alpha) * front.y();

        front.setX(newX); front.setY(newY);
    }
}
