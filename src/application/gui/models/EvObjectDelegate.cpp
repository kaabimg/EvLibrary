#include "EvObjectDelegate.h"
#include "EvObjectModelPainter.h"

EvObjectDelegate::EvObjectDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void EvObjectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{   
    EvObjectModelPainter::paint(painter,option,index);
}
