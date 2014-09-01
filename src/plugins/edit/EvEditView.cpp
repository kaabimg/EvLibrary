#include "EvEditView.h"
#include "EvTabWidget.h"
#include "EvTabBar.h"
#include "EvScrollTabBar.h"

#include "EvAppSettings.h"
#include "EvIconsfactory.h"
#include "EvMainWindow.h"
#include "EvHideShowSideBarWidget.h"



#include "views/EvEditProjectView.h"
#include "views/EvSchematicView.h"
#include "views/EvStateView.h"
#include "views/EvCellView.h"
#include "views/EvProcessView.h"

#include "EvCell.h"
#include "EvProcess.h"
#include "EvSession.h"
#include "EvObjectsTreeModel.h"
#include "EvObjectsTreeView.h"

#include "EvSystem.h"
#include "EvCommands.h"

struct EvEditViewPrivate {
};

EvEditView::EvEditView(QWidget *parent) :
    EvObjectsTreeTabWidget(evApp->currentSession(),parent),
    d_ptr(new EvEditViewPrivate)
{
    setWindowTitle("Design");
    setEnabled(true);
    setWindowIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Edit,EvIconsFactory::Light));
    setProperty("index",2);
    setBehaviorFlags(
                HasSideBarInteractions |
                HasHideSideBarFeature |
                HasShowSideBarFeature |
                SupportsCopyPaste |
                SupportsUndoRedo
                );




    setMaxSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth() -1// -1 == splitter handle
                );

    setSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth()-1
                );

    model()->setLeafsTypes(QSet<int>()<<Ev::Process<<Ev::Schematic<<Ev::State);
    model()->addFilter(Ev::Cell,Ev::Process);
    model()->addFilter(Ev::Cell,Ev::Schematic);
    model()->addFilter(Ev::Cell,Ev::State);     

    connect(this,SIGNAL(sideBarFocusIn()),this,SLOT(onSideBarFocusIn()));
    connect(this,SIGNAL(sideBarFocusOut()),this,SLOT(onSideBarFocusOut()));

}


EvEditView::~EvEditView()
{
    delete d_ptr;
}



bool EvEditView::supportsObjectType(int type)const
{
    static const QSet<int> supportedTypes =
            QSet<int>()<< Ev::Project
                       << Ev::Cell
                       << Ev::Schematic
                       << Ev::State
                       << Ev::Process;

    return supportedTypes.contains(type);
}


EvWidget *EvEditView::createViewForObject(EvObject * object)
{
    if(!supportsObjectType(object->typeId())){
        return NULL;
    }

    EvWidget * widget = NULL;
    switch (object->typeId()) {
    case Ev::Project:
        widget = new EvEditProjectView(object->to<EvProject>(),this);
        break;
    case Ev::Cell:
        widget = new EvCellView(object->to<EvCell>(),this);
        break;
    case Ev::Schematic:
        widget = new EvSchematicView(object->to<EvSchematic>(),this);
        break;
    case Ev::State:
        widget = new EvStateView(object->to<EvState>(),this);
        break;
    case Ev::Process:
        widget = new EvProcessView(object->to<EvProcess>(),this);
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



void EvEditView::showEvent(QShowEvent * e)
{
    EvObjectsTreeTabWidget::showEvent(e);
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
            this,SLOT(minimizeSideBar()));
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
            this,SLOT(maximizeSideBar()));
}

void EvEditView::hideEvent(QHideEvent * e)
{
    EvObjectsTreeTabWidget::hideEvent(e);
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
               this,SLOT(minimizeSideBar()));
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
               this,SLOT(maximizeSideBar()));

}


void EvEditView::minimizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1 ;// -1 == splitter handle
    int width = 0;

    if(sideBarSize() > mid)
        width = mid;

    setSideBarSize(width);
}

void EvEditView::maximizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1;// -1 == splitter handle
    int max = evMainWindow->logoWidth()+
            2 * evMainWindow->tabWidth()-1 ;// -1 == splitter handle

    int width = mid;

    if(sideBarSize() >= mid)
        width = max;

    setSideBarSize(width);
}

void EvEditView::onObjectSelected(EvObject * object)
{
    EvObjectsTreeTabWidget::onObjectSelected(object);
    clipboardInterface()->setSelection(object);
    setAsActiveWidget();
}

void EvEditView::onRemoveRequest(EvObject * object)
{
    EvSystem output("Objects manager");
    EvSystem::Message message;
    message<<"Remove object "<<object<<" ? ";

    if(output.question(message)){
        commandsInterface()->removeObject(object);
    }
}

void EvEditView::onCopyRequest(EvObject * object)
{
    clipboardInterface()->setCopyObject(object);
}

void EvEditView::onCutRequest(EvObject * object)
{
    clipboardInterface()->setCutObject(object);
}

void EvEditView::onPasteRequest(EvObject * )
{
    clipboardInterface()->paste();
}

void EvEditView::onSaveRequest(EvObject * )
{

}


void EvEditView::setAsActiveWidget()
{
    if(sideBar()->hasFocus()){
        EvObjectsTreeTabWidget::setAsActiveWidget();
    }
    else {
        EvWidget * active = currentWidget();
        if( active ){
            active->setAsActiveWidget();
        }
        else {
            EvObjectsTreeTabWidget::setAsActiveWidget();
        }
    }
}

void EvEditView::onSideBarFocusIn()
{
    setAsActiveWidget();
}

void EvEditView::onSideBarFocusOut()
{
    if(isVisible()){
        setAsActiveWidget();
    }
}
