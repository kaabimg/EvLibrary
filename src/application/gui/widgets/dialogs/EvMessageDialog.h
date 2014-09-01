#ifndef EVMESSAGEDIALOG_H
#define EVMESSAGEDIALOG_H

#include "EvDialog.h"
class QTextEdit;

class EvMessageDialog : public EvDialog
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage)
public:
    enum MessageType{
        Information,
        Warning,
        Error,
        Question
    };
    explicit EvMessageDialog(QWidget *parent = 0);
    explicit EvMessageDialog(Buttons buttons,QWidget *parent = 0);


    QString message() const;
    void setMessageType(MessageType arg);

public Q_SLOTS:
    void setMessage(const QString & arg);

private:
    QTextEdit * m_message;
};

#endif // EVMESSAGEDIALOG_H
