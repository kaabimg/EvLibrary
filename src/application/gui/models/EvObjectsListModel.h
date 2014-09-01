#ifndef EVOBJECTSLISTMODEL_H
#define EVOBJECTSLISTMODEL_H

#include <QAbstractListModel>
#include "EvObject.h"
class EvObjectsContainer;

class EvObjectsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EvObjectsListModel(EvObjectsContainer * ,QObject *parent = 0);
    void setIconStyle(int style){
        m_iconStyle = style;
    }

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    void setContent(const EvObjectsList & list);

protected Q_SLOTS:
    void onContentChanged();

private:
    EvObjectsContainer * m_objectsContainer;
    int m_iconStyle;
};

#endif // EVOBJECTSLISTMODE_H
