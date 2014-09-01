#include "EvSystem.h"
#include "EvApplication.h"
#include "EvMessagesManager.h"
#include "EvObject.h"
#include "EvVariantUtils.h"

EvSystem::EvSystem(const QString &name, QObject * parent):
    QObject(parent),
    m_name(name)
{
    connect(this,
            SIGNAL(log(QString,QString)),
            evApp->messagesManager(),
            SLOT(addLog(QString,QString)));
    connect(this,
            SIGNAL(info(QString,QString,bool)),
            evApp->messagesManager(),
            SLOT(addInformation(QString,QString,bool)));
    connect(this,
            SIGNAL(warn(QString,QString,bool)),
            evApp->messagesManager(),
            SLOT(addWarning(QString,QString,bool)));
    connect(this,
            SIGNAL(error(QString,QString,bool)),
            evApp->messagesManager(),
            SLOT(addError(QString,QString,bool)));

}

void EvSystem::info(const QString & msg)
{
    Q_EMIT info(m_name,msg,false);
}

void EvSystem::warn(const QString & msg)
{
    Q_EMIT warn(m_name,msg,false);
}

void EvSystem::error(const QString & msg)
{
    Q_EMIT error(m_name,msg,false);
}

void EvSystem::importantInfo(const QString & msg)
{
    Q_EMIT info(m_name,msg,true);

}

void EvSystem::importantWarning(const QString & msg)
{
    Q_EMIT warn(m_name,msg,true);

}

void EvSystem::importantError(const QString & msg)
{
    Q_EMIT error(m_name,msg,true);

}

bool EvSystem::question(const QString & question)
{
    bool reply;

    QMetaObject::invokeMethod(
                evApp->messagesManager(),
                "yesNoQuestion",
                Q_RETURN_ARG(bool,reply),
                Q_ARG(QString,m_name),
                Q_ARG(QString,question)
                );

    return reply;
}

void EvSystem::log(const QString & msg)
{
    Q_EMIT log(m_name,msg);
}

QString EvSystem::env(const QString & name) const
{
    return qgetenv(qPrintable(name));
}


EvSystem::Message &EvSystem::Message::operator <<(const char *data)
{
    text.append(data);
    return *this;
}

EvSystem::Message &EvSystem::Message::operator <<(const QByteArray &data)
{
    text.append(data);
    return *this;
}


EvSystem::Message &EvSystem::Message::operator <<(const QString &data){
    text.append("\'"+data+"\'");
    return *this;
}


EvSystem::Message &EvSystem::Message::operator <<(int data){
    text.append(QString::number(data));
    return *this;
}


EvSystem::Message &EvSystem::Message::operator <<(double data){
    text.append(QString::number(data));
    return *this;
}





EvSystem::Message &EvSystem::Message::operator <<(const QDateTime &data){
    text.append(data.toString());
    return *this;
}


EvSystem::Message &EvSystem::Message::operator <<(const QDate &data){
    text.append(data.toString());
    return *this;
}


EvSystem::Message &EvSystem::Message::operator <<(const QTime &data){
    text.append(data.toString());
    return *this;
}

EvSystem::Message &EvSystem::Message::operator <<(const EvVersion &data)
{
    text.append(data);
    return *this;
}

EvSystem::Message &EvSystem::Message::operator <<(const EvObject *object)
{
    text.append(object->typeName());
    text.append("(");
    text.append("'"+object->objectName()+"'");
    text.append(")");
    return *this;

}

EvSystem::Message::operator QString() const{
    return text;
}
