#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include "sensor.h"
#include "global.h"
#include <QGraphicsEllipseItem>

class Fahrzeug : public QGraphicsEllipseItem
{
public:
    Fahrzeug(qreal posX, qreal posY, int anzSensors);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void rotate(double alpha);
    void accelerate(int tempSpeed);
    void move();
    void changeDirection(double alpha);
    void advance(int phase);
    std::vector<Sensor*> vec_Sensors() const;

    void setNewDirection(double newDir);
    //CollisionCheckPoint& checkCollisions();
private:
    void rotateSensor(Sensor* sensor, double alpha);
    std::vector<Sensor*> vec_vehSensors;
    int rad = 10;
    int sensorLength = 30;
    double direction = M_PI;
    double newDirection = direction;
    int speed = 0;

    // QGraphicsItem interface
};

#endif // FAHRZEUG_H
