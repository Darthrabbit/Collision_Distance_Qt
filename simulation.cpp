#include "simulation.h"
#include "ui_simulation.h"
#include <QDebug>
Simulation::Simulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simulation), ptr_simScene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->ptr_simView->setScene(ptr_simScene);

    setVehicle(new Fahrzeug(80, 80, 100));

    addPath(new Begrenzung(GERADE_OBEN), 150, -150);
    addPath(new Begrenzung(GERADE_OBEN), 50, -150);
    addPath(new Begrenzung(GERADE_OBEN), -50, -150);
    addPath(new Begrenzung(GERADE_RECHTS), -150, -150);

    addPath(new Begrenzung(GERADE_UNTEN), 150, -150);
    addPath(new Begrenzung(GERADE_RECHTS), 50, -50);
    addPath(new Begrenzung(GERADE_LINKS), 50, -50);
    addPath(new Begrenzung(GERADE_UNTEN), -50, -150);
}

Simulation::~Simulation()
{
    delete ui;
    ptr_simScene->clear();
    delete ptr_simScene;
    delete ptr_simTimer;
}

void Simulation::addPath(Begrenzung *ptr_newPath, qreal x, qreal y)
{
    ptr_newPath->setPos(x,y);
    vec_simPath.push_back(ptr_newPath);
    ptr_simScene->addItem(ptr_newPath);
}

void Simulation::setVehicle(Fahrzeug *ptr_newVehicle)
{
    if(ptr_simVehicle != nullptr)
    {
        delete ptr_simVehicle;
    }
    ptr_simVehicle = ptr_newVehicle;
    ptr_simScene->addItem(ptr_simVehicle);
    ptr_simVehicle->setPos(ptr_simVehicle->x(), ptr_simVehicle->y());
}

void Simulation::startSimulation()
{
    if(simulationRunning == false)
    {
        ptr_simTimer = new QTimer();
        connect(ptr_simTimer, SIGNAL(timeout()), ptr_simScene, SLOT(advance()));
        connect(ptr_simTimer, SIGNAL(timeout()), ui->ptr_simView->viewport(), SLOT(repaint()));
        connect(ptr_simTimer, SIGNAL(timeout()), this, SLOT(checkVehicleCollision()));

        ptr_simTimer->setInterval(1000.0/ 40.0);
        ptr_simTimer->start();
        simulationRunning = true;
    }
}

void Simulation::stopSimulation()
{
    if(simulationRunning == true)
    {
        ptr_simTimer->stop();
        disconnect(ptr_simTimer, SIGNAL(timeout()), ptr_simScene, SLOT(advance()));
        disconnect(ptr_simTimer, SIGNAL(timeout()), ui->ptr_simView->viewport(), SLOT(repaint()));
        disconnect(ptr_simTimer, SIGNAL(timeout()), this, SLOT(checkVehicleCollision()));
        delete ptr_simTimer;
        ptr_simTimer = nullptr;
        simulationRunning = false;
    }
}

void Simulation::keyPressEvent(QKeyEvent *event)
{
    if(ptr_simVehicle)
    {
        if(event->key() == Qt::Key_W)
        {
            ptr_simVehicle->accelerate();
            return;
        }
        if(event->key() == Qt::Key_S)
        {
            ptr_simVehicle->reverse();
            return;
        }

        if(event->key() == Qt::Key_A)
        {
            ptr_simVehicle->changeDirection(-1);
            return;
        }
        if(event->key() == Qt::Key_D)
        {
            ptr_simVehicle->changeDirection(1);
            return;
        }
    }
}

void Simulation::keyReleaseEvent(QKeyEvent *event)
{
    if(ptr_simVehicle)
    {
        if(event->key() == Qt::Key_W || event->key() == Qt::Key_S)
        {
            ptr_simVehicle->stop();
            return;
        }

    }
}

void Simulation::on_ptr_buttonStart_clicked()
{
    startSimulation();
}

void Simulation::on_ptr_buttonStop_clicked()
{
    stopSimulation();
}

void Simulation::checkVehicleCollision()
{
    for(auto &it : ptr_simVehicle->collidingItems())
    {
        Begrenzung* collision = qgraphicsitem_cast<Begrenzung*>(it);
        if(collision)
        {
            stopSimulation();
            return;
        }
    }
}
