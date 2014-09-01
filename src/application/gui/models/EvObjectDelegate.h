#ifndef EVOBJECTDELEGATE_H
#define EVOBJECTDELEGATE_H

#include <QStyledItemDelegate>

class EvObjectDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EvObjectDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;
};

#endif // EVOBJECTDELEGATE_H
