#ifndef EVSPICENUMBERDELEGATE_H
#define EVSPICENUMBERDELEGATE_H


#include "EvPropertyAbstractDelegate.h"


class EvSpiceNumberDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT

public:
    EvSpiceNumberDelegate(QObject * parent =0):EvPropertyAbstractDelegate(parent){}

    int propertyType()const{return EvProperty::SpiceNumber;}


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

#endif // EVSPICENUMBERDELEGATE_H
