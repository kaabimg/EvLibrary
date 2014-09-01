#ifndef EVAPPLICATIONDOCUMENTATION_H
#define EVAPPLICATIONDOCUMENTATION_H

#include "EvObject.h"

class EvApplicationDocumentation : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Core,ApplicationDocumentation,1,0)
    EV_CHILDREN_INTERFACE_1(Documentation)

public:
    Q_INVOKABLE explicit EvApplicationDocumentation(QObject *parent = 0);


};

#endif // EVAPPLICATIONDOCUMENTATION_H
