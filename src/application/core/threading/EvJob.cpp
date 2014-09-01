#include "EvJob.h"

EvJob::EvJob(QObject *parent) :
    QThread(parent)
{
    setMode(NormalMode);
}

void EvJob::setMode(EvJob::Mode mode)
{
   m_mode = mode;
}
