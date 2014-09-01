#include "EvScrollTabBar.h"
#include "EvTabBar.h"
#include <QScrollBar>
#include <QResizeEvent>

EvScrollTabBar::EvScrollTabBar(Qt::Orientation orientation,QWidget *parent) :
    QScrollArea(parent)
{
    m_tabBar = new EvTabBar(orientation,this);
    setWidget(m_tabBar);
    setWidgetResizable(true);
    setViewportMargins(0,0,-3,-3);
    setFrameShape(QFrame::NoFrame);
    connect(m_tabBar,SIGNAL(currentIndexChanged(bool)),this,SLOT(updateScrollPosition(bool)));
}

EvTabBar *EvScrollTabBar::tabBar() const
{
    return m_tabBar;

}

void EvScrollTabBar::updateScrollPosition(bool mouseEvent)
{
    if(mouseEvent)
        return;
    int tabsCount = m_tabBar->tabsCount();
    int index = m_tabBar->currentIndex();

    if(index == 0){
        verticalScrollBar()->setValue(verticalScrollBar()->minimum());
    }
    else if(tabsCount == (index+1)){
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());

    }
    else {
        float range = verticalScrollBar()->maximum() - verticalScrollBar()->minimum();
        float value = verticalScrollBar()->minimum() + (range * index )/tabsCount;
        verticalScrollBar()->setValue(value);
    }
}



