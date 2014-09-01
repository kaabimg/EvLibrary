#include "EvActionsHistoryView.h"

#include <QVariant>
#include <QUndoView>

#include "EvCommandsInterface.h"
#include "EvMainWindow.h"
#include "EvWidget.h"



EvActionsHistoryView::EvActionsHistoryView(QWidget *parent):EvButton(parent)
{
    setText("Last actions");
    setCheckable(true);
    setPaintMode(TextOnly);
    setMinimumWidth(300);
    setProperty("index",10000);

    m_lastActionsView = new QUndoView(this);
    m_lastActionsView->hide();
    m_lastActionsView->setWindowFlags(Qt::ToolTip);

    connect(evMainWindow,SIGNAL(resized()),this,SLOT(updateViewSize()));
    connect(evMainWindow,SIGNAL(moved()),this,SLOT(updateViewSize()));
    connect(this,SIGNAL(clicked(bool)),m_lastActionsView,SLOT(setVisible(bool)));
    connect(evMainWindow,
            SIGNAL(activeWidgetChanged(EvWidget*)),
            this,
            SLOT(onActiveWidgetChanged(EvWidget*))
            );

}



void EvActionsHistoryView::updateViewSize()
{
    QRect mainGeometry = evMainWindow->geometry();
    int x,y,w,h;

    x = mainGeometry.x()+ geometry().x();
    w = width();

    h = evMainWindow->temporaryWidgetsHeigth();

    QRect rect = evMainWindow->geometry();
    y = mainGeometry.y() + rect.height() - height() - h  - 17;
    m_lastActionsView->setGeometry(QRect(QPoint(x,y),QPoint(x+w,y+h)));
}


void EvActionsHistoryView::onActiveWidgetChanged(EvWidget * widget)
{
    m_lastActionsView->setStack(widget->commandsInterface()->commandsStack());
}
