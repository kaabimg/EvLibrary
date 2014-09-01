#include "EvObjectsTreeModel.h"
#include "EvObject.h"
#include "EvApplication.h"
#include "EvIconsfactory.h"
#include "EvAppSettings.h"

EvObjectsTreeModel::EvObjectsTreeModel(EvObject * rootItem,QObject * parent) :
    QAbstractItemModel(parent),
    m_rootObject(rootItem),
    m_rootVisible(false),
    m_readOnly(false)
{    
    m_font = evApparenceSettings->font();
    m_font.setPointSizeF(m_font.pointSize() * 0.8);
    setRowHeight(35);

    connect(rootItem,SIGNAL(objectAdded(EvObject*,EvObject*)),this,SLOT(onDataHierarchyChanged()));

    connect(rootItem,SIGNAL(objectRemoved(EvObject*,EvObject*)),
            this,SLOT(onDataHierarchyChanged()));

}

EvObject *EvObjectsTreeModel::rootObject() const
{
    return m_rootObject;
}

QModelIndex EvObjectsTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    EvObject *item = static_cast<EvObject*>(index.internalPointer());
    if (item == m_rootObject)
        return QModelIndex();
    EvObject *parentItem = item->parentEvObject();
    return createIndexForObject(parentItem);
}

QModelIndex EvObjectsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    if (!parent.isValid()){
        if(rootVisible())   {
            return createIndex(row, column, m_rootObject);
        }
        else {

            return createIndex(row, column, m_rootObject->child(row));

        }
    }

    EvObject *parentItem = static_cast<EvObject*>(parent.internalPointer());
    EvObject *childItem = child(parentItem,row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


int EvObjectsTreeModel::rowCount(const QModelIndex &parent) const
{
    EvObject *parentItem;
    if (parent.column() > 0){
        return 0;
    }
    if (!parent.isValid()){
        if(rootVisible())   {
            return 1;
        }
        else {
            return m_rootObject->allChildrenCount();
        }

    }
    else
        parentItem = static_cast<EvObject*>(parent.internalPointer());

    if(isLeaf(parent)){
        return 0;
    }

    return rowCount(parentItem);
}

int EvObjectsTreeModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant EvObjectsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    switch (role) {
    case Qt::DisplayRole:{
        EvObject *item = objectForIndex(index);
        QString name = item->objectName();
        if(name.isEmpty())
            name = "unamed "+item->typeLabel().toLower();
        if(item->isTopLevelObject() && item->diskState() == Ev::Modified)
            name += "  *";
        return name;
    }
    case Qt::EditRole:{
        return objectForIndex(index)->objectName();
    }
    case Qt::ToolTipRole:{
        EvObject *item = static_cast<EvObject*>(index.internalPointer());
        return item->typeName();
    }
    case Qt::SizeHintRole:{
        return QSize(100,m_rowHeight);
    }
    case Qt::FontRole:{
        return m_font;
    }
    default:
        return QVariant();
    }
}

bool EvObjectsTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    switch (role) {
    case Qt::EditRole:{
        EvObject * object = objectForIndex(index);
        object->setObjectName(value.toString());
        Q_EMIT dataChanged(index,index);
        return true;
    }
    default:
        break;
    }
    return false;

}

QVariant EvObjectsTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return "Object";
    }
    return QAbstractItemModel::headerData(section,orientation,role);
}

Qt::ItemFlags EvObjectsTreeModel::flags(const QModelIndex & index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index)  | Qt::ItemIsDragEnabled;
    if(!m_readOnly){
        flags |= Qt::ItemIsEditable;
    }
    return  flags ;
}

bool EvObjectsTreeModel::rootVisible() const
{
    return m_rootVisible;
}

int EvObjectsTreeModel::rowHeight() const
{
    return m_rowHeight;
}

bool EvObjectsTreeModel::readOnly() const
{
    return m_readOnly;
}

void EvObjectsTreeModel::setLeafsTypes(const QSet<int> & types)
{
    m_leafsTypes = types;
}

void EvObjectsTreeModel::addFilter(int type, int childType)
{
    m_typesFilters[type].append(childType);
}

void EvObjectsTreeModel::clearFilters()
{
    m_typesFilters.clear();
}

void EvObjectsTreeModel::clearFilter(int type)
{
    m_typesFilters.remove(type);
}

QFont EvObjectsTreeModel::font() const
{
    return m_font;
}

void EvObjectsTreeModel::setRootVisible(bool arg)
{
    if (m_rootVisible != arg) {
        m_rootVisible = arg;
    }
}

void EvObjectsTreeModel::setRowHeight(int arg)
{
    m_rowHeight = arg;
}

void EvObjectsTreeModel::setReadOnly(bool arg)
{
    m_readOnly = arg;
}

void EvObjectsTreeModel::onDataHierarchyChanged()
{
    beginResetModel();
    endResetModel();
    Q_EMIT expandRequest(createIndex(0,0,m_rootObject));
}


EvObject *EvObjectsTreeModel::objectForIndex(const QModelIndex & index)const
{
    return static_cast<EvObject*>(index.internalPointer());
}

bool EvObjectsTreeModel::isLeaf(const QModelIndex & index) const
{
    return m_leafsTypes.size() && m_leafsTypes.contains(objectForIndex(index)->typeId());
}

int EvObjectsTreeModel::rowCount(const EvObject *parent)const
{
    if(m_typesFilters.contains(parent->typeId())){
        int count = 0;
        QList<int>  types = m_typesFilters.value(parent->typeId());
        foreach(int type,types){
            count += parent->childrenCount(type);
        }
        return count;
    }
    return parent->allChildrenCount();
}





QModelIndex EvObjectsTreeModel::createIndexForObject( EvObject * object) const
{
    if(object == m_rootObject ) {// root item
        return createIndex(0,0, m_rootObject);
    }
    else {
        EvObject * parent = object->parentEvObject();
        if(m_typesFilters.contains(parent->typeId())){
            int count = 0;
            QList<int>  types = m_typesFilters.value(parent->typeId());
            foreach(int type,types){
                if(type == object->typeId()){
                    count += parent->indexOf(type,object);
                    return createIndex(count,0, object);;
                }
                else {
                    count += parent->childrenCount(type);
                }

            }
            Q_ASSERT(false);
            return QModelIndex();
        }
        return createIndex(object->indexInParent(),0, object);
    }
}

EvObject * EvObjectsTreeModel::child(const EvObject *parent, int index)const
{
    if(m_typesFilters.contains(parent->typeId())){
        int count = 0;
        QList<int>  types = m_typesFilters.value(parent->typeId());
        foreach(int type,types){
            int size = parent->childrenCount(type);
            if(index<count+size){
                return  parent->child(type,index-count);
            }
            count += size;
        }
        Q_ASSERT(false);
        return NULL;
    }
    return parent->child(index);
}



void EvObjectsTreeModel::setFont(const QFont &arg)
{
    m_font = arg;
}

