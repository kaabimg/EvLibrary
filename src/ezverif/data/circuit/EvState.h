#ifndef EVSTATE_H
#define EVSTATE_H

#include "../../../application/core/base/EvObject.h"


class EvState : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Design,State,1,0)
    EV_TYPE_LABEL("State")
public:
    Q_INVOKABLE explicit  EvState(QObject *parent = 0);

};

#endif // EVSTATE_H
