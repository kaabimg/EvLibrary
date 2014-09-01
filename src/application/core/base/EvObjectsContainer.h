#ifndef EVOBJECTSCONTAINER_H
#define EVOBJECTSCONTAINER_H

#include <QObject>
class EvObject;

class EvObjectsContainer : public QObject
{
    Q_OBJECT
public:
    explicit EvObjectsContainer(QObject *parent = 0);
    explicit EvObjectsContainer(const EvObjectsContainer &);
    bool deleteRemovedObjects() const;

    int count()const;
    EvObject * at(int i)const;
    bool contains(const EvObject *)const;
    bool contains(const QString &)const;
    QList<EvObject *> objects()const;
    int indexOf(const EvObject *)const;
    void clear();


Q_SIGNALS:
    void cleared();
    void objectAdded(EvObject*);
    void objectRemoved(EvObject*);

public Q_SLOTS:
    bool addObject(EvObject*,int index = -1);
    bool addObjects(const QList<EvObject*> &);

    bool removeObject(EvObject*);
    bool deleteObject(EvObject*);

    void setDeleteRemovedObjects(bool arg);

protected Q_SLOTS:
    bool removeObjectFromList(EvObject*);
private:
    QList<EvObject*> m_objects;
    bool m_deleteRemovedObjects;
};

#endif // EVOBJECTSCONTAINER_H
