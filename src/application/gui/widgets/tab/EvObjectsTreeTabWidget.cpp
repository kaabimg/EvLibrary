#include "EvObjectsTreeTabWidget.h"

#include "EvObjectsTreeView.h"
#include "EvSplitter.h"
#include "EvObject.h"
#include "EvObjectsTreeModel.h"

#include <QStackedWidget>

struct EvObjectsTreeTabWidgetPrivate{
    QHash<EvObject*,EvWidget*> widgets;
    EvObjectsTreeView * objectsTree;
    QStackedWidget * stack;
    EvSplitter * splitter;


};

EvObjectsTreeTabWidget::EvObjectsTreeTabWidget(EvObject *rootObject, QWidget *parent) :
    EvWidget(rootObject,parent),d_ptr(new EvObjectsTreeTabWidgetPrivate)
{
    d_ptr->splitter = new EvSplitter(Qt::Horizontal,this);
    d_ptr->objectsTree = new EvObjectsTreeView(rootObject,d_ptr->splitter);
    d_ptr->stack = new QStackedWidget(d_ptr->splitter);

    d_ptr->splitter->addWidget(d_ptr->objectsTree);
    d_ptr->splitter->addWidget(d_ptr->stack);

    d_ptr->objectsTree->objectsModel()->setReadOnly(false);

    setContent(d_ptr->splitter);


    connect(d_ptr->objectsTree,SIGNAL(objectSelected(EvObject*)),
            this, SLOT(onObjectSelected(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(removeRequest(EvObject*)),
            this, SLOT(onRemoveRequest(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(copyRequest(EvObject*)),
            this, SLOT(onCopyRequest(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(cutRequest(EvObject*)),
            this, SLOT(onCutRequest(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(pasteRequest(EvObject*)),
            this, SLOT(onPasteRequest(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(saveRequest(EvObject*)),
            this, SLOT(onSaveRequest(EvObject*)));

    connect(d_ptr->objectsTree,SIGNAL(focusIn()),this,SIGNAL(sideBarFocusIn()));
    connect(d_ptr->objectsTree,SIGNAL(focusOut()),this,SIGNAL(sideBarFocusOut()));

    connect(rootObject,SIGNAL(objectRemoved(EvObject*,EvObject*)),
            this,SLOT(onObjectRemoved(EvObject*,EvObject*)));
}

EvObjectsTreeTabWidget::~EvObjectsTreeTabWidget()
{
    delete d_ptr;
}

EvObjectsTreeView *EvObjectsTreeTabWidget::sideBar() const
{
    return d_ptr->objectsTree;
}




void EvObjectsTreeTabWidget::add(EvWidget * widget, int )
{
    if(!contains(widget)){
        d_ptr->widgets.insert(widget->evObject(),widget);
        d_ptr->stack->addWidget(widget);
    }
}

void EvObjectsTreeTabWidget::remove(EvWidget * widget)
{
    d_ptr->widgets.remove(widget->evObject());
    d_ptr->stack->removeWidget(widget);
}

bool EvObjectsTreeTabWidget::contains(EvWidget  * widget)
{
    return d_ptr->stack->indexOf(widget) != -1;
}

int EvObjectsTreeTabWidget::indexOf(EvWidget *widget)
{
    return d_ptr->stack->indexOf(widget);
}

QList<EvWidget *> EvObjectsTreeTabWidget::chilrenWidgets() const
{
    return d_ptr->widgets.values();
}

int EvObjectsTreeTabWidget::childrenWidgetsCount() const
{
    return d_ptr->widgets.count();
}

void EvObjectsTreeTabWidget::setCurrentIndex(int)
{
    // unimplemented
}

EvWidget *EvObjectsTreeTabWidget::currentWidget() const
{
    return qobject_cast<EvWidget*>(d_ptr->stack->currentWidget());
}

int EvObjectsTreeTabWidget::currentIndex() const
{
    return -1;
}

void EvObjectsTreeTabWidget::setCurrentWidget(EvWidget * widget)
{
    if(contains(widget)){
        setCurrentStackWidget(widget);
        d_ptr->objectsTree->setCurrentSelection(widget->evObject());
    }
}



int EvObjectsTreeTabWidget::sideBarSize() const
{
    return d_ptr->splitter->sizes().first();
}

void EvObjectsTreeTabWidget::setSideBarSize(int size)
{
    QList<int> sizes;
    sizes<<size;
    sizes<< (width()-size -1);// -1 == splitter handler
    d_ptr->splitter->setSizes(sizes);
}

void EvObjectsTreeTabWidget::setMaxSideBarSize(int size)
{
    d_ptr->objectsTree->setMaximumWidth(size);
}

void EvObjectsTreeTabWidget::setMinSideBarSize(int size)
{
    d_ptr->objectsTree->setMinimumWidth(size);
}

bool EvObjectsTreeTabWidget::readOnly() const
{
    return d_ptr->objectsTree->objectsModel()->readOnly();
}

EvObjectsTreeModel *EvObjectsTreeTabWidget::model() const
{
    return d_ptr->objectsTree->objectsModel();
}

void EvObjectsTreeTabWidget::setReadOnly(bool arg)
{
    d_ptr->objectsTree->objectsModel()->setReadOnly(arg);;
}



void EvObjectsTreeTabWidget::onObjectRemoved(EvObject * object, EvObject *)
{
    if(d_ptr->widgets.contains(object)){
        remove(d_ptr->widgets.value(object));
    }
    EvWidget * current = qobject_cast<EvWidget*>(d_ptr->stack->currentWidget());
    if(current){
        d_ptr->objectsTree->setCurrentSelection(current->evObject());

    }
}

void EvObjectsTreeTabWidget::setCurrentStackWidget(QWidget * widget)
{
    if(d_ptr->stack->indexOf(widget) == -1){
        d_ptr->stack->addWidget(widget);
    }
    d_ptr->stack->setCurrentWidget(widget);
}

bool EvObjectsTreeTabWidget::containsObject(const EvObject * obj) const
{
    if(evObject() == obj){
        return true;
    }
    return evObject()->contains(obj,true);
}


void EvObjectsTreeTabWidget::onObjectSelected(EvObject * object)
{
    if(!supportsObjectType(object->typeId())){
        return ;
    }
    if(!d_ptr->widgets.contains(object)){
        EvWidget * view = createViewForObject(object);
        Q_ASSERT(view);
        add(view);
    }
    setCurrentWidget(d_ptr->widgets.value(object));
    clipboardInterface()->setSelection(object);
}


bool EvObjectsTreeTabWidget::showObject(EvObject * object)
{ 
    if(d_ptr->widgets.contains(object)){ // object view already created
        setCurrentWidget(d_ptr->widgets.value(object));
        return true;
    }

    if(!evObject()->isAncestorOf(object)){
        return false;
    }

    if(supportsObjectType(object->typeId())){ // object not yet created
        EvWidget * view = createViewForObject(object);
        Q_ASSERT(view);
        add(view);
        setCurrentWidget(view);
        Q_EMIT showRequest(this);
        return true;
    }

    EvObject * parent = object->parentEvObject();
    while (parent) {
        if(supportsObjectType(parent->typeId())){
            EvWidget * view = createViewForObject(parent);
            Q_ASSERT(view);
            add(view);
            setCurrentWidget(view);
            if(view->showObject(object)){
                Q_EMIT showRequest(this);
                return true;
            }
            return false;
        }
        else {
            parent = parent->parentEvObject();
        }

    }

    return false;
}


