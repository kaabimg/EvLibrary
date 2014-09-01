#include "EvSimulateView.h"

#include "EvTabWidget.h"
#include "EvTabBar.h"
#include "EvScrollTabBar.h"

#include "EvAppSettings.h"
#include "EvIconsfactory.h"
#include "EvMainWindow.h"
#include "EvHideShowSideBarWidget.h"


#include "views/EvSimulationView.h"

#include "EvCell.h"
#include "EvProcess.h"
#include "EvSession.h"
#include "EvSimulation.h"
#include "EvObjectsTreeModel.h"

struct EvSimulateViewPrivate {
};

EvSimulateView::EvSimulateView(QWidget *parent) :
    EvObjectsTreeTabWidget(evApp->currentSession(),parent),
    d_ptr(new EvSimulateViewPrivate)
{
    setWindowTitle("Simulations");
    setEnabled(true);
    setWindowIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Play,EvIconsFactory::Light));
    setProperty("index",3);
    setBehaviorFlags(behaviorFlags() | HasSideBarInteractions | HasHideSideBarFeature | HasShowSideBarFeature);




    setMaxSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth() -1// -1 == splitter handle
                );

    setSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth()-1
                );

    model()->setLeafsTypes(QSet<int>()<<Ev::Simulation);
    model()->addFilter(Ev::Cell,Ev::Simulation);

}


EvSimulateView::~EvSimulateView()
{
    delete d_ptr;
}


void EvSimulateView::setAsActiveWidget()
{
    EvWidget * active = currentWidget();
    if( active){
        active->setAsActiveWidget();
    }
    else {
        EvObjectsTreeTabWidget::setAsActiveWidget();
    }

}

EvWidget *EvSimulateView::createViewForObject(EvObject * object)
{
    EvWidget * widget = NULL;
    switch (object->typeId()) {
    case Ev::Simulation:
        widget = new EvSimulationView(object->to<EvSimulation>(),this);
        break;
    default:
        break;
    }

    if(widget){
        widget->setParentEvWidget(this);
        widget->setActiveOnShow(false);
        connect(widget,SIGNAL(showRequest(EvWidget*)),
                this,SLOT(setCurrentWidget(EvWidget*)));

    }
    return widget;
}

bool EvSimulateView::supportsObjectType(int type) const
{
    return type == Ev::Simulation;
}

void EvSimulateView::showEvent(QShowEvent * e)
{
    EvObjectsTreeTabWidget::showEvent(e);
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
            this,SLOT(minimizeSideBar()));
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
            this,SLOT(maximizeSideBar()));
}

void EvSimulateView::hideEvent(QHideEvent * e)
{
    EvObjectsTreeTabWidget::hideEvent(e);
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
               this,SLOT(minimizeSideBar()));
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
               this,SLOT(maximizeSideBar()));

}


void EvSimulateView::minimizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1 ;// -1 == splitter handle
    int width = 0;

    if(sideBarSize() > mid)
        width = mid;

    setSideBarSize(width);
}

void EvSimulateView::maximizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1;// -1 == splitter handle
    int max = evMainWindow->logoWidth()+
            2 * evMainWindow->tabWidth()-1 ;// -1 == splitter handle

    int width = mid;

    if(sideBarSize() >= mid)
        width = max;

    setSideBarSize(width);
}

void EvSimulateView::onObjectSelected(EvObject * object)
{
    clipboardInterface()->setSelection(object);
}

void EvSimulateView::onRemoveRequest(EvObject * object)
{
    if(object){
        object->remove();
    }
}

void EvSimulateView::onCopyRequest(EvObject * object)
{
    clipboardInterface()->setCopyObject(object);
}

void EvSimulateView::onCutRequest(EvObject * object)
{
    clipboardInterface()->setCutObject(object);
}

void EvSimulateView::onPasteRequest(EvObject * )
{
//    paste();
}

void EvSimulateView::onSaveRequest(EvObject * )
{

}





