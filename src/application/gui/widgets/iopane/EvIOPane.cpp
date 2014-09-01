#include "EvIOPane.h"
#include<QPaintEvent>
#include <QPainter>

EvIOPane::EvIOPane(QWidget * parent):EvWidget(parent),m_contentChangedOnInit(false)
{
    setBehaviorFlags(NoBehaviorFlags);
    setActiveOnShow(false);
}

bool EvIOPane::contentChangedOnInit() const
{
    return m_contentChangedOnInit;
}

void EvIOPane::setContentChangedOnInit(bool arg)
{
    m_contentChangedOnInit = arg;
}
