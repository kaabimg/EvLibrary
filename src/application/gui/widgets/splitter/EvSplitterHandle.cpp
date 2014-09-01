#include "EvSplitterHandle.h"
#include <QSplitter>
#include <QPainter>
#include "EvAppSettings.h"

EvSplitterHandle::EvSplitterHandle(Qt::Orientation orientation,QSplitter *parent) :
    QSplitterHandle(orientation,parent)
{
    setMask(QRegion(contentsRect()));
    setAttribute(Qt::WA_MouseNoMask, true);
}

void EvSplitterHandle::resizeEvent(QResizeEvent *event)
{
    if (orientation() == Qt::Horizontal)
        setContentsMargins(2, 0, 2, 0);
    else
        setContentsMargins(0, 2, 0, 2);
    setMask(QRegion(contentsRect()));
    QSplitterHandle::resizeEvent(event);
}

void EvSplitterHandle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(),evApparenceSettings->darkColor());
}
