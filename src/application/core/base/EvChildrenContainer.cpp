#include "EvChildrenContainer.h"

#include "EvObject.h"
#include "EvObjectsManagement.h"

/*

EvChildrenContainer::EvChildrenContainer(EvObject *obj, int type):
    mode(Container),object(obj),objectsType(type)
{

}

int EvChildrenContainer::supportedType() const {return objectsType;}

int EvChildrenContainer::size() const {return objects.size();}

int EvChildrenContainer::indexOf(const EvObject *obj) const
{
    return objects.indexOf(const_cast<EvObject *>(obj));
}

EvObject *EvChildrenContainer::childAt(int i) const
{
    return objects.at(i);
}

void EvChildrenContainer::add(EvObject *obj)
{
    Q_ASSERT(obj);
    if(mode == Property)
        clear();

    objects.append(obj);
}

void EvChildrenContainer::remove(EvObject *obj)
{
    objects.removeOne(obj);
}

void EvChildrenContainer::clear()
{
    while (size()) {
        remove(childAt(0));
    }
}

QString EvChildrenContainer::generateDefautObjectName() const
{
    QString name = EvObjectsManagement::typeName(this->objectsType);
    name = name.toLower()+"_";
    int index = 1;
    while(containsName(name+QString::number(index)))
        index++;
    return name+QString::number(index);
}

bool EvChildrenContainer::containsName(const QString & name) const
{
    for(int i=0;i<objects.size();++i){
        if(objects[i]->name() == name)
            return true;
    }
    return false;
}

void EvChildrenContainer::updateFrom(const EvChildrenContainer *another)
{
    int difference = another->size() - size();
    if(difference > 0){
        for(int i=0;i<difference;++i)
            add(EvObject::createObject(objectsType));
    }
    else if (difference < 0) {
        difference = -difference;
        for(int i=0;i<difference;++i)
            remove(objects.last());
    }

    for(int i = 0;i<size();++i)
        childAt(i)->updateFrom(another->childAt(i));
}

*/
