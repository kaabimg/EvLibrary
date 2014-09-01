#include "EvStringDelegate.h"
#include <QLineEdit>



QWidget *EvStringDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new QLineEdit(parent);
}

void EvStringDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit * lineEdit = qobject_cast<QLineEdit*>(editor);
    lineEdit->setText(property(index)->value().toString());

}

void EvStringDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,qobject_cast<QLineEdit*>(editor)->text(),Qt::EditRole);
}

