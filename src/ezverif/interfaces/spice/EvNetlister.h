#ifndef EVNETLISTER_H
#define EVNETLISTER_H

#include "../../../application/core/base/EvObject.h"

class EvNetlister : public EvObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit EvNetlister(QObject *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // EVNETLISTER_H
