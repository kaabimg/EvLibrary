#include "EvObjectsRemoveRestore.h"
#include "EvObject.h"
#include "EvApplication.h"
#include "EvApplicationObjects.h"




bool Ev::moveObject(EvObject * object,EvObject* newParent)
{
    if(!newParent->canAdd(object)){
        return false;
    }

    EvObject * parent = object->parentEvObject();
    if(parent){
        parent->removeObject(object);
    }
    newParent->addObject(newParent);
    return true;

}



bool Ev::isObjectValid(const EvObject *object)
{
    return evApp->applicationObjects()->isPointerValid(object);
}
