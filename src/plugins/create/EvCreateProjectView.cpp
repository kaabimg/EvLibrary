#include "EvCreateProjectView.h"
#include "EvApplication.h"
#include "EvIconsfactory.h"
#include "EvObjectsTreeView.h"
#include "EvSession.h"
#include "EvAppSettings.h"
#include "EvObjectsTreeModel.h"

EvCreateProjectView::EvCreateProjectView(QWidget *parent) :
    EvWidget(parent)
{
    setWindowTitle("Start");
    setEnabled(true);
    setWindowIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Home,EvIconsFactory::Light));
    setProperty("index",0);
    setBehaviorFlags(behaviorFlags() | HasSideBarInteractions);

    EvObjectsTreeView* treeView = new EvObjectsTreeView(evApp->currentSession(),this);
    setContent(treeView);
    treeView->objectsModel()->setReadOnly(true);
}
