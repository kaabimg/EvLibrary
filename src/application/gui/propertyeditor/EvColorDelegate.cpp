#include "EvColorDelegate.h"


#include <QPainter>

#include <QLineEdit>
#include <QColorDialog>
#include "EvEditWidget.h"



QWidget *EvColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new EvEditWidget(new QLineEdit,parent);
}

void EvColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);

    QString text = qvariant_cast<QColor>(property(index)->value()).name();
    qobject_cast<QLineEdit*>(editWidget->widget())->setText(text);
    editWidget->setData(index.internalPointer());
    disconnect(editWidget,0,this,0);
    connect(editWidget,SIGNAL(editRequest()),this,SLOT(chooseColor()));
}

void EvColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);

    QColor color = QColor(qobject_cast<QLineEdit*>(editWidget->widget())->text());
    if(color.isValid())
        model->setData(
                    index,
                    color,
                    Qt::EditRole );
}

void EvColorDelegate::chooseColor()
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(sender());
    EvProperty * property = static_cast<EvProperty*>(editWidget->data());
    QColor initialColor = QColor(qobject_cast<QLineEdit*>(editWidget->widget())->text());
    QColor color = QColorDialog::getColor(
                initialColor,
                editWidget,
                property->label()
                );

    if(color.isValid())
        qobject_cast<QLineEdit*>(editWidget->widget())->setText(color.name());
}

bool EvColorDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
{
    painter->fillRect(option.rect,qvariant_cast<QColor>(property(index)->value()));
    return true;
}
