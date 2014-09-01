#ifndef EVPROPERTIESTREEMODEL_H
#define EVPROPERTIESTREEMODEL_H

#include <QAbstractItemModel>
#include"EvProperty.h"
class EvObject;

class EvPropertiesTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit EvPropertiesTreeModel(EvProperty * property,QObject *parent = 0);
    explicit EvPropertiesTreeModel(const EvPropertiesList & list,QObject *parent = 0);
    explicit EvPropertiesTreeModel(EvObject  * object,QObject *parent = 0);

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
    void connectTopProperties();
    void disconnectTopProperties();

    void connectProperty(EvProperty*);
    void disconnectProperty(EvProperty*);

private:
    EvObject  * m_object;
    EvPropertiesList m_topProperties;
    EvProperty *m_topProperty;

};

#endif // EVPROPERTIESTREEMODEL_H
