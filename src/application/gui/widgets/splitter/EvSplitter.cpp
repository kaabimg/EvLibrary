#include "EvSplitter.h"
#include "EvSplitterHandle.h"

EvSplitter::EvSplitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation,parent)
{
    setHandleWidth(1);
}

QSplitterHandle *EvSplitter::createHandle()
{
    return new EvSplitterHandle(orientation(),this);
}
