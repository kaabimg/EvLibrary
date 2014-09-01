#ifndef EVSIMULATIONSVIEWPLUGIN_H
#define EVSIMULATIONSVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvSimulateView.h"


struct EvSimulationsViewPlugin : EvPlugin {

    EV_PLUGIN(EvSimulateView,EvPlugin::Unique,EvPluginInfo::MainViewWidget)
    EV_PLUGIN_INFO("simulations-view","",1,0)
};


#endif // EVSIMULATIONSVIEWPLUGIN_H
