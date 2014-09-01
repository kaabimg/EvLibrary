#include "EvSetPropertyCommand.h"
#include "EvObject.h"

#include "EvSystem.h"

EvSetPropertyCommand::EvSetPropertyCommand(
        EvObject *object,
        const QByteArray &propertyName,
        const QVariant &value,
        EvCommand *parent):
    EvCommand(parent),
    m_object(object),
    m_propetyName(propertyName),
    m_newValue(value)

{
    m_oldValue = object->property(m_propetyName);
    EvSystem::Message text;
    text <<"Set "<< object <<" property "<<propertyName;
    setText(text);
}


bool EvSetPropertyCommand::isValid() const
{
    return Ev::isObjectValid(m_object);
}

void EvSetPropertyCommand::execUndo()
{
    m_object->setProperty(m_propetyName,m_oldValue);
}

void EvSetPropertyCommand::execRedo()
{
    m_object->setProperty(m_propetyName,m_newValue);
}

