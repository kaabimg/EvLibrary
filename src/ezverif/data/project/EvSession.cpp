#include "EvSession.h"

EvSession::EvSession(QObject *parent) :
    EvObject(parent)
{
}

void EvSession::addProject(const QString &path)
{
    EvProject  * project = create<EvProject>(this);
    project->read(path);
    add<EvProject>(project);
}


void EvSession::closeProject(EvProject *project)
{
    Q_EMIT projectDeleted(project);
    remove<EvProject>(project);
}
