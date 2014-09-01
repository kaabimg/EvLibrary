#ifndef EVMESSAGESMANAGER_H
#define EVMESSAGESMANAGER_H

#include <QObject>
#include <QDateTime>

class EvUserInteractionsInterface;

class EvMessagesManager : public QObject
{
    Q_OBJECT

public:

    enum MessageType {
        Log,
        Information,
        ImportantInformation,
        Warning,
        ImportantWarning,
        Error,
        ImportantError,
        Question

    };

    struct Message {
        MessageType type;
        QString sender;
        QString content;
        QTime time;
    };
    explicit EvMessagesManager(QObject *parent = 0);
    QList<Message> messages()const;


    void installUserInteractionsInterface(EvUserInteractionsInterface*);
    void uninstallUserInteractionsInterface();

public Q_SLOTS:
    void addLog(const QString & sender,const QString & content);
    void addInformation(const QString & sender,const QString & content,bool important = false);
    void addWarning(const QString & sender,const QString & content,bool important = false);
    void addError(const QString & sender,const QString & content,bool important = false);

    bool yesNoQuestion(const QString & sender,const QString & content);



Q_SIGNALS:
    void newMessage(EvMessagesManager::Message );

protected:
    void addMessage(const QString & sender,const QString & content,MessageType );

private:
    QList<Message> m_messages;
    EvUserInteractionsInterface * m_userInteractionsInterface;

};
Q_DECLARE_METATYPE(EvMessagesManager::Message)

#endif // EVMESSAGESMANAGER_H
