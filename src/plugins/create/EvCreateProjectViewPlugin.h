#ifndef EVCREATEPROJECTVIEWPLUGIN_H
#define EVCREATEPROJECTVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvCreateProjectView.h"


struct EvCreateProjectViewPlugin : EvPlugin {

    EV_PLUGIN(EvCreateProjectView,EvPlugin::Unique,EvPluginInfo::MainViewWidget)
    EV_PLUGIN_INFO("create-project-view","",1,0)

};


#endif // EVCREATEPROJECTVIEWPLUGIN_H
