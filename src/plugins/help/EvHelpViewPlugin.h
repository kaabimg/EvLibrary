#ifndef EVHELPVIEWPLUGIN_H
#define EVHELPVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvHelpView.h"


struct EvHelpViewPlugin : EvPlugin {

    EV_PLUGIN(EvHelpView,EvPlugin::Unique,EvPluginInfo::MainViewWidget)
    EV_PLUGIN_INFO("help-view","",1,0)

};


#endif // EVHELPVIEWPLUGIN_H
