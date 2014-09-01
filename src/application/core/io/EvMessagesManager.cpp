#include "EvMessagesManager.h"
#include "EvUserInteractionsInterface.h"
#include "EvApplication.h"

EvMessagesManager::EvMessagesManager(QObject *parent) :
    QObject(parent),m_userInteractionsInterface(NULL)
{
}

QList<EvMessagesManager::Message> EvMessagesManager::messages() const
{
    return m_messages;
}

void EvMessagesManager::installUserInteractionsInterface(EvUserInteractionsInterface * interface)
{
    m_userInteractionsInterface = interface;
}

void EvMessagesManager::uninstallUserInteractionsInterface()
{
    installUserInteractionsInterface(NULL);
}


void EvMessagesManager::addMessage(
        const QString &sender,
        const QString &content,
        EvMessagesManager::MessageType type)
{
    Message m;
    m.sender = sender;
    m.content = content;
    m.type = type;
    m.time = QTime::currentTime();
    m_messages<<m;
    Q_EMIT newMessage(m);
}


void EvMessagesManager::addLog(const QString &sender, const QString &content)
{
    addMessage(sender,content,Log);
}

void EvMessagesManager::addInformation(const QString &sender, const QString &content, bool important)
{
    addMessage(sender,content,Information);
    if(important && m_userInteractionsInterface){
        m_userInteractionsInterface->importantInformation(sender,content);
    }
}

void EvMessagesManager::addWarning(const QString &sender, const QString &content, bool important)
{
    addMessage(sender,content,Warning);
    if(important && m_userInteractionsInterface){
        m_userInteractionsInterface->importantWarning(sender,content);
    }
}

void EvMessagesManager::addError(const QString &sender, const QString &content, bool important)
{
    addMessage(sender,content,Error);
    if(important && m_userInteractionsInterface){
        m_userInteractionsInterface->importantError(sender,content);
    }
}

bool EvMessagesManager::yesNoQuestion(const QString &sender, const QString &content)
{
    if(m_userInteractionsInterface){
        return m_userInteractionsInterface->yesNoQuestion(sender,content);
    }

    return evApp->defaultYesNoQuestionReply();
}

