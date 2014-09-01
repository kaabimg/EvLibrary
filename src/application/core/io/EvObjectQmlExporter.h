#ifndef EVOBJECTQMLEXPORTER_H
#define EVOBJECTQMLEXPORTER_H

#include "EvObjectAbstractExporter.h"

struct EvObjectQmlExporter :  EvObjectAbstractExporter
{
    void exportObject(const EvObject* object, QTextStream & out);
};

#endif // EVOBJECTQMLEXPORTER_H
