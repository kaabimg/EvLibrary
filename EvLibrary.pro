#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T08:31:02
#
#-------------------------------------------------

QT       += core widgets qml multimedia multimediawidgets webkitwidgets

TARGET = EvLibrary
TEMPLATE = app


OTHER_FILES += \
    qml/IProcess.qml \
    qml/Card.qml \
    qml/IProject.qml \
    LICENSE.txt

RESOURCES += \
    icons.qrc \
    styles.qrc

HEADERS += \
    src/application/core/base/EvApplication.h \
    src/application/core/base/EvApplicationArgumentsManager.h \
    src/application/core/base/EvChildrenContainer.h \
    src/application/core/base/EvEnvironment.h \
    src/application/core/base/EvGlobal.h \
    src/application/core/base/EvMacros.h \
    src/application/core/base/EvObject.h \
    src/application/core/base/EvObjectsManagement.h \
    src/application/core/base/EvProperty.h \
    src/application/core/io/EvMessagesManager.h \
    src/application/core/io/EvQmlEngine.h \
    src/application/core/io/EvSystem.h \
    src/application/core/plugins/EvPlugin.h \
    src/application/core/scripting/EvApplicationScriptingInterface.h \
    src/application/core/settings/EvApparenceSettings.h \
    src/application/core/settings/EvApplicationSettings.h \
    src/application/core/settings/EvAppSettings.h \
    src/application/core/settings/EvIconsfactory.h \
    src/application/core/settings/EvSettings.h \
    src/application/core/threading/EvJob.h \
    src/application/core/threading/EvJobsManager.h \
    src/application/gui/mainwindow/EvMainWindow.h \
    src/application/gui/mainwindow/EvMainWindowIOBar.h \
    src/application/gui/models/EvObjectPropertiesModel.h \
    src/application/gui/propertyeditor/EvBoolDelegate.h \
    src/application/gui/propertyeditor/EvColorDelegate.h \
    src/application/gui/propertyeditor/EvDirectoryDelegate.h \
    src/application/gui/propertyeditor/EvDoubleDelegate.h \
    src/application/gui/propertyeditor/EvEditWidget.h \
    src/application/gui/propertyeditor/EvEnumDelegate.h \
    src/application/gui/propertyeditor/EvFileDelegate.h \
    src/application/gui/propertyeditor/EvFontDelegate.h \
    src/application/gui/propertyeditor/EvIntDelegate.h \
    src/application/gui/propertyeditor/EvPropertiesListModel.h \
    src/application/gui/propertyeditor/EvPropertiesListView.h \
    src/application/gui/propertyeditor/EvPropertyAbstractDelegate.h \
    src/application/gui/propertyeditor/EvPropertyEditorDelegateManager.h \
    src/application/gui/propertyeditor/EvStringDelegate.h \
    src/application/gui/qmleditor/EvQmlEditor.h \
    src/application/gui/qmleditor/EvQmlSyntaxHighlighter.h \
    src/application/gui/widgets/iopane/EvIOPane.h \
    src/application/gui/widgets/iopane/EvIOPaneContainer.h \
    src/application/gui/widgets/tab/EvScrollTabBar.h \
    src/application/gui/widgets/tab/EvTabBar.h \
    src/application/gui/widgets/tab/EvTabElement.h \
    src/application/gui/widgets/tab/EvTabWidget.h \
    src/application/gui/widgets/toolbar/EvToolBar.h \
    src/application/gui/utils/EvGuiUtils.h \
    src/application/gui/widgets/evwidget/EvWidget.h \
    src/ezverif/data/circuit/EvCell.h \
    src/ezverif/data/circuit/EvSchematic.h \
    src/ezverif/data/circuit/EvState.h \
    src/ezverif/data/project/EvProject.h \
    src/ezverif/data/project/EvSession.h \
    src/ezverif/data/variation/EvCorner.h \
    src/ezverif/data/variation/EvDeviceFamily.h \
    src/ezverif/data/variation/EvFilter.h \
    src/ezverif/data/variation/EvLibrary.h \
    src/ezverif/data/variation/EvMismatch.h \
    src/ezverif/data/variation/EvParameter.h \
    src/ezverif/data/variation/EvProcess.h \
    src/ezverif/data/variation/EvSimulationPlan.h \
    src/ezverif/interfaces/simulation/EvSimulationManager.h \
    src/ezverif/interfaces/simulation/EvSimulator.h \
    src/ezverif/interfaces/spice/EvNetlister.h \
    src/plugins/create/EvCreateProjectView.h \
    src/plugins/edit/views/EvCellView.h \
    src/plugins/edit/views/EvEditProjectView.h \
    src/plugins/edit/views/EvSchematicView.h \
    src/plugins/edit/views/EvStateView.h \
    src/plugins/edit/EvEditView.h \
    src/plugins/help/EvHelpView.h \
    src/plugins/simulate/EvSimulateView.h \
    src/types/EvCircuitTypes.h \
    src/types/EvCoreTypes.h \
    src/types/EvObjectsTypes.h \
    src/types/EvSessionTypes.h \
    src/types/EvVariationTypes.h \
    src/plugins/messagesview/EvMessagesView.h \
    src/application/gui/widgets/splitter/EvSplitter.h \
    src/application/gui/widgets/splitter/EvSplitterHandle.h \
    src/application/core/utils/EvSpiceNumber.h \
    src/application/core/utils/EvVariantUtils.h \
    src/application/core/base/EvBinding.h \
    src/application/core/base/EvPropertyBinding.h \
    src/application/gui/propertyeditor/EvSpiceNumberDelegate.h \
    src/application/gui/widgets/buttons/EvButton.h \
    src/application/gui/widgets/buttons/EvToolButton.h \
    src/application/core/plugins/EvPluginsManager.h \
    src/application/core/io/EvUserInteractionsInterface.h \
    src/plugins/edit/EvEditProjectsViewPlugin.h \
    src/plugins/help/EvHelpViewPlugin.h \
    src/plugins/messagesview/EvMessagesViewPlugin.h \
    src/plugins/simulate/EvSimulationsViewPlugin.h \
    src/plugins/create/EvCreateProjectViewPlugin.h \
    src/plugins/find/EvFindPlugin.h \
    src/plugins/find/EvFindWidget.h \
    src/application/gui/mainwindow/EvHideShowSideBarWidget.h \
    src/application/core/base/EvObjectsContainer.h \
    src/plugins/log/EvLogView.h \
    src/plugins/log/EvLogViewPlugin.h \
    src/application/gui/commands/EvSetPropertyCommand.h \
    src/application/gui/commands/EvRemoveCommand.h \
    src/application/core/utils/EvTextFileHandler.h \
    src/plugins/find/EvFindLineEdit.h \
    src/plugins/find/EvFindObjectsList.h \
    src/application/core/base/EvObjectsFinder.h \
    src/application/gui/models/EvObjectsListModel.h \
    src/application/gui/models/EvObjectsListView.h \
    src/application/gui/models/EvObjectModelPainter.h \
    src/application/gui/models/EvObjectDelegate.h \
    src/application/gui/models/EvObjectsTreeView.h \
    src/application/gui/models/EvObjectsTreeModel.h \
    src/application/gui/widgets/tab/EvObjectsTreeTabWidget.h \
    src/application/gui/widgets/evwidget/EvMimeData.h \
    src/application/gui/commands/EvCommand.h \
    src/application/gui/widgets/evwidget/EvWidgetFlagsInterface.h \
    src/application/core/base/EvObjectInfo.h \
    src/application/gui/widgets/evwidget/EvObjectsPasteManager.h \
    src/ezverif/data/variation/EvParameterValueParser.h \
    src/plugins/edit/views/EvProcessView.h \
    src/application/core/base/EvObjectLink.h \
    src/plugins/edit/views/EvLibrariesView.h \
    src/plugins/edit/views/EvParametersView.h \
    src/plugins/edit/views/EvFiltersView.h \
    src/ezverif/data/simulation/EvSimulation.h \
    src/ezverif/data/simulation/EvScenario.h \
    src/types/EvSimulationTypes.h \
    src/plugins/simulate/views/EvSimulationView.h \
    src/ezverif/data/simulation/EvSimulationRun.h \
    src/application/gui/widgets/dialogs/EvDialog.h \
    src/application/gui/widgets/dialogs/EvMessageDialog.h \
    src/application/gui/commands/EvCommands.h \
    src/application/core/base/EvObjectsRemoveRestore.h \
    src/application/core/base/EvApplicationObjects.h \
    src/plugins/edit/models/EvParametersModel.h \
    src/application/gui/commands/EvCommandsInterface.h \
    src/application/gui/commands/EvAddObjectCommand.h \
    src/application/gui/widgets/evwidget/EvClipboardInterface.h \
    src/plugins/actionshistory/EvActionsHistoryPlugin.h \
    src/plugins/actionshistory/EvActionsHistoryView.h \
    src/plugins/edit/models/EvParameterValueDelegate.h \
    src/application/core/io/EvObjectQmlExporter.h \
    src/application/core/io/EvObjectAbstractExporter.h \
    src/application/core/documentation/EvDocumentation.h \
    src/application/core/documentation/EvApplicationDocumentation.h \
    src/plugins/help/EvVideoPlayer.h \
    src/application/gui/propertyeditor/EvPropertiesTreeModel.h \
    src/application/gui/propertyeditor/EvPropertiesTreeView.h

