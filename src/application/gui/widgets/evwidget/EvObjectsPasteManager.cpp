#include "EvObjectsPasteManager.h"
#include "EvObject.h"
#include "EvObjectsContainer.h"
#include "EvMimeData.h"
#include "EvWidget.h"
#include "EvCommandsInterface.h"

EvObjectsPasteManager::EvObjectsPasteManager(EvWidget *widget):
    m_widget(widget)
{

}

void EvObjectsPasteManager::paste()
{

}

void EvObjectsPasteManager::paste(EvObject *object, EvObject *destination)
{

    if( !Ev::isObjectValid(object)){
        return;
    }
    if( !Ev::isObjectValid(destination)){
        return;
    }
    if(object == destination){
        return;
    }


    if(object->typeId() == destination->typeId()){ // update from
        m_widget->commandsInterface()->updateObject(destination,object);
    }

    if(destination->supportsChildrenType(object->typeId())){ // add a copy
        EvObject * copy = object->copy();
        if(destination == object->parentEvObject()){
            copy->setObjectName("copy_of_"+copy->objectName());
        }
        m_widget->commandsInterface()->addObject(destination,copy);
    }
}

EvCommand *EvObjectsPasteManager::createPasteCommand(EvObject *object, EvObject *destination)
{

}
