#include "EvFileDelegate.h"
#include <QFileDialog>
#include <QLineEdit>
#include "EvEditWidget.h"

QWidget *EvFileDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new EvEditWidget(new QLineEdit,parent);
}

void EvFileDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    qobject_cast<QLineEdit*>(editWidget->widget())->setText((property(index)->value().toString()));
    editWidget->setData(index.internalPointer());
    disconnect(editWidget,0,this,0);
    connect(editWidget,SIGNAL(editRequest()),this,SLOT(browseFile()));
}

void EvFileDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    model->setData(
                index,
                qobject_cast<QLineEdit*>(editWidget->widget())->text(),
                Qt::EditRole );
}

void EvFileDelegate::browseFile()
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(sender());
    EvProperty * property = static_cast<EvProperty*>(editWidget->data());
    QString dir = QDir::homePath();
    if(property->hasAttribute("dir"))
        dir = property->attribute("dir").toString();

    QString filter;
    if(property->hasAttribute("filters"))
        filter = property->attribute("filters").toString();

    QString file = QFileDialog::getOpenFileName(
                editWidget,
                property->label(),
                dir,
                filter);

    if(!file.isEmpty())
        qobject_cast<QLineEdit*>(editWidget->widget())->setText(file);
}
