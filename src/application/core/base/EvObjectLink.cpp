#include "EvObjectLink.h"
#include "EvObject.h"

EvObjectLink::EvObjectLink(EvObject *target, QObject *parent) :   
    EvObject(parent),
    m_target(target)
{
    m_isValid = (m_target != NULL);
    if(m_target){
        connectTarget();
    }
}

EvObject *EvObjectLink::target() const
{
    return m_target;
}

bool EvObjectLink::isValid() const
{
    return m_isValid;
}

EvObject *EvObjectLink::operator ->() const
{
    return m_target;
}

void EvObjectLink::setIsValid(bool arg)
{
    if (m_isValid != arg) {
        m_isValid = arg;
        Q_EMIT isValidChanged(arg);
    }
}

void EvObjectLink::onTargetRemoved()
{
    disconnectTarget();
    m_target = NULL;
    setIsValid(false);
}


void EvObjectLink::connectTarget()
{
    connect(m_target,SIGNAL(removed(EvObject*,EvObject*)),this,SLOT(onTargetRemoved()));
    connect(m_target,SIGNAL(designablePropertiesChanged()),this,SIGNAL(designablePropertiesChanged()));
    setIsValid(true);
}

void EvObjectLink::disconnectTarget()
{
    disconnect(m_target,SIGNAL(removed(EvObject*,EvObject*)),this,SLOT(onTargetRemoved()));
    disconnect(m_target,SIGNAL(designablePropertiesChanged()),this,SIGNAL(designablePropertiesChanged()));
    setIsValid(false);
}



EvObject *EvObjectLink::copy() const
{
    if(m_isValid){
        return new EvObjectLink(m_target);
    }

    return new EvObjectLink(NULL);
}

