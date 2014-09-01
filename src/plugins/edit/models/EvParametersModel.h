#ifndef EVPARAMETERSMODEL_H
#define EVPARAMETERSMODEL_H

#include <QAbstractTableModel>
class EvObject;
class EvProcess;
class EvCommandsInterface;

class EvParametersModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EvParametersModel(
            EvProcess * process,
            EvCommandsInterface * commandsInterface,
            QObject *parent = 0);


    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addParameter();
    void removeParameters();


protected Q_SLOTS:
    void onDataChanged(EvObject*);
    void onHierarchyChanged();

private:
    EvProcess * m_process;
    EvCommandsInterface * m_commandsInterface;
};

#endif // EVPARAMETERSMODEL_H
