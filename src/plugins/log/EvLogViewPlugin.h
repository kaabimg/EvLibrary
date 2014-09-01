#ifndef EVLOGVIEWPLUGIN_H
#define EVLOGVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvLogView.h"


struct EvLogViewPlugin : EvPlugin {

    EV_PLUGIN(EvLogView,EvPlugin::Unique,EvPluginInfo::IOPane)
    EV_PLUGIN_INFO("log-view","",1,0)
};

#endif // EVLOGVIEWPLUGIN_H
