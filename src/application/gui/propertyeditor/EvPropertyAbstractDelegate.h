#ifndef EVPROPERTYABSTRACTDELEGATE_H
#define EVPROPERTYABSTRACTDELEGATE_H

class QWidget;
class QModelIndex;
class QStyleOptionViewItem;
class QAbstractItemModel;

#include "EvProperty.h"

#include <QModelIndex>
#include <QStyleOptionViewItem>

class EvPropertyAbstractDelegate : public QObject
{
    Q_OBJECT
public:
    EvPropertyAbstractDelegate(QObject * parent = 0):QObject(parent){}

    virtual int propertyType()const=0;

    virtual QWidget *createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const =0;

    virtual void setEditorData(
            QWidget *editor,
            const QModelIndex &index) const=0;

    virtual void setModelData(
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index) const=0;

    virtual void updateEditorGeometry(
            QWidget *editor,
            const QStyleOptionViewItem &option,
            const QModelIndex &) const{
        editor->setGeometry(option.rect);
        }

    virtual bool paint(QPainter *, const QStyleOptionViewItem&,
                       const QModelIndex &){
        return false;
    }


Q_SIGNALS:
    void commitData(QWidget*);

protected Q_SLOTS:
    void emitCommitData()
    {
        QWidget * widget = qobject_cast<QWidget*>(sender());
        if(widget){
            Q_EMIT commitData(widget);
        }
    }


protected:
    EvProperty *property(const QModelIndex & index)const{
        return static_cast<EvProperty*>(index.internalPointer());
    }
};

#endif // EVPROPERTYABSTRACTDELEGATE_H



