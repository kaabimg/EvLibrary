#ifndef EVOBJECTSFINDER_H
#define EVOBJECTSFINDER_H

#include "EvObjectsContainer.h"

struct EvObjectsFinder
{
    struct FindData {
        QString regexp;
        int objectType;
    };

    static QList<EvObject*> find(const FindData & data, const EvObject * parent);

};

#endif // EVOBJECTSFINDER_H
