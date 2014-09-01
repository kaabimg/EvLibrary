#ifndef EVSIMULATOR_H
#define EVSIMULATOR_H

#include "EvObject.h"


class EvSimulator : public EvObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit EvSimulator(QObject *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // EVSIMULATOR_H
