#ifndef EVDIRECTORYDELEGATE_H
#define EVDIRECTORYDELEGATE_H

#include "EvPropertyAbstractDelegate.h"


class EvDirectoryDelegate : public EvPropertyAbstractDelegate
{
    Q_OBJECT
public:
    EvDirectoryDelegate():EvPropertyAbstractDelegate(){}

    int propertyType()const{return EvProperty::Directory;}

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
    void browseDirectory();
};

#endif // EVDIRECTORYDELEGATE_H
