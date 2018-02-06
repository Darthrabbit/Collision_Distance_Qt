#ifndef COLLISIONPOINT
#define COLLISIONPOINT
#include <QtMath>

class QGraphicsItem;
enum STATE{AKTIV, INAKTIV};
struct CollisionCheckPoint
{
    qreal x, y;
    STATE state = INAKTIV;
    QGraphicsItem* parent  = nullptr;
};
#endif // COLLISIONPOINT

