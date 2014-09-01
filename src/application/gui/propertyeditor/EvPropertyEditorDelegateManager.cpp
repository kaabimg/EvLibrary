#include "EvPropertyEditorDelegateManager.h"
#include "EvProperty.h"
#include "EvPropertyAbstractDelegate.h"
#include "EvStringDelegate.h"
#include "EvIntDelegate.h"
#include "EvDoubleDelegate.h"
#include "EvColorDelegate.h"
#include "EvFileDelegate.h"
#include "EvDirectoryDelegate.h"
#include "EvEnumDelegate.h"
#include "EvFontDelegate.h"
#include "EvBoolDelegate.h"
#include "EvSpiceNumberDelegate.h"


#include <QLineEdit>
#include <QPainter>

EvPropertyEditorDelegateManager::EvPropertyEditorDelegateManager(QObject *parent) :
    QStyledItemDelegate(parent)
{
    registerPropertyDelegate(new EvIntDelegate);
    registerPropertyDelegate(new EvDoubleDelegate);
    registerPropertyDelegate(new EvColorDelegate);
    registerPropertyDelegate(new EvFileDelegate);
    registerPropertyDelegate(new EvDirectoryDelegate);
    registerPropertyDelegate(new EvEnumDelegate);
    registerPropertyDelegate(new EvFontDelegate);
    registerPropertyDelegate(new EvBoolDelegate);
    registerPropertyDelegate(new EvStringDelegate);
    registerPropertyDelegate(new EvSpiceNumberDelegate);



}

QWidget *EvPropertyEditorDelegateManager::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int type = static_cast<EvProperty *>(index.internalPointer())->editMode();
    if(m_delegates.contains(type))
        return m_delegates.value(type)->createEditor(parent,option,index);
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void EvPropertyEditorDelegateManager::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int type = static_cast<EvProperty *>(index.internalPointer())->editMode();
    if(m_delegates.contains(type))
        return m_delegates.value(type)->setEditorData(editor,index);
     return QStyledItemDelegate::setEditorData(editor,index);
}

void EvPropertyEditorDelegateManager::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int type = static_cast<EvProperty *>(index.internalPointer())->editMode();
    if(m_delegates.contains(type))
         m_delegates.value(type)->setModelData(editor,model,index);
    else if(type == EvProperty::String){
        QLineEdit * lineEdit = qobject_cast<QLineEdit*>(editor);
        if(lineEdit)
            model->setData(index,lineEdit->text(),Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(editor,model,index);
}

void EvPropertyEditorDelegateManager::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int type = static_cast<EvProperty *>(index.internalPointer())->editMode();
    if(m_delegates.contains(type))
        return m_delegates.value(type)->updateEditorGeometry(editor,option,index);
    return QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}

void EvPropertyEditorDelegateManager::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        EvProperty * property = static_cast<EvProperty *>(index.internalPointer());
        int type = property->editMode();
        if(m_delegates.contains(type)){
            if(m_delegates.value(type)->paint(painter,option,index))
                return;
        }
    }
    QStyledItemDelegate::paint(painter,option,index);

}

void EvPropertyEditorDelegateManager::registerPropertyDelegate(EvPropertyAbstractDelegate * delegate)
{
    delegate->setParent(this);
    m_delegates.insert(delegate->propertyType(),delegate);
    connect(delegate,SIGNAL(commitData(QWidget*)),
            this,SIGNAL(commitData(QWidget*)));
}
