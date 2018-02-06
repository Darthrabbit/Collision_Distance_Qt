#ifndef BEGRENZUNG_H
#define BEGRENZUNG_H

#include "collisionPoint.h"

#include <QGraphicsPathItem>
#include <QPainter>
enum BEGRENZUNGSTYP{GERADE_OBEN, GERADE_UNTEN, GERADE_RECHTS, GERADE_LINKS};
//LINKS_LINKS, LINKS_RECHTS, RECHTS_RECHTS, RECHTS_LINKS,
class Begrenzung : public QGraphicsPathItem
{
public:
    Begrenzung(BEGRENZUNGSTYP t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    std::vector<CollisionCheckPoint*> boundCheckPoints() const;
    int type() const;
    void print();
    enum {Type = UserType + 1};

private:
    BEGRENZUNGSTYP begType;
    std::vector<CollisionCheckPoint*> vec_boundCheckPoints;
};

#endif // BEGRENZUNG_H
