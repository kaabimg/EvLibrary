#include "EvEnvironment.h"

EvEnvironment::EvEnvironment(QObject *parent) :
    QObject(parent),m_parentEnv(NULL)
{
}

EvEnvironment::EvEnvironment(EvEnvironment *parentEnv, QObject *parent):
     QObject(parent),m_parentEnv(parentEnv)
{

}

QString EvEnvironment::value(const QString &variable) const
{
    if(m_variables.contains(variable))
        return m_variables.value(variable);

    if(m_parentEnv)
        return m_parentEnv->value(variable);
    return qgetenv(qPrintable(variable));
}

void EvEnvironment::insert(const QString &variable, const QString &value)
{
    m_variables.insert(variable,value);
}
