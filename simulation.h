#ifndef SIMULATION_H
#define SIMULATION_H

#include "begrenzung.h"
#include "fahrzeug.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>
#include <vector>


namespace Ui {
class Simulation;
}

class Simulation : public QWidget
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = 0);
    ~Simulation();
    void addPath(Begrenzung *ptr_newPath, qreal x, qreal y);
    void setVehicle(Fahrzeug* ptr_newVehicle);
    void startSimulation();
    void stopSimulation();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void on_ptr_buttonStart_clicked();
    void on_ptr_buttonStop_clicked();

    void checkVehicleCollision();

private:
    Ui::Simulation *ui;
    QGraphicsScene* ptr_simScene;
    Fahrzeug* ptr_simVehicle = nullptr;
    std::vector< Begrenzung* > vec_simPath;
    QTimer* ptr_simTimer = nullptr;
    bool simulationRunning = false;
};

#endif // SIMULATION_H
