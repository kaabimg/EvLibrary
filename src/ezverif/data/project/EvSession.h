#ifndef EVSESSION_H
#define EVSESSION_H
#include "../../../application/core/base/EvObject.h"
#include "EvProject.h"

class EvSession : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Session,Session,1,0)
    EV_TYPE_LABEL("Session")
    EV_CHILDREN_INTERFACE_1(Project)

public:
    Q_INVOKABLE explicit EvSession(QObject *parent = 0);

public Q_SLOTS:
    void addProject(const QString & path);
    void closeProject(EvProject* project);

Q_SIGNALS:
    void projectAdded(EvProject*);
    void projectDeleted(EvProject*);

};

#endif // EVSESSION_H
