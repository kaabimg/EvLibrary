#ifndef EVFINDPLUGIN_H
#define EVFINDPLUGIN_H

#include "EvPlugin.h"
#include "EvFindWidget.h"

struct EvFindPlugin : EvPlugin {

    EV_PLUGIN(EvFindWidget,EvPlugin::Unique,EvPluginInfo::IOPaneRightWidget)
    EV_PLUGIN_INFO("find-widget","",1,0)

};


#endif // EVFINDPLUGIN_H
