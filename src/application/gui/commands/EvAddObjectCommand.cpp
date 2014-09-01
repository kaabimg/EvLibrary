#include "EvAddObjectCommand.h"
#include "EvObject.h"
#include "EvSystem.h"

EvAddObjectCommand::EvAddObjectCommand(EvObject *parentObject, int type, EvCommand *parent) :
    EvCommand(parent),
    m_parent(parentObject),
    m_object(NULL),
    m_type(type),
    m_removed(false)

{
    m_object = EvObject::createObject(type);
    m_object->setObjectName(m_parent->generateDefaultName(m_type));

    EvSystem::Message text;
    text <<"Add "<< m_object <<" to "<<m_parent;
    setText(text);

}

EvAddObjectCommand::EvAddObjectCommand(EvObject *parentObject, EvObject *object, EvCommand *parent):
    EvCommand(parent),
    m_parent(parentObject),
    m_object(object),
    m_type(object->typeId()),
    m_removed(false)
{
    EvSystem::Message text;
    text <<"Add "<< m_object <<" to "<<m_parent;
    setText(text);
}

EvAddObjectCommand::~EvAddObjectCommand()
{
    if(m_removed && Ev::isObjectValid(m_object)){
        m_object->deleteLater();
    }
}

bool EvAddObjectCommand::isValid() const
{
    return Ev::isObjectValid(m_parent) && Ev::isObjectValid(m_object);
}

void EvAddObjectCommand::execRedo()
{
    if(!m_parent->canAdd(m_object)){
        QString name = m_object->objectName();
        name += "_backup";
        m_object->setObjectName(name);

        if(!m_parent->canAdd(m_object)){
            int index= 1;
            name.append('_');
            do{
                m_object->setObjectName(name+QString::number(index));

            }
            while (!m_parent->canAdd(m_object));
        }
        EvSystem::Message text;
        text <<"Add "<< m_object <<" to "<<m_parent;
        setText(text);
    }
    m_parent->addObject(m_object);
    m_removed = false;
}

void EvAddObjectCommand::execUndo()
{
    m_parent->removeObject(m_object);
    m_removed = true;
}
