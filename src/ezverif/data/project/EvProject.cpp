#include "EvProject.h"

#include "../../data/simulation/EvSimulation.h"
#include "../circuit/EvCell.h"

struct EvProjectPrivate{
    QString path;
};


EvProject::EvProject(QObject *parent) :
    EvObject(parent),d_ptr(new EvProjectPrivate)
{

}

EvProject::~EvProject()
{
    delete d_ptr;
}

QString EvProject::path() const
{
    return d_ptr->path;
}

void EvProject::read(const QString &path)
{
    Q_UNUSED(path);
}

void EvProject::save()
{

}

void EvProject::saveAs(const QString &)
{

}

void EvProject::deleteFiles()
{

}
