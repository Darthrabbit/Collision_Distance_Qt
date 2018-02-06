#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include "sensor.h"
#include "collisionPoint.h"
#include <QGraphicsEllipseItem>

class Fahrzeug : public QGraphicsEllipseItem
{
public:
    Fahrzeug(qreal posX, qreal posY, int anzSensors);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);    
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void accelerate();
    void stop();
    void reverse();
    void move();
    void changeDirection(double alpha);
    void checkSensors();

    std::vector<Sensor*> vec_Sensors() const;
    void setNewDirection(double newDir);
private:
    /*Functions*/
    void rotate();
    void rotateSensor(Sensor* sensor, double alpha);
    void rotateFront();

    /*Attributes*/
    int rad = 10;
    double direction = M_PI / 2.0;
    QPointF front = QPointF(0.0, rad);
    double rotation = M_PI / 10.0;
    int speed = 0;
    int maxSpeed = 5;

    double newDirection = direction;

    int sensorLength = 50;
    std::vector<Sensor*> vec_vehSensors;
    CollisionCheckPoint* nearestCollision = nullptr;
    double collisionDistance = -1.0;
};
#endif // FAHRZEUG_H
