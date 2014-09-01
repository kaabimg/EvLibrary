#include "EvSimulationRun.h"

EvSimulationRunVariants::EvSimulationRunVariants(int parametersCount, int fdCount):
    m_parameters(parametersCount),
    m_deviceFamilies(fdCount)
{

}

EvSpiceNumber &EvSimulationRunVariants::parameter(int i)
{
    return m_parameters[i];
}

EvSimulationRunVariants::DeviceFamilyData &EvSimulationRunVariants::deviceFamily(int i)
{
    return m_deviceFamilies[i];
}



EvSimulationRun::EvSimulationRun(int parametersCount, int fdCount):
    m_data(parametersCount,fdCount)
{

}
