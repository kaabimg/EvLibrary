#include "EvDoubleDelegate.h"
#include <QDoubleSpinBox>

#include <limits>

QWidget *EvDoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new QDoubleSpinBox(parent);

}

void EvDoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDoubleSpinBox * spinBox = qobject_cast<QDoubleSpinBox*>(editor);

    EvProperty * p = property(index);

    if(p->hasAttribute("min"))
        spinBox->setMinimum(p->attribute("min").toDouble());
    else
        spinBox->setMinimum(std::numeric_limits<double>::min());

    if(p->hasAttribute("max"))
        spinBox->setMaximum(p->attribute("max").toDouble());
    else
        spinBox->setMaximum(std::numeric_limits<double>::max());

    if(p->hasAttribute("step"))
        spinBox->setSingleStep(p->attribute("step").toDouble());
    else
        spinBox->setSingleStep(0.001);

    spinBox->setValue(p->value().toDouble());
}

void EvDoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,qobject_cast<QDoubleSpinBox*>(editor)->value(),Qt::EditRole);
}


