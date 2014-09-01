#include "EvMainWindowIOBar.h"

#include <QList>
#include <QHBoxLayout>
#include <QAction>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include "EvToolButton.h"

#include "EvIOPane.h"
#include "EvGuiUtils.h"
#include "EvApplication.h"
#include "EvAppSettings.h"

struct EvMainWindowIOBarPrivate
{
    QHBoxLayout * layout;
    QList<EvToolButton*> buttons;
    QList<EvIOPane*> ioPanes;
    int width;
    QColor backgroundColor;
    int currentSelectionIndex;
    QTimer animationTimer;
    QList<EvToolButton*> animatedPanesButtons;
    bool animationCycle;

};
EvMainWindowIOBar::EvMainWindowIOBar(QWidget * parent):QWidget(parent),d_ptr(new EvMainWindowIOBarPrivate)
{
    d_ptr->currentSelectionIndex = -1;

    d_ptr->layout = new QHBoxLayout;
    d_ptr->layout ->setContentsMargins(0,3,0,0);
    d_ptr->layout ->setSpacing(10);
    d_ptr->layout->setDirection(QBoxLayout::LeftToRight);
    d_ptr->layout->setAlignment(Qt::AlignCenter);
    setLayout(d_ptr->layout );
    setFixedHeight(35);
    d_ptr->width = 0;
    d_ptr->backgroundColor = evApparenceSettings->darkColor();


    d_ptr->animationCycle = false;
    d_ptr->animationTimer.setInterval(800);
    connect(&d_ptr->animationTimer,SIGNAL(timeout()),this,SLOT(animatePanes()));

}
EvMainWindowIOBar::~EvMainWindowIOBar()
{
    delete d_ptr;
}
void EvMainWindowIOBar::addWidget(QWidget * w)
{
    d_ptr->layout->addWidget(w);
    w->setParent(this);
}
void EvMainWindowIOBar::addPane(EvIOPane * ioPane)
{
    EvToolButton * button = new EvToolButton(
                d_ptr->buttons.count()+1
                ,this);

    button->setText(ioPane->windowTitle());

    button->setProperty("index", d_ptr->ioPanes.size());
    d_ptr->layout->addWidget(button);
    d_ptr->buttons<<button;
    d_ptr->ioPanes<<ioPane;
    connect(button,SIGNAL(toggled(bool)),this,SLOT(paneButtonToggled(bool)));
    connect(ioPane,SIGNAL(contentChanged()),this,SLOT(animatePane()));
    if(ioPane->contentChangedOnInit())
        animatePane(ioPane);
}

void EvMainWindowIOBar::paneButtonToggled(bool toggled)
{
    EvToolButton * theButton = qobject_cast<EvToolButton*>(sender());
    if(toggled)
    {
        if(d_ptr->currentSelectionIndex !=-1){
             EvToolButton * button = d_ptr->buttons[d_ptr->currentSelectionIndex];
             button->blockSignals(true);
             button->setChecked(false);
             button->blockSignals(false);
        }
        d_ptr->currentSelectionIndex  = theButton->property("index").toInt();
        d_ptr->animatedPanesButtons.removeOne(theButton);
        theButton->setAnimated(false);
        EvIOPane * pane = d_ptr->ioPanes[d_ptr->currentSelectionIndex];
        Q_EMIT showRequest(pane);
    }
    else
    {
        d_ptr->currentSelectionIndex =-1;
        Q_EMIT hideRequest();
    }
}

void EvMainWindowIOBar::animatePanes()
{
    d_ptr->animationCycle = !d_ptr->animationCycle;

    for(int i=0;i<d_ptr->animatedPanesButtons.size();++i){
        d_ptr->animatedPanesButtons[i]->setAnimated(d_ptr->animationCycle);
    }



}

void EvMainWindowIOBar::animatePane()
{
    EvIOPane* pane = qobject_cast<EvIOPane*>(sender());
    animatePane(pane);

}

void EvMainWindowIOBar::animatePane(EvIOPane * pane)
{
    int index = d_ptr->ioPanes.indexOf(pane);
    EvToolButton * button = d_ptr->buttons.at(index);

    if(button->isChecked())//pane is visible
        return;

    if(!d_ptr->animatedPanesButtons.contains(button))
        d_ptr->animatedPanesButtons.append(button);

    if(!d_ptr->animationTimer.isActive())
        d_ptr->animationTimer.start();
}


void EvMainWindowIOBar::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    Ev::paintBarGradient(&painter,rect());
    QWidget::paintEvent(event);
}