SOURCES += \
    src/application/core/base/EvApplication.cpp \
    src/application/core/base/EvApplicationArgumentsManager.cpp \
    src/application/core/base/EvChildrenContainer.cpp \
    src/application/core/base/EvEnvironment.cpp \
    src/application/core/base/EvObject.cpp \
    src/application/core/base/EvObjectsManagement.cpp \
    src/application/core/base/EvProperty.cpp \
    src/application/core/io/EvMessagesManager.cpp \
    src/application/core/io/EvQmlEngine.cpp \
    src/application/core/io/EvSystem.cpp \
    src/application/core/plugins/EvPluginsManager.cpp \
    src/application/core/scripting/EvApplicationScriptingInterface.cpp \
    src/application/core/settings/EvApparenceSettings.cpp \
    src/application/core/settings/EvApplicationSettings.cpp \
    src/application/core/settings/EvIconsfactory.cpp \
    src/application/core/settings/EvSettings.cpp \
    src/application/core/threading/EvJob.cpp \
    src/application/core/threading/EvJobsManager.cpp \
    src/application/gui/mainwindow/EvMainWindow.cpp \
    src/application/gui/mainwindow/EvMainWindowIOBar.cpp \
    src/application/gui/models/EvObjectPropertiesModel.cpp \
    src/application/gui/propertyeditor/EvBoolDelegate.cpp \
    src/application/gui/propertyeditor/EvColorDelegate.cpp \
    src/application/gui/propertyeditor/EvDirectoryDelegate.cpp \
    src/application/gui/propertyeditor/EvDoubleDelegate.cpp \
    src/application/gui/propertyeditor/EvEditWidget.cpp \
    src/application/gui/propertyeditor/EvEnumDelegate.cpp \
    src/application/gui/propertyeditor/EvFileDelegate.cpp \
    src/application/gui/propertyeditor/EvFontDelegate.cpp \
    src/application/gui/propertyeditor/EvIntDelegate.cpp \
    src/application/gui/propertyeditor/EvPropertiesListModel.cpp \
    src/application/gui/propertyeditor/EvPropertiesListView.cpp \
    src/application/gui/propertyeditor/EvPropertyEditorDelegateManager.cpp \
    src/application/gui/propertyeditor/EvStringDelegate.cpp \
    src/application/gui/qmleditor/EvQmlEditor.cpp \
    src/application/gui/qmleditor/EvQmlSyntaxHighlighter.cpp \
    src/application/gui/widgets/iopane/EvIOPane.cpp \
    src/application/gui/widgets/iopane/EvIOPaneContainer.cpp \
    src/application/gui/widgets/tab/EvScrollTabBar.cpp \
    src/application/gui/widgets/tab/EvTabBar.cpp \
    src/application/gui/widgets/tab/EvTabElement.cpp \
    src/application/gui/widgets/tab/EvTabWidget.cpp \
    src/application/gui/widgets/toolbar/EvToolBar.cpp \
    src/application/gui/utils/EvGuiUtils.cpp \
    src/application/gui/widgets/evwidget/EvWidget.cpp \
    src/ezverif/data/circuit/EvCell.cpp \
    src/ezverif/data/circuit/EvSchematic.cpp \
    src/ezverif/data/circuit/EvState.cpp \
    src/ezverif/data/project/EvProject.cpp \
    src/ezverif/data/project/EvSession.cpp \
    src/ezverif/data/variation/EvCorner.cpp \
    src/ezverif/data/variation/EvDeviceFamily.cpp \
    src/ezverif/data/variation/EvFilter.cpp \
    src/ezverif/data/variation/EvLibrary.cpp \
    src/ezverif/data/variation/EvParameter.cpp \
    src/ezverif/data/variation/EvProcess.cpp \
    src/ezverif/data/variation/EvSimulationPlan.cpp \
    src/ezverif/interfaces/simulation/EvSimulationManager.cpp \
    src/ezverif/interfaces/simulation/EvSimulator.cpp \
    src/ezverif/interfaces/spice/EvNetlister.cpp \
    src/plugins/create/EvCreateProjectView.cpp \
    src/plugins/edit/views/EvEditProjectView.cpp \
    src/plugins/edit/views/EvSchematicView.cpp \
    src/plugins/edit/views/EvStateView.cpp \
    src/plugins/edit/EvEditView.cpp \
    src/plugins/help/EvHelpView.cpp \
    src/plugins/simulate/EvSimulateView.cpp \
    main.cpp \
    src/plugins/messagesview/EvMessagesView.cpp \
    src/application/gui/widgets/splitter/EvSplitter.cpp \
    src/application/gui/widgets/splitter/EvSplitterHandle.cpp \
    src/application/core/utils/EvSpiceNumber.cpp \
    src/application/core/utils/EvVariantUtils.cpp \
    src/application/core/base/EvBinding.cpp \
    src/application/gui/propertyeditor/EvSpiceNumberDelegate.cpp \
    src/application/gui/widgets/buttons/EvButton.cpp \
    src/application/gui/widgets/buttons/EvToolButton.cpp \
    src/application/core/plugins/EvPlugin.cpp \
    src/plugins/find/EvFindWidget.cpp \
    src/application/gui/mainwindow/EvHideShowSideBarWidget.cpp \
    src/application/core/base/EvObjectsContainer.cpp \
    src/plugins/log/EvLogView.cpp \
    src/application/gui/commands/EvSetPropertyCommand.cpp \
    src/application/gui/commands/EvRemoveCommand.cpp \
    src/application/core/utils/EvTextFileHandler.cpp \
    src/plugins/find/EvFindLineEdit.cpp \
    src/plugins/find/EvFindObjectsList.cpp \
    src/application/core/base/EvObjectsFinder.cpp \
    src/application/gui/models/EvObjectsListModel.cpp \
    src/application/gui/models/EvObjectsListView.cpp \
    src/application/gui/models/EvObjectModelPainter.cpp \
    src/application/gui/models/EvObjectDelegate.cpp \
    src/application/gui/models/EvObjectsTreeView.cpp \
    src/application/gui/models/EvObjectsTreeModel.cpp \
    src/application/gui/widgets/tab/EvObjectsTreeTabWidget.cpp \
    src/application/gui/widgets/evwidget/EvMimeData.cpp \
    src/application/gui/commands/EvCommand.cpp \
    src/application/core/base/EvObjectInfo.cpp \
    src/application/gui/widgets/evwidget/EvObjectsPasteManager.cpp \
    src/plugins/edit/views/EvCellView.cpp \
    src/ezverif/data/variation/EvParameterValueParser.cpp \
    src/plugins/edit/views/EvProcessView.cpp \
    src/application/core/base/EvObjectLink.cpp \
    src/plugins/edit/views/EvLibrariesView.cpp \
    src/plugins/edit/views/EvParametersView.cpp \
    src/plugins/edit/views/EvFiltersView.cpp \
    src/ezverif/data/simulation/EvSimulation.cpp \
    src/ezverif/data/simulation/EvScenario.cpp \
    src/plugins/simulate/views/EvSimulationView.cpp \
    src/ezverif/data/simulation/EvSimulationRun.cpp \
    src/application/gui/widgets/dialogs/EvDialog.cpp \
    src/application/gui/widgets/dialogs/EvMessageDialog.cpp \
    src/application/core/base/EvObjectsRemoveRestore.cpp \
    src/application/core/base/EvApplicationObjects.cpp \
    src/plugins/edit/models/EvParametersModel.cpp \
    src/application/gui/commands/EvCommandsInterface.cpp \
    src/application/gui/commands/EvAddObjectCommand.cpp \
    src/application/gui/widgets/evwidget/EvClipboardInterface.cpp \
    src/plugins/actionshistory/EvActionsHistoryView.cpp \
    src/plugins/edit/models/EvParameterValueDelegate.cpp \
    src/application/core/io/EvObjectQmlExporter.cpp \
    src/application/core/documentation/EvDocumentation.cpp \
    src/application/core/documentation/EvApplicationDocumentation.cpp \
    src/plugins/help/EvVideoPlayer.cpp \
    src/application/gui/propertyeditor/EvPropertiesTreeModel.cpp \
    src/application/gui/propertyeditor/EvPropertiesTreeView.cpp


INCLUDEPATH = src
INCLUDEPATH += src/application/core/base/ \
    src/application/core/documentation/ \
    src/application/core/io/ \
    src/application/core/plugins/ \
    src/application/core/scripting/ \
    src/application/core/settings/ \
    src/application/core/threading/ \
    src/application/core/utils/ \
    src/application/gui/mainwindow/ \
    src/application/gui/models/ \
    src/application/gui/propertyeditor/ \
    src/application/gui/qmleditor/ \
    src/application/gui/widgets/iopane/ \
    src/application/gui/widgets/tab/ \
    src/application/gui/widgets/toolbar/ \
    src/application/gui/widgets/evwidget/ \
    src/application/gui/widgets/splitter/ \
    src/application/gui/widgets/dialogs/ \
    src/application/gui/widgets/buttons/ \
    src/application/gui/widgets/evwidget/ \
    src/application/gui/propertyeditor/ \
    src/application/gui/commands/ \
    src/application/gui/utils/ \
    src/ezverif/data/circuit/ \
    src/ezverif/data/project/ \
    src/ezverif/data/variation/ \
    src/ezverif/data/simulation/ \
    src/ezverif/interfaces/simulation/ \
    src/ezverif/interfaces/spice/ \
    src/types/


