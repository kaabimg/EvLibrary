#include "EvBoolDelegate.h"

#include <QCheckBox>

QWidget *EvBoolDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QWidget  * widget = new  QCheckBox(parent);
    connect(widget,SIGNAL(toggled(bool)),this,SLOT(emitCommitData()));
    return widget;
}

void EvBoolDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qobject_cast<QCheckBox*>(editor)->setChecked(property(index)->value().toBool());
}

void EvBoolDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,qobject_cast<QCheckBox*>(editor)->isChecked(),Qt::EditRole);
}

bool EvBoolDelegate::paint(QPainter * , const QStyleOptionViewItem & option, const QModelIndex & )
{
    if(option.state.testFlag(QStyle::State_Editing))
        return true;
    return false;
}
