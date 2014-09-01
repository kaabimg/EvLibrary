#ifndef EVCIRCUITTYPES_H
#define EVCIRCUITTYPES_H

#include "EvObjectsManagement.h"
#include "EvCell.h"
#include "EvState.h"
#include "EvSchematic.h"


namespace EvCircuitModule {
void registerTypes () {
    mgcRegisterType<EvCell>();
    mgcRegisterType<EvState>();
    mgcRegisterType<EvSchematic>();

    qmlRegisterType<EvCell>("Ev.Design",1,0,"Cell");
    qmlRegisterType<EvState>("Ev.Design",1,0,"State");
    qmlRegisterType<EvSchematic>("Ev.Design",1,0,"Schematic");


}
}
#endif // EVCIRCUITTYPES_H
