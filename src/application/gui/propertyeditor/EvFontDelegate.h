#ifndef EVFONTDELEGATE_H
#define EVFONTDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvFontDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvFontDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Font;}

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
    void chooseFont();
};

#endif // EVFONTDELEGATE_H
