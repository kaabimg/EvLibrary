#ifndef SIMULATIONPLAN_H
#define SIMULATIONPLAN_H

#include "../../../application/core/base/EvObject.h"
#include "EvScenario.h"
#include "EvFilter.h"


class EvSimulationPlan : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Variation,SimulationPlan,1,0)
    EV_TYPE_LABEL("Simulation plan")
    EV_CHILDREN_INTERFACE_2(Scenario,Filter)
public:
    Q_INVOKABLE EvSimulationPlan(QObject *parent = 0);

Q_SIGNALS:


public Q_SLOTS:

private:

};

#endif // SIMULATIONPLAN_H
