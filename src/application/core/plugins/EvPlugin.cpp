#include "EvPlugin.h"


EvPluginInfo::EvPluginInfo(EvPluginInfo::Type _type, QString _id, QString _description, int _minorVersion, int _majorVersion):
    type(_type),
    id(_id),
    description(_description),
    version(_majorVersion,_minorVersion){}


EvPlugin::EvPlugin():lastCreatedInstance(NULL){}

EvPlugin::~EvPlugin(){}

QList<EvPluginDependency> EvPlugin::dependencies() const{
    return QList<EvPluginDependency>();
}

QObject *EvPlugin::create(){
    if(lastCreatedInstance && mode() == Unique)
        return lastCreatedInstance;

    lastCreatedInstance = createOne();
    return lastCreatedInstance;
}

QString EvPlugin::loadFile() const
{
    return m_loadFile;
}

void EvPlugin::setLoadFile(const QString &file)
{
    m_loadFile = file;
}
