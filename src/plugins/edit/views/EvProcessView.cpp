#include "EvProcessView.h"
#include "EvProcess.h"
#include "EvLibrariesView.h"
#include "EvParametersView.h"
#include "EvFiltersView.h"
#include "EvAppSettings.h"

#include "EvTabBar.h"
#include "EvScrollTabBar.h"

EvProcessView::EvProcessView(EvProcess * process, QWidget *parent) :
    EvTabWidget(parent)
{
    setWindowTitle("Process");
    setWindowIcon(evIconsFactory->objectIcon(Ev::Process,EvIconsFactory::Light));
    setEvObject(process);


    tabBar()->setBackgroundColor(evApparenceSettings->grayColor());
    tabBar()->setOutlineColor(evApparenceSettings->darkColor());
    QColor selectionColor = evApparenceSettings->secondaryColor();
    tabBar()->setSelectionColor(selectionColor);
    tabBar()->setLogoSize(QSize(0,30));
    tabBar()->setTabSize(QSize( evApparenceSettings->mainTabSize().width(),30));
    tabBar()->setMaximumSize(35);


    m_librariesView = new EvLibrariesView(process,this);
    m_parametersView = new EvParametersView(process,this);
    m_filtersView = new EvFiltersView(process,this);

    add(m_librariesView);
    add(m_parametersView);
    add(m_filtersView);
    setCurrentWidget(m_librariesView);
}

bool EvProcessView::showObject(EvObject * object)
{

    if(!evObject()->contains(object)){
        return false;
    }
    switch (object->typeId()) {
    case Ev::Parameter:{
        return m_parametersView->showObject(object);
        break;
    }
    case Ev::Filter:{
        return m_filtersView->showObject(object);
        break;
    }
    default:
        return m_librariesView->showObject(object);
        break;
    }

    return false;
}

void EvProcessView::setAsActiveWidget()
{
    EvWidget * active = currentWidget();
    if( active ){
        active->setAsActiveWidget();
    }
}
