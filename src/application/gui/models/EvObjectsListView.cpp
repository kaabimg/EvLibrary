#include "EvObjectsListView.h"
#include "EvObjectsListModel.h"
#include "EvObjectsContainer.h"
#include "EvAppSettings.h"

EvObjectsListView::EvObjectsListView(QWidget *parent) :
    QListView(parent)
{
}

EvObjectsListView::EvObjectsListView(EvObjectsContainer * container, QWidget *parent):
     QListView(parent)
{
    setContainer(container);
}

void EvObjectsListView::setContainer(EvObjectsContainer *objects)
{
    EvObjectsListModel * model = new EvObjectsListModel(objects,this);
    model->setIconStyle(EvIconsFactory::Light);
    setModel(model);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base,evApparenceSettings->grayColor());
    palette.setColor(QPalette::Text,evApparenceSettings->ligthColor());
    setPalette(palette);
}

void EvObjectsListView::setContent(const EvObjectsList & list)
{
    qobject_cast<EvObjectsListModel*>(model())->setContent(list);;
}



