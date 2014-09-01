#ifndef EVVARIATIONTYPES_H_
#define EVVARIATIONTYPES_H_

#include "EvObjectsManagement.h"
#include "EvCorner.h"
#include "EvFilter.h"
#include "EvDeviceFamily.h"
#include "EvLibrary.h"
#include "EvParameter.h"
#include "EvProcess.h"
#include "EvSimulationPlan.h"

namespace EvVariationModule {


void registerV1Types(){
    mgcRegisterType<EvCorner>();
    mgcRegisterType<EvFilter>();
    mgcRegisterType<EvDeviceFamily>();
    mgcRegisterType<EvLibrary>();
    mgcRegisterType<EvParameter>();
    mgcRegisterType<EvProcess>();
    mgcRegisterType<EvSimulationPlan>();
}


static void registerTypes () {

    registerV1Types();

    qmlRegisterType<EvCorner>("Ev.Variation",1,0,"Corner");
    qmlRegisterType<EvFilter>("Ev.Variation",1,0,"EvFilter");
    qmlRegisterType<EvDeviceFamily>("Ev.Variation",1,0,"DeviceFamily");
    qmlRegisterType<EvLibrary>("Ev.Variation",1,0,"Library");
    qmlRegisterType<EvParameter>("Ev.Variation",1,0,"Parameter");
    qmlRegisterType<EvProcess>("Ev.Variation",1,0,"Process");
    qmlRegisterType<EvSimulationPlan>("Ev.Variation",1,0,"SimulationPlan");

}

}


#endif /* EVVARIATIONTYPES_H_ */
