#include "EvApplicationObjects.h"
#include "EvObject.h"
EvApplicationObjects::EvApplicationObjects(QObject *parent) :
    QObject(parent)
{
}

void EvApplicationObjects::addObject(EvObject * object)
{
    m_objectsIds.insert(object->objectId(),object);
    m_objects.insert(object);
}

void EvApplicationObjects::removeObject(EvObject * object)
{
    m_objectsIds.remove(object->objectId());
    m_objects.remove(object);
}

EvObject *EvApplicationObjects::object(uint id) const
{
    if(m_objectsIds.contains(id)){
        return m_objectsIds[id];
    }
    return NULL;
}

bool EvApplicationObjects::contains(uint id) const
{
    return m_objectsIds.contains(id);
}

bool EvApplicationObjects::isPointerValid(const EvObject *object) const
{
    return m_objects.contains(const_cast<EvObject*>(object));
}
