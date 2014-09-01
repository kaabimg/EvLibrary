#ifndef EVSIMULATIONRUN_H
#define EVSIMULATIONRUN_H

#include <QVector>
#include "EvSpiceNumber.h"


class EvSimulationRunVariants
{
public:
    EvSimulationRunVariants(int parametersCount,int fdCount);
    struct DeviceFamilyData {
        QString library;
        QString corner;
    };

    EvSpiceNumber & parameter(int i);
    DeviceFamilyData & deviceFamily(int i);
private:
    QVector<EvSpiceNumber> m_parameters;
    QVector<DeviceFamilyData> m_deviceFamilies;

};


class EvSimulationRun
{
public:
    EvSimulationRun(int parametersCount,int fdCount);


private:
    EvSimulationRunVariants m_data;

};



#endif // EVSIMULATIONRUN_H
