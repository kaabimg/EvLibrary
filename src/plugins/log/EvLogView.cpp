#include "EvLogView.h"
#include "../../application/core/settings/EvAppSettings.h"


#include<QTextEdit>

EvLogView::EvLogView(QWidget *parent) :
    EvIOPane(parent)
{
    setWindowTitle("Log");
    setProperty("index",1);
    m_logText = new QTextEdit(this);

    connect(evApp->messagesManager(),SIGNAL(newMessage(EvMessagesManager::Message)),
            this,SLOT(addMessage(EvMessagesManager::Message)));

    foreach (const EvMessagesManager::Message & message , evApp->messagesManager()->messages()) {
        addMessage(message);
    }

    m_logText->setReadOnly(true);
    setContent(m_logText);


    QAction * action = createAction(
                evIconsFactory->applicationIcon(EvIconsFactory::Clear,EvIconsFactory::Light),
                "Clear",
                SLOT(clear()));

    addAction(action);
}

void EvLogView::addMessage(const EvMessagesManager::Message & message)
{

    switch (message.type) {
    case EvMessagesManager::Information:
        m_logText->setTextColor("#0a16fe");
        break;
    case EvMessagesManager::Warning:
        m_logText->setTextColor("#ff6600");
        break;
    case EvMessagesManager::Error:
        m_logText->setTextColor("#CC4747");
        break;
    case EvMessagesManager::Log:
        m_logText->setTextColor(Qt::black);
        break;
    default:
        break;
    }

    m_logText->append("[ "+message.time.toString()+ " | "+message.sender+ " ] "+message.content);
}

void EvLogView::clear()
{
    m_logText->clear();
}


