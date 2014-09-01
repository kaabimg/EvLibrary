
#include <QApplication>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMenu>
#include <QTextEdit>


#include "EvQmlEngine.h"
#include "EvSystem.h"

#include "EvCoreTypes.h"
#include "EvVariationTypes.h"
#include "EvCircuitTypes.h"
#include "EvSessionTypes.h"
#include "EvSimulationTypes.h"


#include "EvApplication.h"
#include "EvMainWindow.h"
#include "EvPluginsManager.h"
#include "EvPropertiesTreeView.h"
#include "EvPropertiesListView.h"


#include "src/plugins/create/EvCreateProjectViewPlugin.h"
#include "src/plugins/edit/EvEditProjectsViewPlugin.h"
#include "src/plugins/simulate/EvSimulationsViewPlugin.h"
#include "src/plugins/help/EvHelpViewPlugin.h"
#include "src/plugins/messagesview/EvMessagesViewPlugin.h"
#include "src/plugins/log/EvLogViewPlugin.h"
#include "src/plugins/find/EvFindPlugin.h"
#include "src/plugins/actionshistory/EvActionsHistoryPlugin.h"


#include "EvMessageDialog.h"

#include "EvObjectQmlExporter.h"
#include <QClipboard>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EvCoreModule::registerTypes();
    EvVariationModule::registerTypes();
    EvCircuitModule::registerTypes();
    EvSimulationModule::registerTypes();
    EvSessionModule::registerTypes();

    EvApplication app;


    app.pluginsManager()->addPlugin(new EvCreateProjectViewPlugin);
    app.pluginsManager()->addPlugin(new EvEditProjectsViewPlugin);
    app.pluginsManager()->addPlugin(new EvSimulationsViewPlugin);
    app.pluginsManager()->addPlugin(new EvHelpViewPlugin);
    app.pluginsManager()->addPlugin(new EvMessagesViewPlugin);
    app.pluginsManager()->addPlugin(new EvLogViewPlugin);
    app.pluginsManager()->addPlugin(new EvFindPlugin);
    app.pluginsManager()->addPlugin(new EvActionsHistoryPlugin);


    app.loadPlugins();
    app.create();


    EvQmlEngine engine;
    engine.setGlobalObject("system",new EvSystem);


    EvProject  * project = engine.create<EvProject>("/home/ghaith/development/workspace/EzVerif/EzVerif/qml/IProject.qml");

    if(project)
        evApp->currentSession()->add<EvProject>(project);
    else
        qDebug()<<engine.errorString();


    EvMainWindow mainWindow;
    mainWindow.resize(1000,600);
    mainWindow.show();


    EvProperty  * card = engine.create<EvProperty>("/home/ghaith/development/workspace/EzVerif/EzVerif/qml/Card.qml");

    QVariant netlisting;

    QMetaObject::invokeMethod(card,"netlist",Q_RETURN_ARG(QVariant,netlisting));


    qDebug()<<netlisting.toString();


    EvPropertiesListView * pe = new EvPropertiesListView(card);
    EvWidget *  pane =new EvWidget;
    pane->setWindowTitle("Card");
    pane->setContent(pe);
    mainWindow.addWidget(pane);

    int ret = a.exec();

    a.clipboard()->clear();

    return ret;
}
