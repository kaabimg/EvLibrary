#ifndef EVSIMULATIONVIEW_H
#define EVSIMULATIONVIEW_H
#include "EvWidget.h"
class EvSimulation;
class EvSimulationView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvSimulationView(EvSimulation * simulation,QWidget *parent = 0);

};

#endif // EVSIMULATIONVIEW_H
