#include "EvIOPaneContainer.h"

#include <QStackedWidget>
#include <QVBoxLayout>

#include "EvIOPane.h"
#include "EvToolBar.h"
#include "EvAppSettings.h"

struct EvIOPaneContainerPrivate {

    EvToolBar * toolBar;
    QStackedWidget * stack;

};

EvIOPaneContainer::EvIOPaneContainer(QWidget *parent) :
    QWidget(parent)
{
    d_ptr = new EvIOPaneContainerPrivate;
    d_ptr->toolBar = new EvToolBar(150,12,this);
    QFont font = evApparenceSettings->font();
    font.setPointSize(font.pointSize()*0.8);
    d_ptr->toolBar->setFont(font);
    d_ptr->toolBar->setFixedHeight(25);
    d_ptr->stack = new QStackedWidget(this);

    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(d_ptr->toolBar);
    layout->addWidget(d_ptr->stack);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
}

int EvIOPaneContainer::preferredSize() const
{
    return 350;
}

void EvIOPaneContainer::showPane(EvIOPane * pane)
{
    int index = d_ptr->stack->indexOf(pane);
    if(index<0){
        index = d_ptr->stack->addWidget(pane);
    }
    d_ptr->stack->setCurrentIndex(index);
    d_ptr->toolBar->setCurrentWidget(pane);

}
