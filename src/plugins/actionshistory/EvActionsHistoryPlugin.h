#ifndef EVACTIONSHISTORYPLUGIN_H
#define EVACTIONSHISTORYPLUGIN_H


#include "EvPlugin.h"
#include "EvActionsHistoryView.h"

struct EvActionsHistoryPlugin : EvPlugin {

    EV_PLUGIN(EvActionsHistoryView,EvPlugin::Unique,EvPluginInfo::IOPaneRightWidget)
    EV_PLUGIN_INFO("actions-history","",1,0)

};

#endif // EVACTIONSHISTORYPLUGIN_H
