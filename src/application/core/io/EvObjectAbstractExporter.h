#ifndef EVOBJECTABSTRACTEXPORTER_H
#define EVOBJECTABSTRACTEXPORTER_H

#include "EvObject.h"

struct EvObjectAbstractExporter {

    QByteArray objectToString(const EvObject* object){
        QByteArray data;
        QTextStream out(&data);
        exportObject(object,out);
        return data;
    }

    virtual void exportObject(const EvObject* object,QTextStream & out)=0;

};

#endif // EVOBJECTABSTRACTEXPORTER_H
