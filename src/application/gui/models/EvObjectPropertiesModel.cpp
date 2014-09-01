#include "EvObjectPropertiesModel.h"

#include "EvObject.h"

EvObjectPropertiesModel::EvObjectPropertiesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int EvObjectPropertiesModel::rowCount(const QModelIndex &) const
{
    return m_itemPropertiesNames.size();
}

int EvObjectPropertiesModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant EvObjectPropertiesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();


    switch (index.column()) {
        case 0:{
        return m_itemPropertiesNames[index.row()];
            break;
        }
        case 1:{
            return Ev::variantToString(m_item->property(m_itemPropertiesNames[index.row()].constData()));
            break;
        }

        default:
            return QVariant();
            break;
     }
    return QVariant();
}

QVariant EvObjectPropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return "Property";
            break;
        case 1:
            return "Value";
            break;
        default:
            break;
        }
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

Qt::ItemFlags EvObjectPropertiesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index)| Qt::ItemIsEditable;
}

void EvObjectPropertiesModel::setObject(EvObject * item)
{
    if(m_item == item)
        return;
    beginResetModel();

    m_item = item;
    if(m_item){
        m_itemPropertiesNames = m_item->designablePropertiesNames();
        m_itemPropertiesNames.removeOne("description");
        m_itemPropertiesNames.removeOne("name");
    }
    else
        m_itemPropertiesNames.clear();


    endResetModel();
}
