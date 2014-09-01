#include "EvWidget.h"

#include <QAction>
#include <QPainter>
#include <QShowEvent>
#include <QVBoxLayout>

#include "EvToolBar.h"
#include "EvSystem.h"
#include "EvMainWindow.h"
#include "EvHideShowSideBarWidget.h"
#include "EvAppSettings.h"

#include <QUndoStack>


EvWidget::EvWidget(QWidget *parent) :
    QWidget(parent),
    m_parentEvWidget(NULL),m_object(NULL),m_isProcessing(false)
{    
    initialize();
}

EvWidget::EvWidget(EvObject * object, QWidget *parent):
    QWidget(parent),
    m_parentEvWidget(NULL),
    m_object(object),
    m_isProcessing(false)
{
    initialize();
}


void EvWidget::initialize()
{
    setEnabled(true);
    setActiveOnShow(true);
    setSupportsRename(false);
    setBehaviorFlags(NoBehaviorFlags);

    m_commandsInterface =new EvCommandsInterface(this);
    m_clipboardInterface = new EvClipboardInterface(this);

    createClipboardActions();
    createUndoRedoActions();
    updateClipboardActions();
}


EvObject *EvWidget::evObject() const
{
    return m_object;
}



void EvWidget::setEvObject(EvObject *arg)
{
    if (m_object != arg) {
        if(m_object){
            disconnect(m_object,SIGNAL(destroyed()),this,SIGNAL(controlledObjectDeleted()));
        }
        m_object = arg;
        connect(m_object,SIGNAL(destroyed()),this,SIGNAL(controlledObjectDeleted()));
        Q_EMIT objectChanged(arg);
    }
}



void EvWidget::setIsProcessing(bool arg)
{
    if (m_isProcessing != arg) {
        m_isProcessing = arg;
        Q_EMIT isProcessingChanged(arg);
    }
}


void EvWidget::setSupportsRename(bool arg)
{
    m_supportsRename = arg;
}


void EvWidget::updateClipboardActions()
{
   m_clipboardActions[0]->setEnabled(m_clipboardInterface->canCopy());
   m_clipboardActions[1]->setEnabled(m_clipboardInterface->canCopy());
}

void EvWidget::setContent(QWidget * widget)
{
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(widget);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    widget->setParent(this);
}



void EvWidget::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if(m_setActiveOnShow){
        setAsActiveWidget();
    }
    if(m_behaviorFlags.testFlag(HasSideBarInteractions)){
        evMainWindow->hideShowSizeBarWidget()->setMaximizeAvailable(
                    m_behaviorFlags.testFlag(HasShowSideBarFeature)
                    );
        evMainWindow->hideShowSizeBarWidget()->setMinimizeAvailable(
                    m_behaviorFlags.testFlag(HasHideSideBarFeature)
                    );
    }

}

void EvWidget::createClipboardActions()
{
    m_clipboardActions << createAction(
                              evIconsFactory->applicationIcon(
                                  EvIconsFactory::Copy,EvIconsFactory::Colored),
                              "Copy",
                              SLOT(copy())
                              );
    m_clipboardActions.last()->setShortcut(Qt::CTRL + Qt::Key_C);

    m_clipboardActions << createAction(
                              evIconsFactory->applicationIcon(
                                  EvIconsFactory::Cut,EvIconsFactory::Colored),
                              "Cut",
                              SLOT(cut())
                              );

    m_clipboardActions.last()->setShortcut(Qt::CTRL + Qt::Key_X);

    m_clipboardActions << createAction(
                              evIconsFactory->applicationIcon(
                                  EvIconsFactory::Paste,EvIconsFactory::Colored),
                              "Paste",
                              SLOT(paste())
                              );

    m_clipboardActions.last()->setShortcut(Qt::CTRL + Qt::Key_V);

    connect(m_clipboardInterface,SIGNAL(selectionChanged()),this,SLOT(updateClipboardActions()));
}

void EvWidget::createUndoRedoActions()
{
    m_undoRedoActions << m_commandsInterface->commandsStack()->createUndoAction(this);
    m_undoRedoActions.last()->setIcon(
                evIconsFactory->applicationIcon(
                    EvIconsFactory::Undo,EvIconsFactory::Colored)
                );
    m_undoRedoActions.last()->setShortcut(Qt::CTRL + Qt::Key_Z);

    m_undoRedoActions << m_commandsInterface->commandsStack()->createRedoAction(this);
    m_undoRedoActions.last()->setIcon(
                evIconsFactory->applicationIcon(
                    EvIconsFactory::Redo,EvIconsFactory::Colored)
                );
    m_undoRedoActions.last()->setShortcut(Qt::CTRL +Qt::SHIFT + Qt::Key_Z);
}


EvCommandsInterface *EvWidget::commandsInterface() const
{
    return m_commandsInterface;
}

EvClipboardInterface *EvWidget::clipboardInterface() const
{
    return m_clipboardInterface;
}

void EvWidget::setAsActiveWidget()
{
    evMainWindow->setActiveWidget(this);
}

bool EvWidget::isProcessing() const
{
    return m_isProcessing;
}

QList<QAction *> EvWidget::clipboardActions() const
{
    return m_clipboardActions;
}

void EvWidget::setCopyEnabled(bool  arg)
{
    m_clipboardActions[0]->setEnabled(arg);
}

void EvWidget::setCutEnabled(bool arg)
{
    m_clipboardActions[1]->setEnabled(arg);
}

void EvWidget::setPasteEnabled(bool arg)
{
    m_clipboardActions[2]->setEnabled(arg);
}

QList<QAction *> EvWidget::undoRedoActions() const
{
    return m_undoRedoActions;
}

int EvWidget::childrenWidgetsCount() const{return 0;}



bool EvWidget::showObject(EvObject *)
{
    return false;
}

void EvWidget::copy()
{
    clipboardInterface()->copy();
}

void EvWidget::cut()
{
    clipboardInterface()->cut();
}

void EvWidget::paste(){}


EvWidget *EvWidget::parentEvWidget() const
{
    return m_parentEvWidget;
}

void EvWidget::setParentEvWidget(EvWidget * widget)
{
    m_parentEvWidget = widget;
}




QAction *EvWidget::createAction(const QIcon & icon, const QString &text, const char *member)
{
    QAction * action = new QAction(icon,text,this);
    connect(action,SIGNAL(triggered(bool)),this,member);
    return action;
}

QAction *EvWidget::createAction(const QIcon & icon, const QString &text, QObject *object, const char *member)
{
    QAction * action = new QAction(icon,text,this);
    connect(action,SIGNAL(triggered(bool)),object,member);
    return action;
}

QAction *EvWidget::createSeparator()
{
     QAction * action = new QAction(this);
     action->setSeparator(true);
     return action;
}



bool EvWidget::enabled() const
{
    return m_enabled;
}

void EvWidget::setEnabled(bool arg)
{
    if (m_enabled != arg) {
        m_enabled = arg;
        Q_EMIT enabledChanged(arg);
    }
}

void EvWidget::setActiveOnShow(bool arg)
{
    m_setActiveOnShow = arg;
}

bool EvWidget::activeOnShow() const
{
    return m_setActiveOnShow;
}



bool EvWidget::supportsRename() const
{
    return m_supportsRename;
}

void EvWidget::rename(const QString & ){}


