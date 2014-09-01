#ifndef EVDOUBLEDELEGATE_H
#define EVDOUBLEDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvDoubleDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT

public:
    EvDoubleDelegate(QObject * parent =0):EvPropertyAbstractDelegate(parent){}

    int propertyType()const{return EvProperty::Double;}


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

#endif // EVDOUBLEDELEGATE_H
