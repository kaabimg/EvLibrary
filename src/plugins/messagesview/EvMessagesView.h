#ifndef EVMESSAGESVIEW_H
#define EVMESSAGESVIEW_H

#include "EvIOPane.h"
#include "EvMessagesManager.h"

class QTableWidget;

class EvMessagesView : public EvIOPane
{
    Q_OBJECT
public:
    explicit EvMessagesView(QWidget *parent = 0);

public Q_SLOTS:
    void addMessage(const EvMessagesManager::Message &message);
    void clear();

protected:
    void resizeEvent(QResizeEvent * event);

private:
    QAction * m_clearAction;
    QTableWidget * m_messagesList;
    bool m_resized;

};

#endif // EVMESSAGESVIEW_H
