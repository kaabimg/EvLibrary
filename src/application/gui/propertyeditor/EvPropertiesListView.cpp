#include "EvPropertiesListView.h"
#include "EvPropertiesListModel.h"
#include "EvPropertyEditorDelegateManager.h"

EvPropertiesListView::EvPropertiesListView(EvProperty *group, QWidget *parent):
    QTreeView(parent)
{
    EvPropertiesListModel * model = new EvPropertiesListModel(group,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);

}

EvPropertiesListView::EvPropertiesListView(const EvPropertiesList &list, QWidget *parent) :
    QTreeView(parent)
{
    EvPropertiesListModel * model = new EvPropertiesListModel(list,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);
}

EvPropertiesListView::EvPropertiesListView(EvObject *object, QWidget *parent) :
    QTreeView(parent)
{
    EvPropertiesListModel * model = new EvPropertiesListModel(object,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);
}
