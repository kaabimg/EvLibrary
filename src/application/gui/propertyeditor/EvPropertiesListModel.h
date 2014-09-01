#ifndef EVPROPERTIESLISTMODEL_H
#define EVPROPERTIESLISTMODEL_H

#include <QAbstractItemModel>
#include "EvProperty.h"

class EvPropertiesListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit EvPropertiesListModel(EvProperty * group,QObject *parent = 0);

    explicit EvPropertiesListModel(const EvPropertiesList & list,QObject *parent = 0);
    explicit EvPropertiesListModel(EvObject  * object,QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex())const;
    virtual QModelIndex parent(const QModelIndex &) const ;



    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);


    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;


protected Q_SLOTS:
    void onObjectPropertiesChanged();
    void onPropertyChanged();
    void onVisiblePropertiesChanged();

protected:
    void connectProperties();
    void disconnectProperties();

private:
    EvObject  * m_object;
    EvPropertiesList m_properties;
    EvProperty * m_propertiesGroup;

};

#endif // EVPROPERTIESLISTMODEL_H
