#include "EvSimulationView.h"
#include "EvSimulation.h"
#include "EvAppSettings.h"


EvSimulationView::EvSimulationView(EvSimulation * simulation,QWidget *parent) :
    EvWidget(simulation,parent)
{
    setWindowTitle(simulation->objectName());
    setWindowIcon(evApp->iconsFactory()->objectIcon(Ev::Simulation,EvIconsFactory::Light));
    setEnabled(true);
    setSupportsRename(true);
}
