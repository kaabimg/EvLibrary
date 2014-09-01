#ifndef EVPROJECT_H
#define EVPROJECT_H

#include "../../../application/core/base/EvObject.h"
class EvSimulation;
class EvCell;


class EvProjectPrivate;

class EvProject : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Session,Project,1,0)
    EV_TYPE_LABEL("Project")
    EV_CHILDREN_INTERFACE_1(Cell)

    Q_PROPERTY(QString path READ path NOTIFY pathChanged)

public:
    Q_INVOKABLE explicit  EvProject(QObject *parent = 0);
    ~EvProject();
    QString path() const;    
    bool isTopLevelObject()const{return true;}

Q_SIGNALS:
    void pathChanged(const QString &);

public Q_SLOTS:

    void read(const QString & path);
    void save();
    void saveAs(const QString & name);

    void deleteFiles();

private:
    EV_PRIVATE(EvProject)

};

#endif // EVPROJECT_H
