#ifndef EVSIMULATIONMANAGER_H
#define EVSIMULATIONMANAGER_H

#include "EvObject.h"

class EvSimulationManager : public EvObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit EvSimulationManager(QObject *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // EVSIMULATIONMANAGER_H
