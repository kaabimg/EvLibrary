#include "EvParameterValueDelegate.h"
#include <QLineEdit>
#include "EvEditWidget.h"

#include "EvParameter.h"
#include "EvDialog.h"
#include "EvPropertiesListView.h"

EvParameterValueDelegate::EvParameterValueDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *EvParameterValueDelegate::createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &,
        const QModelIndex &) const
{
    return new EvEditWidget(new QLineEdit,parent);

}

void EvParameterValueDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    qobject_cast<QLineEdit*>(editWidget->widget())->setText(
                static_cast<EvParameter*>(index.internalPointer())->textualValue());
    editWidget->setData(index.internalPointer());
    disconnect(editWidget,0,this,0);
    connect(editWidget,SIGNAL(editRequest()),this,SLOT(editParameter()));
}

void EvParameterValueDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    model->setData(
                index,
                qobject_cast<QLineEdit*>(editWidget->widget())->text(),
                Qt::EditRole );
}

void EvParameterValueDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}

void EvParameterValueDelegate::editParameter()
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(sender());

    EvParameter * parameter = static_cast<EvParameter*>(editWidget->data());
    EvParameter * clone = parameter->copy()->to<EvParameter>();


    EvDialog dialog(EvDialog::Ok | EvDialog::Cancel);
    dialog.setTitle("Edit parameter "+parameter->objectName());

    EvPropertiesListView * properties = new EvPropertiesListView(clone,&dialog);
    dialog.addContent(properties);
    dialog.resize(400,500);

    EvDialog::Button ret = dialog.exec();

    if(ret == EvDialog::Ok){
        qobject_cast<QLineEdit*>(editWidget->widget())->setText(clone->buildTextualValue());
    }

    clone->deleteLater();
}
