#ifndef EVSIMULATION_H
#define EVSIMULATION_H

#include "../../../application/core/base/EvObject.h"

class EvSimulation : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Simulation,Simulation,1,0)
    EV_CHILDREN_INTERFACE_1(Scenario)


public:
    Q_INVOKABLE explicit EvSimulation(QObject *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // EVSIMULATION_H
