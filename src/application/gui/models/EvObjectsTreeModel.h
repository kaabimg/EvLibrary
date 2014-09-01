#ifndef EVOBJECTSTREEMODEL_H
#define EVOBJECTSTREEMODEL_H

#include <QAbstractItemModel>
#include <QFont>
#include <QSet>
class EvObject;


class EvObjectsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(bool rootVisible READ rootVisible WRITE setRootVisible)
    Q_PROPERTY(QFont font READ font WRITE setFont)
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly)
public:

    explicit EvObjectsTreeModel(EvObject * ,QObject *parent = 0);

    EvObject * rootObject()const;
    QModelIndex createIndexForObject(EvObject *object)const;

public:
    virtual QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const ;
    virtual QModelIndex parent(const QModelIndex &child) const ;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QFont font() const;
    bool rootVisible() const;
    int rowHeight() const;
    bool readOnly() const;

    void setLeafsTypes(const QSet<int> &);


    void addFilter(int type,int childType);
    void clearFilter(int type);
    void clearFilters();

Q_SIGNALS:
    void expandRequest(const QModelIndex &);

public Q_SLOTS:
    void setFont(const QFont& arg);
    void setRootVisible(bool arg);
    void setRowHeight(int arg);
    void setReadOnly(bool arg);

protected Q_SLOTS:
    void onDataHierarchyChanged();

protected:
    EvObject * objectForIndex(const QModelIndex &)const;
    bool isLeaf(const QModelIndex &)const;
    friend class EvObjectsTreeView;
    int rowCount(const EvObject*)const;
    EvObject *child(const EvObject* parent, int index)const;


private:
    EvObject * m_rootObject;
    QFont m_font;
    bool m_rootVisible;
    int m_rowHeight;
    bool m_readOnly;
    QSet<int> m_leafsTypes;
    QHash<int, QList<int> >  m_typesFilters;
};

#endif // EVOBJECTSTREEMODEL_H
