#include "EvQmlEngine.h"

#include "EvObject.h"

#include <QQmlContext>

QQmlEngine * EvQmlEngine::engine = 0;

EvQmlEngine::EvQmlEngine():
    m_hasErrors(false){
    if(engine == 0)
        engine = new QQmlEngine;
}

bool EvQmlEngine::hasErrors() const
{
    return m_hasErrors;
}

QString EvQmlEngine::errorString() const
{
    return m_errorStrings;
}

void EvQmlEngine::setGlobalObject(const QString &name, QObject *obj)
{
    m_globalContextObjects[name] = obj;
}

void EvQmlEngine::removeGlobalObject(const QString &name)
{
    m_globalContextObjects.remove(name);
}

void EvQmlEngine::setGlobalProperty(const QString &name, const QVariant &value)
{
    m_globalContextProperties[name] = value;
}

void EvQmlEngine::removeGlobalProperty(const QString &name)
{
    m_globalContextProperties.remove(name);
}

void EvQmlEngine::prepareEngine(QQmlEngine * engine)const
{
    QQmlContext * context = engine->rootContext();
    foreach (const QString & name,m_globalContextObjects.keys()){
        context->setContextProperty(name,m_globalContextObjects[name]);
    }
    foreach (const QString & name,m_globalContextProperties.keys()){
        context->setContextProperty(name,m_globalContextProperties[name]);
    }
}


