#ifndef EVPROPERTYEDITORDELEGATE_H
#define EVPROPERTYEDITORDELEGATE_H

#include <QStyledItemDelegate>

class EvPropertyAbstractDelegate;



class EvPropertyEditorDelegateManager : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EvPropertyEditorDelegateManager(QObject *parent = 0);

    QWidget *createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    void setEditorData(
            QWidget *editor,
            const QModelIndex &index) const;

    void setModelData(
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index) const;

    void updateEditorGeometry(
            QWidget *editor,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;


    void registerPropertyDelegate(EvPropertyAbstractDelegate * );

private:
    QHash<int,EvPropertyAbstractDelegate*> m_delegates;

};

#endif // EVPROPERTYEDITORDELEGATE_H
