#include "begrenzung.h"
#include <QDebug>
Begrenzung::Begrenzung(BEGRENZUNGSTYP t)
    : begType(t)
{
    QPainterPath path;
    int anzSensorenGerade = 10;
    switch(t)
    {
    case GERADE_OBEN :
        path.moveTo(50.0, -50.0);
        path.lineTo(-50.0, -50.0);
        for(int i = 0; i < anzSensorenGerade; i++)
        {
            CollisionCheckPoint* temp = new CollisionCheckPoint;
            temp->x = 50.0 + i * (-100.0 / anzSensorenGerade);
            temp->y = -50;
            temp->parent = this;
            vec_boundCheckPoints.push_back(temp);
        }
        break;
    case GERADE_UNTEN :
        path.moveTo(50.0, 50.0);
        path.lineTo(-50, 50.0);
        for(int i = 0; i < anzSensorenGerade; i++)
        {
            CollisionCheckPoint* temp = new CollisionCheckPoint;
            temp->x = 50.0 + i * (-100.0 / anzSensorenGerade);
            temp->y = 50;
            temp->parent = this;
            vec_boundCheckPoints.push_back(temp);
        }
        break;
    case GERADE_RECHTS:
        path.moveTo(50.0, 50.0);
        path.lineTo(50.0, -50.0);
        for(int i = 0; i < anzSensorenGerade; i++)
        {
            CollisionCheckPoint* temp = new CollisionCheckPoint;
            temp->y = 50.0 + i * (-100.0 / anzSensorenGerade);
            temp->x = 50;
            temp->parent = this;
            vec_boundCheckPoints.push_back(temp);
        }
        break;
    case GERADE_LINKS:
        path.moveTo(-50.0, 50.0);
        path.lineTo(-50.0, -50.0);
        for(int i = 0; i < anzSensorenGerade; i++)
        {
            CollisionCheckPoint* temp = new CollisionCheckPoint;
            temp->y = 50.0 + i * (-100.0 / anzSensorenGerade);
            temp->x = -50;
            temp->parent = this;
            vec_boundCheckPoints.push_back(temp);
        }
        break;
    }
    this->setPath(path);
}

void Begrenzung::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPathItem::paint(painter, option, widget);
    QPen pen;
    QBrush brush;

    pen.setWidth(3);
    brush.setStyle(Qt::SolidPattern);

    for(auto &it : vec_boundCheckPoints)
    {
        pen.setColor((it->state == AKTIV ? Qt::red : Qt::black));
        brush.setColor(pen.color());
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(QPoint(it->x, it->y), 1,1);
    }
}

std::vector<CollisionCheckPoint *> Begrenzung::boundCheckPoints() const
{
    return vec_boundCheckPoints;
}

int Begrenzung::type() const
{
    return Type;
}

void Begrenzung::print()
{
    qDebug() << "Begrenzung: " << "\n\t Typ: " << begType;
}

//case LINKS_LINKS :
//    path.moveTo(-50.0, 0.0);
//    path.arcTo(-150.0, -100.0, 100.0, 100.0, 0.0, 90.0);
//    path.moveTo(-100, -100);
//    path.lineTo(-100, -100);
//    break;
//case LINKS_RECHTS :
//    path.moveTo(-50.0, 0.0);
//    path.arcTo(150.0, 0.0, -200.0, -200.0, 0.0, -90.0);
//    path.moveTo(50, -200);
//    path.lineTo(100, -200);
//    break;
//case RECHTS_RECHTS :
//    path.moveTo(50.0, 0.0);
//    path.arcTo(150.0, 0.0, -100.0, -100.0, 0.0, -90.0);
//    path.moveTo(100.0, -100.0);
//    path.lineTo(100.0, -100.0);
//    break;
//case RECHTS_LINKS :
//    path.moveTo(50.0, 0.0);
//    path.arcTo(-150.0, -200.0, 200.0, 200.0, 0.0, 90.0);
//    path.moveTo(-50, -200);
//    path.lineTo(-100, -200);
//    break;
