#include "EvEnumDelegate.h"
#include <QComboBox>
#include "EvVariantUtils.h"

QWidget *EvEnumDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QComboBox  * widget = new QComboBox(parent);
    connect(widget,SIGNAL(currentIndexChanged(int)),this,SLOT(emitCommitData()));
    return widget;
}

void EvEnumDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* combo = qobject_cast<QComboBox*>(editor);
    EvProperty * p = property(index);
    combo->addItems(Ev::variantListToStringList(p->attribute("keys").toList()));
    combo->setCurrentText(p->value().toString());
}

void EvEnumDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,qobject_cast<QComboBox*>(editor)->currentText(),Qt::EditRole);
}


