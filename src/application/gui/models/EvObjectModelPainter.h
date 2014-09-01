#ifndef EVOBJECTMODELPAINTER_H
#define EVOBJECTMODELPAINTER_H

class QPainter;
class QStyleOptionViewItem;
class QModelIndex;
class QRect;

struct EvObjectModelPainter
{



    static void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);



    static void adjustIconRect(QRect & rect);

};

#endif // EVOBJECTMODELPAINTER_H
