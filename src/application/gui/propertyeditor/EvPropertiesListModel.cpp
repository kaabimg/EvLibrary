#include "EvPropertiesListModel.h"
#include "EvSpiceNumber.h"
#include "EvVariantUtils.h"

#include <QFont>

EvPropertiesListModel::EvPropertiesListModel(EvProperty *group, QObject *parent):
    QAbstractItemModel(parent),
    m_propertiesGroup(group)
{
    m_object = NULL;
    onVisiblePropertiesChanged();
    connect(m_propertiesGroup,SIGNAL(visiblePropertiesChanged()),this,SLOT(onVisiblePropertiesChanged()));
    connectProperties();
}

EvPropertiesListModel::EvPropertiesListModel(
        const EvPropertiesList & list,
        QObject *parent) :
    QAbstractItemModel(parent)
{
    m_properties = list;
    m_object = NULL;
    connectProperties();

}

EvPropertiesListModel::EvPropertiesListModel(
        EvObject *object,
        QObject *parent) :
    QAbstractItemModel(parent)
{
    m_properties = object->designablePropertiesWrappers();
    m_object = object;
    connectProperties();
    connect(object,SIGNAL(designablePropertiesChanged()),this,SLOT(onObjectPropertiesChanged()));

}


void EvPropertiesListModel::connectProperties()
{
    for (int i = 0; i < m_properties.size(); ++i) {
        connect(m_properties[i],SIGNAL(valueChanged()),this,SLOT(onPropertyChanged()));
    }
}

void EvPropertiesListModel::disconnectProperties()
{
    for (int i = 0; i < m_properties.size(); ++i) {
        disconnect(m_properties[i],SIGNAL(valueChanged()),this,SLOT(onPropertyChanged()));
    }
}


QModelIndex EvPropertiesListModel::index(int row, int column, const QModelIndex &) const
{
    QModelIndex index = createIndex (row,column,column == 1 ? m_properties[row] : NULL);
    return index;
}

QModelIndex EvPropertiesListModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int EvPropertiesListModel::rowCount(const QModelIndex &) const
{
    return m_properties.size();
}

int EvPropertiesListModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant EvPropertiesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    switch (index.column()) {
        case 0:{
            return m_properties[index.row()]->label();
            break;
        }
        case 1:{
            switch (m_properties[index.row()]->editMode()) {
            case EvProperty::SpiceNumber:
                return  qvariant_cast<EvSpiceNumber>(m_properties[index.row()]->value()).toString();
            case EvProperty::Font:
                return  Ev::fontToString(qvariant_cast<QFont>(m_properties[index.row()]->value()));
            default:
                break;
            }
            return m_properties[index.row()]->value();
            break;
        }

        default:
            return QVariant();
            break;
     }
    return QVariant();
}

bool EvPropertiesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole){
        m_properties[index.row()]->setValue(value);
        return true;
    }
    else
        return QAbstractItemModel::setData(index,value,role);
}

QVariant EvPropertiesListModel::headerData(int section, Qt::Orientation orientation, int role) const
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
    return QAbstractItemModel::headerData(section,orientation,role);
}

Qt::ItemFlags EvPropertiesListModel::flags(const QModelIndex &index) const
{

    if (!index.isValid())
        return Qt::NoItemFlags;
    if(index.column() == 0)
        return QAbstractItemModel::flags(index) | Qt::ItemNeverHasChildren;

    Qt::ItemFlags flags = Qt::ItemNeverHasChildren;

    EvProperty * property = static_cast<EvProperty*>(index.internalPointer());
    if(!property->readOnly()){
        flags |= Qt::ItemIsEditable ;
    }
    if(property->enabled()){
        flags |= Qt::ItemIsEnabled ;
    }

    return flags;
}

void EvPropertiesListModel::onObjectPropertiesChanged()
{
    beginResetModel();
    qDeleteAll(m_properties);
    m_properties = m_object->designablePropertiesWrappers();
    connectProperties();
    endResetModel();
}

void EvPropertiesListModel::onPropertyChanged()
{
    EvProperty * property = qobject_cast<EvProperty*>(sender());
    Q_ASSERT(property);
    int index = m_properties.indexOf(property);
    Q_ASSERT(index >-1);
    Q_EMIT dataChanged(createIndex(index,1),createIndex(index,1));


}

void EvPropertiesListModel::onVisiblePropertiesChanged()
{
    beginResetModel();

    disconnectProperties();
    m_properties.clear();
    EvProperty * property;
    for(int i=0;i<m_propertiesGroup->count<EvProperty>();i++){
        property =m_propertiesGroup->child<EvProperty>(i);
        if(property->visible())
            m_properties << property;
    }

    endResetModel();
}

