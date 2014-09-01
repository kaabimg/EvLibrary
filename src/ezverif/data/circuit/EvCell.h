#ifndef EVDESIGN_H
#define EVDESIGN_H

#include "../../../application/core/base/EvObject.h"
#include "EvState.h"
#include "EvSchematic.h"

class EvSchematic;

class EvCell : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Design,Cell,1,0)
    EV_TYPE_LABEL("Cell")
    EV_CHILDREN_INTERFACE_4(Process,Schematic,State,Simulation)


public:
    Q_INVOKABLE explicit EvCell(QObject * parent = 0);
};

#endif // EVDESIGN_H
