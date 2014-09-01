#include "EvCommandsInterface.h"
#include <QUndoStack>
#include "EvObject.h"
#include "EvAddObjectCommand.h"
#include "EvRemoveCommand.h"
#include "EvSetPropertyCommand.h"


EvCommandsInterface::EvCommandsInterface(QObject *parent) :
    QObject(parent),m_commandsStack(new QUndoStack(this))
{
}

QUndoStack *EvCommandsInterface::commandsStack() const
{
    return m_commandsStack;
}

EvCommand *EvCommandsInterface::createAddObjectCommand(
        EvObject *parentObject,
        int type,
        EvCommand *parent) const
{
    return new EvAddObjectCommand(parentObject,type,parent);
}

EvCommand *EvCommandsInterface::createAddObjectCommand(
        EvObject *parentObject,
        EvObject *object,
        EvCommand *parent) const
{
    return new EvAddObjectCommand(parentObject,object,parent);
}

EvCommand *EvCommandsInterface::createUpdateObjectCommand(EvObject *parent, EvObject *newValue) const
{
    return NULL;
}

EvCommand *EvCommandsInterface::createRemoveObjectCommand(EvObject *object, EvCommand *parent) const
{
    return new EvRemoveCommand(object,parent);
}

EvCommand *EvCommandsInterface::createSetObjectPropertyCommand(
        EvObject *object,
        const QByteArray &propertyName,
        const QVariant &value,
        EvCommand *parent) const
{
    return new EvSetPropertyCommand(
                object,
                propertyName,
                value,
                parent
                );
}

void EvCommandsInterface::addObject(EvObject * parent,int type)
{
    m_commandsStack->push( createAddObjectCommand(parent,type) ) ;
}

void EvCommandsInterface::addObject(EvObject *parent, EvObject *object)
{
    m_commandsStack->push(createAddObjectCommand(parent,object));
}

void EvCommandsInterface::updateObject(EvObject *object, EvObject *newValue)
{
    Q_UNUSED(object);
    Q_UNUSED(newValue);
}

void EvCommandsInterface::removeObject(EvObject * object)
{
    m_commandsStack->push(createRemoveObjectCommand(object) ) ;
}

void EvCommandsInterface::setObjectProperty(
        EvObject *object,
        const QByteArray &propertyName,
        const QVariant &value)
{
    m_commandsStack->push(createSetObjectPropertyCommand(
                              object,
                              propertyName,
                              value
                              ));
}


