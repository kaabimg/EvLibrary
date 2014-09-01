#ifndef EVLOGVIEW_H
#define EVLOGVIEW_H

#include "EvIOPane.h"
#include "EvMessagesManager.h"

class QTextEdit;

class EvLogView : public EvIOPane
{
    Q_OBJECT
public:
    explicit EvLogView(QWidget *parent = 0);

public Q_SLOTS:
    void addMessage(const EvMessagesManager::Message &);
    void clear();

private:
    QTextEdit * m_logText;

};

#endif // EVLOGVIEW_H
