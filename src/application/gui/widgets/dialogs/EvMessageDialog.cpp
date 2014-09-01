#include "EvMessageDialog.h"

#include <QTextEdit>

EvMessageDialog::EvMessageDialog(QWidget *parent) :
    EvDialog(Ok,parent)
{
    m_message = new QTextEdit(this);
    m_message->setReadOnly(true);

    addContent(m_message);

}

EvMessageDialog::EvMessageDialog(EvDialog::Buttons buttons, QWidget *parent):
     EvDialog(buttons,parent)
{
    m_message = new QTextEdit(this);
    m_message->setReadOnly(true);

    addContent(m_message);
}

QString EvMessageDialog::message() const
{
    return m_message->toPlainText();
}

void EvMessageDialog::setMessageType(EvMessageDialog::MessageType arg)
{
    switch (arg) {
    case Information:
        setTitle("Information");
        break;
    case Warning:
        setTitle("Warning");
        break;
    case Error:
        setTitle("Error");
        break;
    case Question:
        setTitle("Question");
        break;
    default:
        break;
    }
}

void EvMessageDialog::setMessage(const QString &arg)
{
    m_message->setHtml(arg);
}

