#include "EvMessagesView.h"
#include "../../application/core/base/EvApplication.h"
#include "../../application/core/settings/EvIconsfactory.h"

#include <QAction>
#include <QShowEvent>
#include <QTableWidget>
#include <QHeaderView>

EvMessagesView::EvMessagesView(QWidget *parent) :
    EvIOPane(parent),m_resized(false)
{
    setWindowTitle("Messages");
    setProperty("index",0);

    m_clearAction = createAction(
                evApp->iconsFactory()->applicationIcon(EvIconsFactory::Clear,EvIconsFactory::Light),
                "Clear",
                SLOT(clear())
                );

    addAction(m_clearAction);


    m_messagesList = new QTableWidget(this);
    setContent(m_messagesList);

    QStringList headers;
    headers<<"Type"<<"Date"<<"Sender"<<"Message";
    m_messagesList->setColumnCount(4);
    m_messagesList->setHorizontalHeaderLabels(headers);
    m_messagesList->setSelectionBehavior(QTableWidget::SelectRows);


    foreach (const EvMessagesManager::Message & message , evApp->messagesManager()->messages()) {
        addMessage(message);
    }

    connect(evApp->messagesManager(),SIGNAL(newMessage(EvMessagesManager::Message)),
            this,SLOT(addMessage(EvMessagesManager::Message)));         

    setContentChangedOnInit(m_messagesList->rowCount());
}


void EvMessagesView::addMessage(const EvMessagesManager::Message & message)
{
    if(message.type == EvMessagesManager::Log )
        return;

    int row = m_messagesList->rowCount();
    m_messagesList->setRowCount(row+1);

    QTableWidgetItem * item ;

    item = new QTableWidgetItem();
    switch (message.type) {
    case EvMessagesManager::Information:
        item->setIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Information,EvIconsFactory::Colored));
        item->setText("Inforamtion");
        break;
    case EvMessagesManager::Warning:
        item->setIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Warning,EvIconsFactory::Colored));
        item->setText("Warning");
        break;
    case EvMessagesManager::Error:
        item->setIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Error,EvIconsFactory::Colored));
        item->setText("Error");
        break;
    default:
        break;
    }
    m_messagesList->setItem(row,0,item);
    item->setSelected(true);


    item = new QTableWidgetItem(message.time.toString());
    m_messagesList->setItem(row,1,item);
    item->setSelected(true);

    item = new QTableWidgetItem(message.sender);
    m_messagesList->setItem(row,2,item);
    item->setSelected(true);

    item = new QTableWidgetItem(message.content);
    m_messagesList->setItem(row,3,item);   

    item->setSelected(true);


    Q_EMIT contentChanged();
}

void EvMessagesView::clear()
{
    m_messagesList->clear();
    m_messagesList->setRowCount(0);
    QStringList headers;
    headers<<"Type"<<"Date"<<"Sender"<<"Message";
    m_messagesList->setColumnCount(4);
    m_messagesList->setHorizontalHeaderLabels(headers);
    m_messagesList->setSelectionBehavior(QTableWidget::SelectRows);
}

void EvMessagesView::resizeEvent(QResizeEvent *event)
{
    if(!m_resized){
        int w = event->size().width();

        w -= m_messagesList->verticalHeader()->width();

        m_messagesList->setColumnWidth(0,w * 0.1);
        m_messagesList->setColumnWidth(1,w * 0.1);
        m_messagesList->setColumnWidth(2,w * 0.2);
        m_messagesList->setColumnWidth(3,w * 0.6);
        m_resized = true;
    }

    EvIOPane::resizeEvent(event);
}
