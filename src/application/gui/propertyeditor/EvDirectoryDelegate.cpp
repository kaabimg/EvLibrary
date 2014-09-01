#include "EvDirectoryDelegate.h"
#include <QLineEdit>
#include <QFileDialog>
#include "EvEditWidget.h"

QWidget *EvDirectoryDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new EvEditWidget(new QLineEdit,parent);
}

void EvDirectoryDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    qobject_cast<QLineEdit*>(editWidget->widget())->setText((property(index)->value().toString()));
    editWidget->setData(index.internalPointer());
    disconnect(editWidget,0,this,0);
    connect(editWidget,SIGNAL(editRequest()),this,SLOT(browseDirectory()));
}

void EvDirectoryDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    model->setData(
                index,
                qobject_cast<QLineEdit*>(editWidget->widget())->text(),
                Qt::EditRole );
}

void EvDirectoryDelegate::browseDirectory()
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(sender());
    EvProperty * property = static_cast<EvProperty*>(editWidget->data());
    QString file = QFileDialog::getExistingDirectory(
                editWidget,
                property->label(),
                property->value().toString()
                );

    if(!file.isEmpty())
        qobject_cast<QLineEdit*>(editWidget->widget())->setText(file);
}
