#include "EvRemoveCommand.h"
#include "EvObject.h"
#include "EvSystem.h"

EvRemoveCommand::EvRemoveCommand(EvObject *object, EvCommand *parent) :
    EvCommand(parent),m_object(object)
{
    m_parent = object->parentEvObject();
    m_oldIndex = m_parent->indexOf(object->typeId(),object);

    EvSystem::Message text;
    text <<"Remove "<< m_object <<" from "<<m_parent;
    setText(text);

}

EvRemoveCommand::~EvRemoveCommand()
{
    if(m_removed && Ev::isObjectValid(m_object)){
        m_object->deleteLater();
    }
}

bool EvRemoveCommand::isValid() const
{
    return Ev::isObjectValid(m_parent) && Ev::isObjectValid(m_object);
}

void EvRemoveCommand::execUndo()
{
    m_parent->addObject(m_object,m_oldIndex);
    m_removed = false;
}

void EvRemoveCommand::execRedo()
{
    m_parent->removeObject(m_object);
    m_oldIndex = m_parent->indexOf(m_object->typeId(),m_object);
    m_removed = true;
}
