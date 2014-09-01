#include "EvLibrariesView.h"
#include "EvAppSettings.h"
#include <QTextEdit>

EvLibrariesView::EvLibrariesView(EvProcess * process,QWidget *parent) :
    EvWidget(parent)
{
    setWindowTitle("Libraries");
    setWindowIcon(evIconsFactory->objectIcon(Ev::Library,EvIconsFactory::Light));
    setContent(new QTextEdit(windowTitle()));
}
