#include "EvObjectsTreeView.h"

#include "EvAppSettings.h"
#include "EvObjectPropertiesModel.h"
#include "EvObjectsTreeModel.h"
#include "EvObject.h"
#include "EvObjectDelegate.h"

#include <QResizeEvent>
#include <QSplitter>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>

EvObjectsTreeView::EvObjectsTreeView(EvObject *rootItem, QWidget *parent) :
    QTreeView(parent)
{
    customizeStyle();
    EvObjectsTreeModel * model = new EvObjectsTreeModel(rootItem,this);
    setObjectsModel(model);
    setFrameStyle(QFrame::Box | QFrame::Plain);
}

EvObjectsTreeView::EvObjectsTreeView(QWidget *parent) :
    QTreeView(parent)
{
    customizeStyle();
}

void EvObjectsTreeView::setObjectsModel(EvObjectsTreeModel * model)
{
    setModel(model);
    setIndentation(model->rowHeight());
    expandAll();

    connect(model,SIGNAL(expandRequest(QModelIndex)),this,SLOT(expandIndex(QModelIndex)));

    connect(selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(onSelectionChanged()));
    setContentsMargins(-3,-3,-3,-3);

}

EvObjectsTreeModel *EvObjectsTreeView::objectsModel() const
{
    return qobject_cast<EvObjectsTreeModel *>(model());
}

void EvObjectsTreeView::customizeStyle()
{
    QPalette palette  = this->palette();
    palette.setColor(QPalette::Base,evApparenceSettings->grayColor());
    setPalette(palette);
    setItemDelegate(new EvObjectDelegate(this));
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setAnimated(true);
    setEditTriggers(EditKeyPressed);
    setSelectionMode(SingleSelection);


}

void EvObjectsTreeView::drawBranches(QPainter *, const QRect &, const QModelIndex & ) const
{
    // the delegate will draw the branches
}




EvObject *EvObjectsTreeView::selectedObject() const
{
    QModelIndexList selection = selectedIndexes();
    if(selection.size()){
        return static_cast<EvObject*>(selection.first().internalPointer());
    }
    return NULL;
}

void EvObjectsTreeView::setCurrentSelection(EvObject * object)
{
    selectionModel()->select(
                objectsModel()->createIndexForObject(object),
                QItemSelectionModel::SelectCurrent
                );
}

void EvObjectsTreeView::expandIndex(const QModelIndex &index)
{
    expand(index);
    QModelIndexList indexes = model()->match(index, Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
    foreach (const QModelIndex& subIndex, indexes){
        expand(subIndex);
    }
}


void EvObjectsTreeView::onSelectionChanged()
{
    Q_EMIT objectSelected(selectedObject());
}



void EvObjectsTreeView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_C:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            EvObject * current = selectedObject();
            if(current){
                Q_EMIT copyRequest(current);
                return;
            }
        }
        break;
    }
    case Qt::Key_X:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            EvObject * current = selectedObject();
            if(current){
                Q_EMIT cutRequest(current);
                return;
            }
        }
        break;
    }
    case Qt::Key_V:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            EvObject * current = selectedObject();
            if(current){
                Q_EMIT pasteRequest(current);
                return;
            }
        }
        break;
    }
    case Qt::Key_S:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            EvObject * current = selectedObject();
            if(current){
                Q_EMIT saveRequest(current);
                return;
            }
        }
        break;
    }
    case Qt::Key_Delete:{
        EvObject * current = selectedObject();
        if(current){
            Q_EMIT removeRequest(current);
            return;
        }
        break;
    }
    default:
        break;
    }

    QTreeView::keyPressEvent(event);

}

void EvObjectsTreeView::focusInEvent(QFocusEvent *event)
{
    QTreeView::focusInEvent(event);
    Q_EMIT focusIn();
}

void EvObjectsTreeView::focusOutEvent(QFocusEvent *event)
{
    QTreeView::focusOutEvent(event);
    Q_EMIT focusOut();

}
