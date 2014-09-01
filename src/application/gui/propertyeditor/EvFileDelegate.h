#ifndef EVFILEDELEGATE_H
#define EVFILEDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvFileDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvFileDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::File;}

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


protected Q_SLOTS:
    void browseFile();
};

#endif // EVFILEDELEGATE_H
