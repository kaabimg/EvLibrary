#ifndef EVJOBSMANAGER_H
#define EVJOBSMANAGER_H

#include <QObject>
#include "EvJob.h"

class EvJobsManager : public QObject
{
    Q_OBJECT
public:
    explicit EvJobsManager(QObject *parent = 0);
    void submitJob(EvJob*);

Q_SIGNALS:
    void jobSubmitted(EvJob*);
    void jobFinished(EvJob*);

protected Q_SLOTS:
    void onJobStateChanged(EvJob::State);

};

#endif // EVJOBSMANAGER_H
