#include "EvHideShowSideBarWidget.h"
#include "EvButton.h"
#include "EvAppSettings.h"

#include <QHBoxLayout>
#include <QResizeEvent>

EvHideShowSideBarWidget::EvHideShowSideBarWidget(QWidget *parent) :
    QWidget(parent)
{
    m_minimizeButton = new EvButton(this);
    m_minimizeButton->setIcon(evIconsFactory->applicationIcon(EvIconsFactory::LeftShortArrow,EvIconsFactory::Light));
    m_minimizeButton->setPaintMode(EvButton::IconOnly);
    m_minimizeButton->setRounded(true);
    m_minimizeButton->setBackgroundColor(QColor(0,0,0,0));


    m_maximizeButton = new EvButton(this);
    m_maximizeButton->setIcon(evIconsFactory->applicationIcon(EvIconsFactory::RightShortArrow,EvIconsFactory::Light));
    m_maximizeButton->setPaintMode(EvButton::IconOnly);
    m_maximizeButton->setRounded(true);
    m_maximizeButton->setBackgroundColor(QColor(0,0,0,0));


    QHBoxLayout * layout =new QHBoxLayout(this);
    layout->setSpacing(3);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);

    layout->addWidget(m_minimizeButton);
    layout->addWidget(m_maximizeButton);

    connect(m_minimizeButton,SIGNAL(clicked()),this,SIGNAL(minimizeRequest()));
    connect(m_maximizeButton,SIGNAL(clicked()),this,SIGNAL(maximizeRequest()));

}

bool EvHideShowSideBarWidget::maximizeAvailable() const
{
    return m_maximizeButton->isVisible();
}

bool EvHideShowSideBarWidget::minimizeAvailable() const
{
    return m_minimizeButton->isVisible();
}

void EvHideShowSideBarWidget::setMaximizeAvailable(bool arg)
{
    m_maximizeButton->setVisible(arg);
}

void EvHideShowSideBarWidget::setMinimizeAvailable(bool arg)
{
    m_minimizeButton->setVisible(arg);
}


