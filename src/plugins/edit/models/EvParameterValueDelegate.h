#ifndef EVPARAMETERVALUEDELEGATE_H
#define EVPARAMETERVALUEDELEGATE_H

#include <QStyledItemDelegate>

class EvParameterValueDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EvParameterValueDelegate(QObject *parent = 0);

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

protected Q_SLOTS:
    void editParameter();

};

#endif // EVPARAMETERVALUEDELEGATE_H
