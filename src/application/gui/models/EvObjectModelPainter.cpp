#include "EvObjectModelPainter.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include "EvObject.h"
#include "EvAppSettings.h"
#include "EvObjectsTreeView.h"
#include "EvObjectsTreeModel.h"

void EvObjectModelPainter::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index)
{
    EvObject * object = static_cast<EvObject*>(index.internalPointer());

    const EvObjectsTreeModel * model = qobject_cast<const EvObjectsTreeModel*>(index.model());
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    int size = option.rect.height();
    QFont font = model->font();


    QRect backgroundRect  = QRect(
                0,
                option.rect.topLeft().y(),
                option.rect.topLeft().x()+option.rect.width(),
                size
                );



    if(option.state.testFlag(QStyle::State_Selected)){
        painter->fillRect(backgroundRect,evApparenceSettings->primaryColor());
        font.setBold(true);
    }
    else if(option.state.testFlag(QStyle::State_MouseOver)){
        painter->fillRect(backgroundRect,QColor(230,230,230,70));
    }


    QRect childrenIndicatorRect = QRect(
                option.rect.topLeft(),
                QSize(size,size)
                );

    childrenIndicatorRect.translate(-size,0);

    if(model->hasChildren(index)){
        QPainterPath path;
        path.addEllipse(childrenIndicatorRect.center(),size/8,size/8);
        painter->fillPath(path,evApparenceSettings->ligthGraycolor());
    }


    painter->setPen(QPen(QBrush(evApparenceSettings->darkColor()),0.1f));
    painter->drawLine(QLineF(backgroundRect.topLeft(),backgroundRect.topRight()));
    painter->drawLine(QLineF(backgroundRect.bottomLeft(),backgroundRect.bottomRight()));

    QRect iconRect = QRect(option.rect.topLeft(),QSize(size,size));
    adjustIconRect(iconRect);

    evIconsFactory->objectIcon(object->typeId(),EvIconsFactory::Light).paint(
                painter,
                iconRect
                );


    QRect textRect = QRect(iconRect.topRight(),backgroundRect.bottomRight());
    painter->setPen(evApparenceSettings->ligthColor());

    painter->setFont(font);

    QFontMetrics metrics(font);
    QString text = "  "+index.model()->data(index,Qt::DisplayRole).toString();

    painter->drawText(
                textRect,
                Qt::AlignVCenter | Qt::AlignLeft,
                metrics.elidedText(text,Qt::ElideMiddle,textRect.width())
             );



    painter->restore();
}

void EvObjectModelPainter::adjustIconRect(QRect &rect)
{
    rect.adjust(4,4,-4,-4);
}
