#include "EvFontDelegate.h"

#include <QFontDialog>
#include <QLineEdit>

#include "EvEditWidget.h"

QWidget *EvFontDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return new EvEditWidget(new QLineEdit,parent);
}

void EvFontDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);

    QString text = qvariant_cast<QFont>(property(index)->value()).toString();
    qobject_cast<QLineEdit*>(editWidget->widget())->setText(text);
    editWidget->setData(index.internalPointer());
    disconnect(editWidget,0,this,0);
    connect(editWidget,SIGNAL(editRequest()),this,SLOT(chooseFont()));
}

void EvFontDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(editor);
    QFont font;
    if(font.fromString(qobject_cast<QLineEdit*>(editWidget->widget())->text())){
        model->setData(
                    index,
                    font,
                    Qt::EditRole );
    }
}


void EvFontDelegate::chooseFont()
{
    EvEditWidget * editWidget =  qobject_cast<EvEditWidget*>(sender());
    EvProperty * property = static_cast<EvProperty*>(editWidget->data());
    QFont initialFont;
    initialFont.fromString(qobject_cast<QLineEdit*>(editWidget->widget())->text());
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok,
                    initialFont,
                    editWidget,
                    property->label()
                );
    if(ok){
        qobject_cast<QLineEdit*>(editWidget->widget())->setText(font.toString());
    }
}
