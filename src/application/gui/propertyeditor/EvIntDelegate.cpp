#include "EvIntDelegate.h"
#include <QSpinBox>
#include <limits>


QWidget *EvIntDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new QSpinBox(parent);
}

void EvIntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox * spinBox = qobject_cast<QSpinBox*>(editor);
    EvProperty * p = property(index);

    if(p->hasAttribute("min"))
        spinBox->setMinimum(p->attribute("min").toInt());
    else
        spinBox->setMinimum(std::numeric_limits<int>::min());

    if(p->hasAttribute("max"))
        spinBox->setMaximum(p->attribute("max").toInt());
    else
        spinBox->setMaximum(std::numeric_limits<int>::max());

    if(p->hasAttribute("step"))
        spinBox->setSingleStep(p->attribute("step").toInt());
    else
        spinBox->setSingleStep(1);

    spinBox->setValue(p->value().toInt());
}

void EvIntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,qobject_cast<QSpinBox*>(editor)->value(),Qt::EditRole);
}

