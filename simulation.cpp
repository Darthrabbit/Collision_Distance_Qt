#include "simulation.h"
#include "ui_simulation.h"
#include <QDebug>
Simulation::Simulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simulation), ptr_simScene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->ptr_simView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->ptr_simView->setScene(ptr_simScene);

    ptr_simScene->setSceneRect(0,0,250,250);
    setVehicle(new Fahrzeug(50,50,5));
}

Simulation::~Simulation()
{
    delete ui;
    ptr_simScene->clear();
    delete ptr_simScene;
    delete ptr_simTimer;
}

void Simulation::addPath(Begrenzung *ptr_newPath)
{
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
    ptr_simTimer = new QTimer();
    connect(ptr_simTimer, SIGNAL(timeout()), ptr_simScene, SLOT(advance()));
    ptr_simTimer->setInterval(1000.0/ 40.0);
    ptr_simTimer->start();
}

void Simulation::stopSimulation()
{
    disconnect(ptr_simTimer, SIGNAL(timeout()), ptr_simScene, SLOT(advance()));
    delete ptr_simTimer;
    ptr_simTimer = nullptr;
}

void Simulation::keyPressEvent(QKeyEvent *event)
{
    int speed = 10;
    if(event->key() == Qt::Key_W)
    {
        ptr_simVehicle->accelerate(speed);
        return;
    }
    double rotation = M_PI / 10.0;
    if(event->key() == Qt::Key_A)
    {
        ptr_simVehicle->changeDirection(-rotation);
        return;
    }
    if(event->key() == Qt::Key_D)
    {
        ptr_simVehicle->changeDirection(rotation);
        return;
    }
}

void Simulation::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        ptr_simVehicle->accelerate(0);
        return;
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
