#include "EvSpiceNumberDelegate.h"
#include "EvSpiceNumber.h"
#include <QLineEdit>


QWidget *EvSpiceNumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new QLineEdit(parent);

}

void EvSpiceNumberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit * lineEdit = qobject_cast<QLineEdit*>(editor);
    EvProperty * p = property(index);
    lineEdit->setText(qvariant_cast<EvSpiceNumber>(p->value()).toString());
}

void EvSpiceNumberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EvSpiceNumber number(qobject_cast<QLineEdit*>(editor)->text());
    if(number.isValid())
        model->setData(index,number,Qt::EditRole);
}

