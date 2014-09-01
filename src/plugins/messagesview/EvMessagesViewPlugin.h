#ifndef EVMESSAGESVIEWPLUGIN_H
#define EVMESSAGESVIEWPLUGIN_H

#include "EvPlugin.h"
#include "EvMessagesView.h"


struct EvMessagesViewPlugin : EvPlugin {

    EV_PLUGIN(EvMessagesView,EvPlugin::Unique,EvPluginInfo::IOPane)
    EV_PLUGIN_INFO("messages-view","",1,0)
};


#endif // EVMESSAGESVIEWPLUGIN_H
