#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include "sensor.h"
#include "collisionPoint.h"
#include <QGraphicsEllipseItem>

class Fahrzeug : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
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

    std::vector<Sensor*> vec_Sensors() const;
    void setNewDirection(double newDir);
    int type() const;
    enum { Type = UserType + 1};
public slots:
    void checkSensors();

private:
    /*Functions*/
    void rotate();
    void rotateSensor(Sensor* sensor, qreal alpha);
    void rotateFront();

    /*Attributes*/
    int rad = 10;
    double direction = M_PI / 2.0;
    QPointF front = QPointF(0.0, rad - 2);
    double rotation = M_PI / 10.0;
    int speed = 0;
    int maxSpeed = 5;

    double newDirection = direction;

    int sensorLength = 60;
    std::vector<Sensor*> vec_vehSensors;
    CollisionCheckPoint* nearestCollision = nullptr;
    double collisionDistance = -1.0;
};
#endif // FAHRZEUG_H
