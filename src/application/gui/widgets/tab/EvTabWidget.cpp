#include "EvTabWidget.h"
#include "EvTabBar.h"

#include "EvWidget.h"
#include "EvSplitter.h"

#include <QStackedWidget>
#include <QHBoxLayout>
#include <QScrollBar>

struct EvTabWidgetPrivate{
    EvTabBar * tabBar;
    QStackedWidget * stack;
    QList<EvWidget*> tabs;
};

EvTabWidget::EvTabWidget(QWidget *parent) :
    EvWidget(parent)
{
    d_ptr = new EvTabWidgetPrivate;
    d_ptr->tabBar = new EvTabBar(Qt::Horizontal,this);
    d_ptr->stack = new QStackedWidget(this);

    QBoxLayout * layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);





    layout->addWidget(d_ptr->tabBar);
    layout->addWidget(d_ptr->stack);

    connect(d_ptr->tabBar,
            SIGNAL(showRequest(EvWidget*)),
            this,
            SLOT(setCurrentWidget(EvWidget*)));
    setLayout(layout);

}

EvTabBar *EvTabWidget::tabBar() const
{
    return d_ptr->tabBar;
}

void EvTabWidget::add(EvWidget * tab, int index)
{
    bool ok;
    int level = tab->property("level").toInt(&ok);
    if(!ok)
        level= 0;
    if(index != -1){
        tabBar()->insertTab(tab,index,level);
        d_ptr->tabs.insert(index,
                           tab);
    }
    else{
        tabBar()->addTab(tab,level);
        d_ptr->tabs.append(tab);
    }
    d_ptr->stack->addWidget(tab);
    tab->setParent(d_ptr->stack);
    tab->setParentEvWidget(this);
    connect(tab,SIGNAL(showRequest(EvWidget*)),this,SLOT(setCurrentWidget(EvWidget*)));
    connect(tab,SIGNAL(removeRequest(EvWidget*)),this,SLOT(remove(EvWidget*)));

}

void EvTabWidget::remove(EvWidget * tab)
{
    int newIndex = currentIndex()-1;
    tabBar()->removeTab(tab);
    tab->setParentEvWidget(NULL);
    d_ptr->tabs.removeOne(tab);
    d_ptr->stack->removeWidget(tab);
    disconnect(tab,SIGNAL(showRequest(EvWidget*)),this,SLOT(setCurrentWidget(EvWidget*)));
    disconnect(tab,SIGNAL(removeRequest(EvWidget*)),this,SLOT(remove(EvWidget*)));

    if(newIndex<0){
        newIndex = 0;
    }
    if(childrenWidgetsCount()){
        setCurrentIndex(newIndex);
    }
}

int EvTabWidget::indexOf(EvWidget * tab)
{
    return d_ptr->tabs.indexOf(tab);
}

QList<EvWidget *> EvTabWidget::chilrenWidgets() const
{
    return d_ptr->tabs;
}

int EvTabWidget::childrenWidgetsCount() const
{
    return d_ptr->tabs.size();
}

void EvTabWidget::setCurrentWidget(EvWidget * tab)
{
    if(!d_ptr->tabs.contains(tab)){
        return;
    }
    tabBar()->setCurrentTab(tab);
    d_ptr->stack->setCurrentWidget(tab);
}

void EvTabWidget::setCurrentIndex(int index)
{
    if(d_ptr->tabs.size()<index-1){
        return;
    }
    setCurrentWidget(d_ptr->tabs[index]);
}

int EvTabWidget::currentIndex() const
{
    return tabBar()->currentIndex();
}

bool EvTabWidget::showObject(EvObject * object)
{
    foreach(EvWidget * tab,d_ptr->tabs){
        if(tab->showObject(object)){
            Q_EMIT showRequest(this);
            return true;
        }
    }
    return false;
}

EvWidget *EvTabWidget::currentWidget() const
{
    if(tabBar()->currentIndex() == -1){
        return NULL;
    }
    return d_ptr->tabs[tabBar()->currentIndex()];
}

bool EvTabWidget::contains(EvWidget * tab)
{
    return d_ptr->tabs.contains(tab);

}

