#include "EvParametersModel.h"
#include "EvProcess.h"
#include "EvParameter.h"
#include "EvCommandsInterface.h"

EvParametersModel::EvParametersModel(EvProcess *process,
                                     EvCommandsInterface *commandsInterface,
                                     QObject *parent) :
    QAbstractTableModel(parent),
    m_process(process),
    m_commandsInterface(commandsInterface)
{
    connect(m_process,SIGNAL(modified(EvObject*)),this,SLOT(onDataChanged(EvObject*)));
    connect(m_process,SIGNAL(objectAdded(EvObject*,EvObject*)),this,SLOT(onHierarchyChanged()));
    connect(m_process,SIGNAL(objectRemoved(EvObject*,EvObject*)),this,SLOT(onHierarchyChanged()));
}


int EvParametersModel::rowCount(const QModelIndex  & /*parent*/) const
{
    return m_process->count<EvParameter>();
}

int EvParametersModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;//name,type,textual value
}

QModelIndex EvParametersModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row,column,m_process->child<EvParameter>(row));
}

QVariant EvParametersModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        EvParameter * parameter = m_process->child<EvParameter>(index.row());
        switch (index.column()) {
        case 0:
            return parameter->objectName();
        case 1:
            return parameter->parameterTypeName();
        case 2:
            return parameter->textualValue();
        default:
            break;
        }
        return "";
    }
    return QVariant();

}

QVariant EvParametersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Type";
        case 2:
            return "Value";
        default:
            break;
        }
    }
    return QAbstractItemModel::headerData(section,orientation,role);
}

Qt::ItemFlags EvParametersModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    Qt::ItemFlags flags =
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsDragEnabled|
            Qt::ItemIsDropEnabled ;

    if(index.column() != 1){
        flags |= Qt::ItemIsEditable ;
    }

    return flags;
}

void EvParametersModel::addParameter()
{
    m_commandsInterface->addObject(m_process,Ev::Parameter);
}

void EvParametersModel::removeParameters()
{

}

void EvParametersModel::onDataChanged(EvObject * object)
{
    if(object->is<EvParameter>()){
        QModelIndex start = createIndex(m_process->indexOf(Ev::Parameter,object),0,object);
        QModelIndex stop = createIndex(m_process->indexOf(Ev::Parameter,object),2,object);
        Q_EMIT dataChanged(start,stop);
    }
}

void EvParametersModel::onHierarchyChanged()
{
   beginResetModel();
   endResetModel();
}

bool EvParametersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    EvParameter * parameter = m_process->child<EvParameter>(index.row());
    if(role == Qt::EditRole){
        switch (index.column()) {
        case 0:{
            m_commandsInterface->setObjectProperty(
                        parameter,
                        "name",
                        value );

            Q_EMIT dataChanged(index,index);
            return true;
        }
        case 2:{
            m_commandsInterface->setObjectProperty(
                        parameter,
                        "textualValue",
                        value );

            Q_EMIT dataChanged(index,index);
            return true;
        }
        default:
            break;
        }
    }
    return false;


}
