#ifndef EVSTRINGDELEGATE_H
#define EVSTRINGDELEGATE_H


#include "EvPropertyAbstractDelegate.h"


class EvStringDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvStringDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::String;}

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

#endif // EVSTRINGDELEGATE_H
