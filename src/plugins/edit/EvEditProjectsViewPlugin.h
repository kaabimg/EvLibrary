#ifndef EVEDITPROJECTSVIEWPLUGIN_H
#define EVEDITPROJECTSVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvEditView.h"


struct EvEditProjectsViewPlugin : EvPlugin {

    EV_PLUGIN(EvEditView,EvPlugin::Unique,EvPluginInfo::MainViewWidget)
    EV_PLUGIN_INFO("edit-projects-view","",1,0)

};


#endif // EVEDITPROJECTSVIEWPLUGIN_H
