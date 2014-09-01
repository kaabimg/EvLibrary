#ifndef EVBOOLDELEGATE_H
#define EVBOOLDELEGATE_H

#include "EvPropertyAbstractDelegate.h"

class EvBoolDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvBoolDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Boolean;}

    virtual QWidget *createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const ;

    virtual void setEditorData(
            QWidget *editor,
            const QModelIndex &index) const;

    virtual void setModelData(
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index) const;
    bool paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // EVBOOLDELEGATE_H
