#include "EvObjectsListModel.h"
#include "EvObject.h"
#include "EvObjectsContainer.h"
#include "EvAppSettings.h"


EvObjectsListModel::EvObjectsListModel(EvObjectsContainer * objects,QObject *parent) :
    QAbstractListModel(parent),
    m_objectsContainer(objects)
{
    connect(m_objectsContainer,SIGNAL(objectAdded(EvObject*)),this,SLOT(onContentChanged()));
    connect(m_objectsContainer,SIGNAL(objectRemoved(EvObject*)),this,SLOT(onContentChanged()));
    setIconStyle(EvIconsFactory::Dark);

}



int EvObjectsListModel::rowCount(const QModelIndex &) const
{
    return m_objectsContainer->count();
}


QVariant EvObjectsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();




    if(role == Qt::DecorationRole){
        return evIconsFactory->objectIcon(
                    m_objectsContainer->at(index.row())->typeId(),
                    (EvIconsFactory::IconStyle)m_iconStyle);
    }

    if (role != Qt::DisplayRole)
        return QVariant();


    if(index.column() == 0)
        return m_objectsContainer->at(index.row())->objectName();


    return QVariant();
}

QVariant EvObjectsListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return "Name";
            break;
        default:
            break;
        }
    }
    return QVariant();
}

void EvObjectsListModel::setContent(const EvObjectsList &list)
{
    beginResetModel();
    m_objectsContainer->blockSignals(true);
    m_objectsContainer->clear();
    m_objectsContainer->addObjects(list);
    m_objectsContainer->blockSignals(false);
    endResetModel();
}

void EvObjectsListModel::onContentChanged()
{
    beginResetModel();

    endResetModel();
}
