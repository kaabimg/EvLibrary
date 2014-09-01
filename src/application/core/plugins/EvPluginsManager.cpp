#include "EvPluginsManager.h"

#include "EvSystem.h"

void EvPluginsContainer::add(EvPlugin *plugin){
    EvPluginInfo info = plugin->pluginInfo();
    EvPluginsByVersion & container = ids[info.id];
    container.versions.insert(info.version,plugin);
}

void EvPluginsContainer::remove(EvPlugin *plugin,bool del)
{
    EvPluginInfo info = plugin->pluginInfo();
    if(ids.contains(info.id)){
        EvPluginsByVersion & container = ids[info.id];
        if(container.versions.contains(info.version)){
            container.versions.take(info.version);
            if(del)
                delete plugin;
        }

    }
}

/////////////////////////////////////////////////////

EvPluginsManager::EvPluginsManager():output("Plugins manager")
{
}

QStringList EvPluginsManager::supportedPluginsLibrariesExtensions()
{
    static const QStringList list = QStringList()<<".so"<<".dll";
    return list;
}

void EvPluginsManager::addPlugin(EvPlugin * plugin, const QString &sourcePathInfo)
{

    EvPluginInfo info = plugin->pluginInfo();
    EvSystem::Message message;
    message << "Adding plugin '"<<info.id<<"'' "<<info.version;
    output.log(message);

    types[plugin->type()].add(plugin);
    allPlugins << plugin;
    plugin->setLoadFile(sourcePathInfo);


}

void EvPluginsManager::addPlugins(const QList<EvPlugin *> &plugins, const QString &sourcePathInfo)
{

    foreach (EvPlugin * plugin, plugins) {
        addPlugin(plugin,sourcePathInfo);
    }
}

void EvPluginsManager::removePlugin(EvPlugin * plugin)
{

    EvPluginInfo info = plugin->pluginInfo();
    EvSystem::Message message;
    message << "Removing plugin"<<info.id<<" "<<info.version;
    output.log(message);

    if(types.contains(plugin->type())){
        types[plugin->type()].add(plugin);
    }
    allPlugins.removeOne(plugin);
}


bool EvPluginsManager::constainsPlugin(EvPluginInfo::Type type, const QString &id, const EvVersion &version) const
{
    return findPlugin(type,id,version) != NULL;
}



EvPlugin *EvPluginsManager::findPlugin(EvPluginInfo::Type type, const QString &id, const EvVersion &version) const
{
    if( !types.contains(type) ||
            !types[type].ids.contains(id) ||
            types[type].ids[id].versions.isEmpty() )
    {
        return NULL;
    }

    if(!version.isValid()){// latest version
        return types[type].ids[id].versions.last();
    }

    if(types[type].ids[id].versions.contains(version)){
        return types[type].ids[id].versions[version];
    }

    return NULL;
}


QObject *EvPluginsManager::createInstance(EvPluginInfo::Type type, const QString &id, const EvVersion &version)
{
    EvPlugin * plugin = findPlugin(type,id,version);
    if(plugin)
        return plugin->create();

    return NULL;
}




bool EvPluginsManager::constainsPlugin(const EvPluginDependency & dependency) const
{
    if( !types.contains(dependency.dependentPluginType) ||
            !types[dependency.dependentPluginType].ids.contains(dependency.dependentPluginId))
    {
        return false;
    }

    if(types[dependency.dependentPluginType].ids[dependency.dependentPluginId].versions.isEmpty())
    {
        return false;
    }

    if(dependency.minVerion.isValid()){
        EvVersion minVersion =
                types[dependency.dependentPluginType].
                ids[dependency.dependentPluginId].
                versions.firstKey();

        if(minVersion> dependency.minVerion)
            return false;
    }

    if(dependency.maxVersion.isValid()){
        EvVersion maxVersion =
                types[dependency.dependentPluginType].
                ids[dependency.dependentPluginId].
                versions.lastKey();

        if(maxVersion< dependency.maxVersion)
            return false;
    }
    return true;
}

bool EvPluginsManager::isPluginCandidate(EvPlugin * plugin) const
{
    QList<EvPluginDependency> dependencies =plugin->dependencies();

    foreach(const EvPluginDependency& dependency,dependencies){
        if(!constainsPlugin(dependency))
            return false;
    }
    return true;
}



void EvPluginsManager::loadPluginsFromLibrary(const QString &path)
{

    output.log("Loading plugins from "+path);

    QFileInfo file(path);
    if(!file.exists()){
        EvSystem::Message message;
        message << "Failed to open plugins library "<<path;
        message <<"File not found";
        output.error(message);
        return;

    }
    if(!file.isReadable()){
        EvSystem::Message message;
        message << "Failed to open plugins library "<<path;
        message << "File not readable";
        output.error(message);
        return;
    }


    QPluginLoader pluginLoader(path);
    QObject *plugin = pluginLoader.instance();

    if (plugin) {
        EvPluginsInterface * interface = qobject_cast<EvPluginsInterface *>(plugin);
        if (interface){
            addPlugins(interface->plugins(),path);
        }
        else {
            EvSystem::Message message;
            message << "Failed to load plugins from "+path;
            message << "The file "<<path<<" is not a plugin";
            output.error(message);
        }
    }
    else {
        EvSystem::Message message;
        message << "Failed to load plugins from "+path;
        message << "The file "<<path<<" is not a plugin";
        output.error(message);
    }
}

void EvPluginsManager::loadPluginsFromDirectory(const QString &path)
{
     QDir pluginsDir(path);
     foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
         foreach (const QString & extension, supportedPluginsLibrariesExtensions()) {
             if(fileName.endsWith(extension)){
                 loadPluginsFromLibrary(fileName);
             }
         }
     }
}



QList<QObject *> EvPluginsManager::latestVersionsOf(EvPluginInfo::Type type)
{
    QList<QObject*> instances;
    if(types.contains(type)){
        foreach(const QString & id, types[type].ids.keys()){
            instances<<types[type].ids[id].versions.last()->create();
        }
    }
    return instances;
}



void EvPluginsManager::terminatePluginsCreation()
{
    output.log("Terminating plugins creation ...");
    bool removed = true;

    while (removed) {
        removed = false;
        for(int i=0;i<allPlugins.size();++i){
            if(! isPluginCandidate(allPlugins[i])){
                removePlugin(allPlugins[i]);
                removed = true;
                --i;
            }
        }
    }
    for(int i=0;i<allPlugins.size();++i){
        if(!allPlugins[i]->init()){
            EvSystem::Message message;
            message << "Failed to initialise plugin"
                    <<allPlugins[i]->pluginInfo().id
                   <<" "<<allPlugins[i]->pluginInfo().version;
            output.error(message);
            removePlugin(allPlugins[i]);
            --i;
        }
    }
    output.log("Plugins creation terminated");
}
