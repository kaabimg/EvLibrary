#ifndef EVAPPLICATION_H
#define EVAPPLICATION_H

#include <QObject>
#include "EvGlobal.h"

class EvApplicationPrivate;
class EvApplicationSettings;
class EvMessagesManager;
class EvJobsManager;
class EvApplicationArgumentsManager;
class EvIconsFactory ;
class EvSession;
class EvPluginsManager;
class QAction;
class EvObject;
class EvApplicationObjects;
class EvApplicationDocumentation;

#define evApp EvApplication::instance()


class EvApplication : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList pluginsDirectories READ pluginsDirectories WRITE setPluginsDirectories)
    Q_PROPERTY(bool defaultYesNoQuestionReply READ defaultYesNoQuestionReply WRITE setDefaultYesNoQuestionReply NOTIFY defaultYesNoQuestionReplyChanged)

public:

    enum Mode {
        Batch,
        Graphical
    };

    EvApplication();
    ~EvApplication();
    Mode mode()const;

    void create();
    static EvApplication *instance();


    QStringList pluginsDirectories() const;
    void setPluginsDirectories(const QStringList & arg);
    void loadPlugins();
    void loadPluginsFromDirectory(const QString & path);
    void loadPluginsFromLibrary(const QString & path);


    EvApplicationObjects * applicationObjects()const;
    bool isObjectValid(EvObject*)const;

    EvMessagesManager* messagesManager()const;
    EvApplicationSettings* settings()const;
    EvJobsManager* jobsManager()const;
    EvApplicationArgumentsManager* argumentsManager()const;
    EvIconsFactory* iconsFactory()const;
    EvPluginsManager *pluginsManager()const;
    EvApplicationDocumentation * documentation()const;

    EvSession* currentSession()const;

    bool defaultYesNoQuestionReply() const;

public Q_SLOTS:
    void setDefaultYesNoQuestionReply(bool arg);

Q_SIGNALS:
    void defaultYesNoQuestionReplyChanged(bool arg);



protected:
    void handleArguments();
    void runScript(const QString & path);

private:
    EV_PRIVATE(EvApplication)

};

#endif // EVAPPLICATION_H
