#ifndef EVCOLORDELEGATE_H
#define EVCOLORDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvColorDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvColorDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Color;}

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

    bool paint(QPainter *, const QStyleOptionViewItem&,const QModelIndex &);

protected Q_SLOTS:
    void chooseColor();
};

#endif // EVCOLORDELEGATE_H
