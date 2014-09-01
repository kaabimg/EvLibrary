#include "EvApplication.h"
#include <QApplication>
#include <QAction>

#include "EvObject.h"
#include "EvApplicationArgumentsManager.h"
#include "EvPluginsManager.h"
#include "EvApplicationSettings.h"
#include "EvIconsfactory.h"
#include "EvMessagesManager.h"
#include "EvJobsManager.h"
#include "EvSystem.h"
#include "EvSession.h"
#include "EvApplicationObjects.h"
#include "EvApplicationDocumentation.h"


struct EvApplicationPrivate {
    static EvApplication * instance;
    EvApplication::Mode mode;
    QStringList pluginsDirectories;
    bool defaultYesNoQuestionReply;
    EvPluginsManager * pluginsManager;
    EvApplicationSettings * settings;
    EvMessagesManager * messagesManager;
    EvJobsManager * jobsManager;
    EvApplicationArgumentsManager * argumentsManager;
    EvApplicationObjects * applicationObjects;
    EvIconsFactory * iconsFactory;
    EvSession * currentSession;
    EvApplicationDocumentation * documentation;

};


EvApplication* EvApplicationPrivate::instance = 0;

EvApplication::EvApplication() :d_ptr (new EvApplicationPrivate)
{
    EvApplicationPrivate::instance = this;

    QCoreApplication::setApplicationName("EvLibrary");
    d_ptr->applicationObjects = new EvApplicationObjects();


    d_ptr->mode = Graphical;
    d_ptr->settings = new EvApplicationSettings();
    d_ptr->messagesManager = new EvMessagesManager(this);
    d_ptr->jobsManager = new EvJobsManager(this);
    d_ptr->argumentsManager = new EvApplicationArgumentsManager();

    d_ptr->argumentsManager->parseArguments(QCoreApplication::instance()->arguments());
    d_ptr->iconsFactory = new EvIconsFactory;
    d_ptr->defaultYesNoQuestionReply = true;
    d_ptr->pluginsManager = new EvPluginsManager;

    d_ptr->currentSession = EvObject::create<EvSession>();
    d_ptr->currentSession->setObjectName("Session");

    d_ptr->documentation = EvObject::create<EvApplicationDocumentation>();
    d_ptr->documentation->setObjectName("Application documentation");


}

EvApplication::~EvApplication()
{   
    delete d_ptr->currentSession ;
    delete d_ptr->pluginsManager;
    delete d_ptr->iconsFactory;
    delete d_ptr->settings;


    // should be removed last after the delete of all
    // evobjects
    delete d_ptr->applicationObjects;
    delete d_ptr;
}

EvApplication::Mode EvApplication::mode() const
{
    return d_ptr->mode;
}


EvApplication *EvApplication::instance()
{
    return EvApplicationPrivate::instance;
}

QStringList EvApplication::pluginsDirectories() const
{
    return d_ptr->pluginsDirectories;

}
void EvApplication::setPluginsDirectories(const QStringList &arg)
{
    d_ptr->pluginsDirectories = arg;
}



EvMessagesManager *EvApplication::messagesManager() const
{
    return d_ptr->messagesManager;
}


EvApplicationSettings *EvApplication::settings() const
{
    return d_ptr->settings;
}

EvJobsManager *EvApplication::jobsManager() const
{
    return d_ptr->jobsManager;
}

EvApplicationArgumentsManager *EvApplication::argumentsManager() const
{
    return d_ptr->argumentsManager;
}

EvIconsFactory *EvApplication::iconsFactory() const
{
    return d_ptr->iconsFactory;
}

EvPluginsManager *EvApplication::pluginsManager() const
{
    return d_ptr->pluginsManager;
}

EvApplicationDocumentation *EvApplication::documentation() const
{
    return d_ptr->documentation;
}



EvApplicationObjects *EvApplication::applicationObjects() const
{
    return d_ptr->applicationObjects;
}

bool EvApplication::isObjectValid(EvObject * object) const
{
    return d_ptr->applicationObjects->isPointerValid(object);
}

EvSession *EvApplication::currentSession() const
{
    return d_ptr->currentSession;
}



bool EvApplication::defaultYesNoQuestionReply() const
{
    return d_ptr->defaultYesNoQuestionReply;
}





void EvApplication::setDefaultYesNoQuestionReply(bool arg)
{
    if (d_ptr->defaultYesNoQuestionReply != arg) {
        d_ptr->defaultYesNoQuestionReply = arg;
        Q_EMIT defaultYesNoQuestionReplyChanged(arg);
    }
}




void EvApplication::loadPlugins()
{
    foreach (const QString & directory, pluginsDirectories()) {
        pluginsManager()->loadPluginsFromDirectory(directory);

    }
    pluginsManager()->terminatePluginsCreation();
}

void EvApplication::loadPluginsFromDirectory(const QString &directory)
{
    pluginsManager()->loadPluginsFromDirectory(directory);
}

void EvApplication::loadPluginsFromLibrary(const QString &path)
{
    pluginsManager()->loadPluginsFromLibrary(path);
    pluginsManager()->terminatePluginsCreation();
}




void EvApplication::handleArguments()
{
    if(d_ptr->argumentsManager->containsOption("-nogui")){
       d_ptr->mode = Batch;
   }


   if(d_ptr->argumentsManager->containsOption("-batch")){
       d_ptr->mode = Batch;
   }

   if(d_ptr->argumentsManager->containsOption("-plugins-directory")){
       QStringList paths = d_ptr->argumentsManager->optionArguments("-plugins-directories");
       d_ptr->pluginsDirectories += paths;
   }


   if(d_ptr->argumentsManager->containsOption("-script")){
       QStringList scripts = d_ptr->argumentsManager->optionArguments("-script");
       foreach (const QString & script , scripts) {
            runScript(script);
       }
   }
}

void EvApplication::runScript(const QString &)
{

}

void EvApplication::create()
{
    handleArguments();
}


