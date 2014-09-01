#ifndef EVPLUGINGSMANAGER_H
#define EVPLUGINGSMANAGER_H

#include <QString>
#include "EvPlugin.h"
#include "EvSystem.h"

class EvWidget;

struct EvPluginsByVersion {
    QMap<EvVersion ,EvPlugin*> versions;
};

struct EvPluginsContainer {
    QMap<QString,EvPluginsByVersion> ids;

    void add(EvPlugin* plugin);
    void remove(EvPlugin* plugin,bool del = true);

};

class EvPluginsManager
{
public:
    EvPluginsManager();


    static QStringList supportedPluginsLibrariesExtensions();

    void addPlugin(EvPlugin *,const QString & sourcePathInfo = "");
    void addPlugins(const QList<EvPlugin*> & plugins,const QString & sourcePathInfo = "");

    void removePlugin(EvPlugin*);
    bool constainsPlugin(const EvPluginDependency & )const;
    bool constainsPlugin(EvPluginInfo::Type, const QString & id, const EvVersion & version = EvVersion() )const;
    void terminatePluginsCreation();

    void loadPluginsFromLibrary(const QString &path);
    void loadPluginsFromDirectory(const QString &path);

    template<typename T>
    T * plugin(EvPluginInfo::Type,const QString & id,const EvVersion & version = EvVersion());

    QList<QObject *> latestVersionsOf(EvPluginInfo::Type);


protected:
    EvPlugin * findPlugin(EvPluginInfo::Type,const QString & id,const EvVersion & version = EvVersion())const;
    bool isPluginCandidate(EvPlugin*)const;
    QObject * createInstance(EvPluginInfo::Type,const QString & id,const EvVersion & version = EvVersion());


private:
    QMap<EvPluginInfo::Type,EvPluginsContainer> types;
    QList<EvPlugin*> allPlugins;
    EvSystem output;
};

template<typename T>
T *EvPluginsManager::plugin(EvPluginInfo::Type type, const QString &id, const EvVersion &version)
{
    return qobject_cast<T*>(createInstance(type,id,version));
}

#endif // EVPLUGINGSMANAGER_H
