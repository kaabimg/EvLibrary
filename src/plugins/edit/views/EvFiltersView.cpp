#include "EvFiltersView.h"
#include "EvProcess.h"
#include "EvAppSettings.h"
#include <QTextEdit>

EvFiltersView::EvFiltersView(EvProcess *process, QWidget *parent) :
    EvWidget(parent)
{
    setWindowTitle("Filters");
    setWindowIcon(evIconsFactory->objectIcon(Ev::Filter,EvIconsFactory::Light));
    setContent(new QTextEdit(windowTitle()));
}
