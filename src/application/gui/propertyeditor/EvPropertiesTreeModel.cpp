#include "EvPropertiesTreeModel.h"
#include "EvSpiceNumber.h"
#include "EvVariantUtils.h"

#include <QFont>

EvPropertiesTreeModel::EvPropertiesTreeModel(EvProperty *property, QObject *parent):
    QAbstractItemModel(parent),
    m_topProperty(property)
{
    m_object = NULL;
    for(int i=0;i<m_topProperty->count<EvProperty>();i++){
        property =m_topProperty->child<EvProperty>(i);
        qDebug()<<property;
        if(property->visible())
            m_topProperties << property;
    }
    connect(m_topProperty,SIGNAL(visiblePropertiesChanged()),this,SLOT(onVisiblePropertiesChanged()));
    connectTopProperties();
}

EvPropertiesTreeModel::EvPropertiesTreeModel(
        const EvPropertiesList & list,
        QObject *parent) :
    QAbstractItemModel(parent)
{
    m_topProperties = list;
    m_object = NULL;
    connectTopProperties();

}

EvPropertiesTreeModel::EvPropertiesTreeModel(
        EvObject *object,
        QObject *parent) :
    QAbstractItemModel(parent)
{
    m_topProperties = object->designablePropertiesWrappers();
    m_object = object;
    connectTopProperties();
    connect(object,SIGNAL(designablePropertiesChanged()),this,SLOT(onObjectPropertiesChanged()));

}


void EvPropertiesTreeModel::connectTopProperties()
{
    for (int i = 0; i < m_topProperties.size(); ++i) {
        connectProperty(m_topProperties[i]);
    }
}

void EvPropertiesTreeModel::disconnectTopProperties()
{
    for (int i = 0; i < m_topProperties.size(); ++i) {
        disconnectProperty(m_topProperties[i]);
    }
}

void EvPropertiesTreeModel::connectProperty(EvProperty * property)
{
     connect(property,SIGNAL(valueChanged()),this,SLOT(onPropertyChanged()));
     connect(property,SIGNAL(visiblePropertiesChanged()),this,SLOT(onVisiblePropertiesChanged()));
}

void EvPropertiesTreeModel::disconnectProperty(EvProperty * property)
{
    disconnect(property,SIGNAL(valueChanged()),this,SLOT(onPropertyChanged()));
    disconnect(property,SIGNAL(visiblePropertiesChanged()),this,SLOT(onVisiblePropertiesChanged()));
}


QModelIndex EvPropertiesTreeModel::index(int row, int column, const QModelIndex & index) const
{
    if(index.isValid()){
        EvProperty * property = static_cast<EvProperty*>(index.internalPointer());
        EvProperty * subProperty = property->visibleSubProperty(row);
        return createIndex (row,column, subProperty);
    }
    return createIndex (row,column, m_topProperties[row]);
}

QModelIndex EvPropertiesTreeModel::parent(const QModelIndex & index) const
{
    if(index.isValid()){
        EvProperty * property = static_cast<EvProperty*>(index.internalPointer());
        EvProperty * parent = property->parentEvObject()->to<EvProperty>();
        if(parent){
            return createIndex (parent->visiblePropertyIndex(property),0, parent);
        }

    }
    return QModelIndex();
}

int EvPropertiesTreeModel::rowCount(const QModelIndex & index) const
{
    if(index.isValid()){
        EvProperty * property = static_cast<EvProperty*>(index.internalPointer());
        return property->visibleSubPropertiesCount();
    }
    return m_topProperties.size();
}

int EvPropertiesTreeModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant EvPropertiesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    EvProperty  * property = static_cast<EvProperty*>(index.internalPointer());
    if(property == NULL){
        property = m_topProperty;
    }
    qDebug()<<index<<property;

    switch (index.column()) {
        case 0:{
            return property->label();
            break;
        }
        case 1:{
            switch (property->editMode()) {
            case EvProperty::SpiceNumber:
                return  qvariant_cast<EvSpiceNumber>(property->value()).toString();
            case EvProperty::Font:
                return  Ev::fontToString(qvariant_cast<QFont>(property->value()));
            default:
                break;
            }
            return property->value();
            break;
        }

        default:
            return QVariant();
            break;
     }
    return QVariant();
}

bool EvPropertiesTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    EvProperty  * property = static_cast<EvProperty*>(index.internalPointer());

    if(role == Qt::EditRole){
        property->setValue(value);
        return true;
    }
    else
        return QAbstractItemModel::setData(index,value,role);
}

QVariant EvPropertiesTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags EvPropertiesTreeModel::flags(const QModelIndex &index) const
{

    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if(index.column() == 0)
        return QAbstractItemModel::flags(index) ;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    EvProperty  * property = static_cast<EvProperty*>(index.internalPointer());

    if(property && !(property->hasSubProperties() || property->readOnly())){
        flags |= Qt::ItemIsEditable ;
    }
    return flags;
}

void EvPropertiesTreeModel::onObjectPropertiesChanged()
{
    beginResetModel();
    qDeleteAll(m_topProperties);
    m_topProperties = m_object->designablePropertiesWrappers();
    connectTopProperties();
    endResetModel();
}

void EvPropertiesTreeModel::onPropertyChanged()
{
    EvProperty * property = qobject_cast<EvProperty*>(sender());
    Q_ASSERT(property);
    int index = m_topProperties.indexOf(property);
    Q_ASSERT(index >-1);
    Q_EMIT dataChanged(createIndex(index,1),createIndex(index,1));


}



void EvPropertiesTreeModel::onVisiblePropertiesChanged()
{
    qDebug()<<"onVisiblePropertiesChanged";
    EvProperty * property  = qobject_cast<EvProperty*>(sender());


    beginResetModel();
    if(m_topProperties.contains(property)){
        disconnectTopProperties();
        m_topProperties.clear();
        EvProperty * property;
        for(int i=0;i<m_topProperty->count<EvProperty>();i++){
            property =m_topProperty->child<EvProperty>(i);
            qDebug()<<property;
            if(property->visible())
                m_topProperties << property;
        }

    }


    endResetModel();
}
