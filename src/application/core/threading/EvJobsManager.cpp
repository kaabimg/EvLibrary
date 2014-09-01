#include "EvJobsManager.h"

EvJobsManager::EvJobsManager(QObject *parent) :
    QObject(parent)
{
}


void EvJobsManager::submitJob(EvJob *)
{

}

void EvJobsManager::onJobStateChanged(EvJob::State state)
{
    EvJob * job = qobject_cast<EvJob *>(sender());

    Q_UNUSED(job );
    Q_UNUSED(state);
}
