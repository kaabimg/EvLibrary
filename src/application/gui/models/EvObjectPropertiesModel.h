#ifndef EVOBJECTPROPERTIESMODEL_H
#define EVOBJECTPROPERTIESMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QByteArray>

class EvObject;

class EvObjectPropertiesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EvObjectPropertiesModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

public Q_SLOTS:
    void setObject(EvObject*);

private:

    EvObject * m_item;
    QList<QByteArray> m_itemPropertiesNames;
};

#endif // EVOBJECTPROPERTIESMODEL_H
