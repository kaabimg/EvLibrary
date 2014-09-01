#ifndef EVINTDELEGATE_H
#define EVINTDELEGATE_H

#include "EvPropertyAbstractDelegate.h"

class EvIntDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvIntDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Int;}

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


};

#endif // EVINTDELEGATE_H
