#ifndef EVSCENARIO_H
#define EVSCENARIO_H

#include "EvObject.h"

class EvScenario : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Simulation,Scenario,1,0)
    EV_CHILDREN_INTERFACE_3(DeviceFamily,Parameter,Filter)

public:
    Q_INVOKABLE explicit EvScenario(QObject *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // EVSCENARIO_H
