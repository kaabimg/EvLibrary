#ifndef EVSIMULATIONTYPES_H
#define EVSIMULATIONTYPES_H


#include "EvObjectsManagement.h"
#include "EvSimulation.h"
#include "EvScenario.h"

namespace EvSimulationModule {
void registerTypes () {
    mgcRegisterType<EvSimulation>();
    mgcRegisterType<EvScenario>();

    qmlRegisterType<EvSimulation>("Ev.Simulation",1,0,"Simulation");
    qmlRegisterType<EvScenario>("Ev.Simulation",1,0,"Scenario");


}
}



#endif // EVSIMULATIONTYPES_H
