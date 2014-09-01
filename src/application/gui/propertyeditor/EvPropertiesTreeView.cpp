#include "EvPropertiesTreeView.h"
#include "EvPropertiesTreeModel.h"
#include "EvPropertyEditorDelegateManager.h"

EvPropertiesTreeView::EvPropertiesTreeView(EvProperty *group, QWidget *parent):
    QTreeView(parent)
{
    EvPropertiesTreeModel * model = new EvPropertiesTreeModel(group,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);

}

EvPropertiesTreeView::EvPropertiesTreeView(const EvPropertiesList &list, QWidget *parent) :
    QTreeView(parent)
{
    EvPropertiesTreeModel * model = new EvPropertiesTreeModel(list,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);
}

EvPropertiesTreeView::EvPropertiesTreeView(EvObject *object, QWidget *parent) :
    QTreeView(parent)
{
    EvPropertiesTreeModel * model = new EvPropertiesTreeModel(object,this);
    setModel(model);
    setItemDelegate(new EvPropertyEditorDelegateManager(this));
    setAlternatingRowColors(true);
}
