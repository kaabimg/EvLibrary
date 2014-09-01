#ifndef EVENUMDELEGATE_H
#define EVENUMDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvEnumDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvEnumDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Enum;}

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

#endif // EVENUMDELEGATE_H
