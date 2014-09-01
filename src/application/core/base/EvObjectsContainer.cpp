#include "EvObjectsContainer.h"
#include "EvObject.h"

EvObjectsContainer::EvObjectsContainer(QObject *parent) :
    QObject(parent),m_deleteRemovedObjects(false)
{
}

EvObjectsContainer::EvObjectsContainer(const EvObjectsContainer & another):
    QObject(NULL)
{
    addObjects(another.m_objects);
}

int EvObjectsContainer::count()const
{
    return m_objects.count();
}

EvObject *EvObjectsContainer::at(int i) const
{
    return m_objects.at(i);
}

bool EvObjectsContainer::contains(const EvObject * object) const
{
    return m_objects.contains(const_cast<EvObject*>(object));
}

bool EvObjectsContainer::contains(const QString & name) const
{
    for(int i = 0;i<m_objects.size();++i){
        if(m_objects[i]->objectName() == name)
            return true;
    }
    return false;
}

QList<EvObject *> EvObjectsContainer::objects() const
{
    return m_objects;
}

int EvObjectsContainer::indexOf(const EvObject *object) const
{
    return m_objects.indexOf(const_cast<EvObject *>(object));
}

void EvObjectsContainer::clear()
{
    while (count()) {
        removeObject(m_objects.first());
    }
}

bool EvObjectsContainer::deleteRemovedObjects() const
{
    return m_deleteRemovedObjects;
}

bool EvObjectsContainer::addObject(EvObject * object, int index)
{
    if(contains(object))
        return false;
    connect(object,SIGNAL(removed(EvObject*,EvObject*)),this,SLOT(removeObject(EvObject*)));
    if(index != -1)
        m_objects.insert(index,object);
    else
        m_objects <<object;
    Q_EMIT objectAdded(object);
    return true;
}

bool EvObjectsContainer::addObjects(const QList<EvObject *> &list)
{
    bool ok = true;
    for(int i=0;i<list.size();++i){
        ok &= addObject(list[i]);
    }
    return ok;
}

bool EvObjectsContainer::removeObject(EvObject * object)
{
    if(m_deleteRemovedObjects){
        return deleteObject(object);
    }
    else {
        return removeObjectFromList(object);
    }
}

bool EvObjectsContainer::deleteObject(EvObject * object)
{
    if(removeObjectFromList(object)){
        object->deleteLater();
        return true;
    }
    return false;
}

void EvObjectsContainer::setDeleteRemovedObjects(bool arg)
{
    m_deleteRemovedObjects = arg;
}

bool EvObjectsContainer::removeObjectFromList(EvObject * object)
{
    if(m_objects.removeOne(object)){
        disconnect(object,SIGNAL(removed(EvObject*,EvObject*)),this,SLOT(removeObject(EvObject*)));
        Q_EMIT objectRemoved(object);
        if(m_objects.isEmpty()){
            Q_EMIT cleared();
        }
        return true;
    }
    return false;
}
