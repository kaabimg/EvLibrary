#ifndef EVPLUGIN_H
#define EVPLUGIN_H

#include <QString>
#include <QtPlugin>
#include "EvObjectsManagement.h"
#include "EvGlobal.h"


struct EvPluginInfo {



    enum  Type{

        Main, // for dependencies
        //core
        Simulator,
        Netlister,
        Parser,
        SimulationResultsReader,
        Service,

        // graphical

        MainViewWidget,
        IOPane,
        IOPaneLeftWidget,
        IOPaneRightWidget,

        // io
        ProjectImport,
        ProjectExport
    };


    EvPluginInfo(
            Type _type,
            QString _id,
            QString _description,
            int _minorVersion,
            int _majorVersion);

    Type type;
    QString id;
    QString description;
    EvVersion version;
};

struct EvPluginDependency {
    EvPluginInfo::Type dependentPluginType;
    QString dependentPluginId;
    EvVersion minVerion;
    EvVersion maxVersion;
};



struct EvPlugin
{
    EvPlugin();
    virtual ~EvPlugin();

    enum InstanciationMode {
        Unique,
        Multiple
    };

    virtual EvPluginInfo::Type type()const = 0;
    virtual EvPluginInfo pluginInfo()const=0;
    virtual QList<EvPluginDependency> dependencies()const;

    virtual InstanciationMode mode()const=0;
    virtual bool init(){return true;}
    virtual void clear(){}
    virtual QObject * create();
    QString loadFile()const;

protected:
    virtual QObject * createOne()=0;
    void setLoadFile(const QString& file);
    friend class EvPluginsManager;

private:
    QString m_loadFile;
    QObject * lastCreatedInstance;
};


#define EV_PLUGIN(Class,PluginMode,PluginType)  \
InstanciationMode mode() const{ return PluginMode;} \
EvPluginInfo::Type type()const {return PluginType;} \
virtual QObject * createOne(){  return new Class;}

#define EV_PLUGIN_INFO(id,description,majorVersion,minorVersion) \
virtual EvPluginInfo pluginInfo()const{ \
    return EvPluginInfo(type(),id,description,majorVersion,minorVersion); \
} \

struct EvPluginsInterface {
    virtual QList<EvPlugin*> plugins()=0;
};




Q_DECLARE_INTERFACE(EvPluginsInterface,"EzVerif.EvPluginsInterface")



#endif // EVPLUGIN_H
