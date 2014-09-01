#include "EvMainWindow.h"

#include <QMenuBar>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QtCore>
#include <QPaintEvent>
#include <QScrollBar>
#include <QApplication>


#include "EvMainWindowIOBar.h"
#include "EvHideShowSideBarWidget.h"

#include "EvTabBar.h"
#include "EvIOPane.h"
#include "EvToolBar.h"

#include "EvIOPaneContainer.h"
#include "EvSplitter.h"
#include "EvMessagesManager.h"

#include "EvAppSettings.h"
#include "EvPluginsManager.h"

#include "EvMessageDialog.h"

struct EvMainWindowPrivate
{
    static EvMainWindow * instance;
    EvTabBar *tabBar;
    QStackedWidget * stackedWidget;
    QScrollArea * scrollArea;
    EvMainWindowIOBar * ioBar;
    EvToolBar * toolBar;
    EvHideShowSideBarWidget * hideShowSidebarWidget;
    EvWidget* activeWidget;


    QList<EvIOPane*> ioPanes;
    QList<EvWidget*> widgets;
    EvIOPaneContainer * ioPane;
    EvSplitter * splitter;
    int ioPaneHeigth;
    int logoWidth;
    int tabWidth;
    int barHeigth ;

    int temporaryWidgetsHeigth;


};

EvMainWindow* EvMainWindowPrivate::instance = NULL ;

EvMainWindow::EvMainWindow(QWidget *parent)
    : QMainWindow(parent),d_ptr(new EvMainWindowPrivate)
{
    EvMainWindowPrivate::instance = this;

    QFile stylesheet(":/ressources/style/style.qss");
    stylesheet.open(QFile::ReadOnly);

    QString ss = stylesheet.readAll();
    ss = ss.arg(
                evApparenceSettings->darkColor().name(),
                evApparenceSettings->grayColor().name(),
                evApparenceSettings->ligthGraycolor().name(),
                evApparenceSettings->ligthColor().name(),
                evApparenceSettings->primaryColor().name(),
                evApparenceSettings->secondaryColor().name()
                );

    qApp->setStyleSheet(ss);
    stylesheet.close();


    d_ptr->activeWidget = NULL;
    d_ptr->ioPaneHeigth = -1;
    d_ptr->logoWidth = evApparenceSettings->logoSize().width();
    d_ptr->tabWidth = evApparenceSettings->mainTabSize().width();
    d_ptr->barHeigth = evApparenceSettings->mainTabSize().height();
    d_ptr->temporaryWidgetsHeigth = 200;

    QWidget * centralWidget = new QWidget(this);

    QVBoxLayout * centralWidgetLayout = new QVBoxLayout;
    d_ptr->tabBar = new EvTabBar(Qt::Horizontal,centralWidget);

    d_ptr->tabBar->setLogoSize(QSize(d_ptr->logoWidth,d_ptr->barHeigth));
    d_ptr->tabBar->setTabSize(QSize(d_ptr->tabWidth,d_ptr->barHeigth));
    d_ptr->tabBar->setMaximumSize(d_ptr->barHeigth);



    QColor selection = evApparenceSettings->ligthColor();
    selection.setAlpha(100);
    d_ptr->tabBar->setSelectionColor(selection);
    d_ptr->tabBar->setBackgroundColor(evApparenceSettings->primaryColor());
    d_ptr->tabBar->setLogoBackgroundColor(evApparenceSettings->primaryColor().darker());
    d_ptr->tabBar->setLogoText(qAppName());
    d_ptr->tabBar->setTabsFont(evApparenceSettings->font());

    d_ptr->toolBar = new EvToolBar(221,evApparenceSettings->font().pointSize(),centralWidget);
    d_ptr->toolBar->setFixedHeight(40);

    d_ptr->splitter = new EvSplitter(Qt::Vertical);

    d_ptr->ioBar = new EvMainWindowIOBar(centralWidget);
    d_ptr->hideShowSidebarWidget = new EvHideShowSideBarWidget(d_ptr->ioBar);



    d_ptr->scrollArea = new QScrollArea(d_ptr->splitter);
    d_ptr->scrollArea->setFrameShape(QFrame::NoFrame);
    d_ptr->stackedWidget = new QStackedWidget(d_ptr->scrollArea);
    d_ptr->scrollArea->setWidget(d_ptr->stackedWidget);


    d_ptr->ioPane = new EvIOPaneContainer(d_ptr->splitter);

    hideIOPane();

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget( d_ptr->splitter);
    vLayout->addWidget(d_ptr->ioBar);


    centralWidgetLayout->addWidget(d_ptr->toolBar);
    centralWidgetLayout->addWidget(d_ptr->tabBar);
    centralWidgetLayout->addLayout(vLayout);


    centralWidgetLayout->setMargin(0);
    centralWidgetLayout->setContentsMargins(0,0,0,0);
    centralWidgetLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);

    centralWidget->setLayout(centralWidgetLayout);
    setCentralWidget(centralWidget);

    connect(d_ptr->ioBar,SIGNAL(showRequest(EvIOPane*)),this,SLOT(showIOPane(EvIOPane*)));
    connect(d_ptr->ioBar,SIGNAL(hideRequest()),this,SLOT(hideIOPane()));
    connect(d_ptr->tabBar,SIGNAL(showRequest(EvWidget*)),this,SLOT(showWidget(EvWidget*)));
    evApp->messagesManager()->installUserInteractionsInterface(this);


    loadPlugins();

    hideShowSizeBarWidget()->setMaximizeAvailable(false);
    hideShowSizeBarWidget()->setMinimizeAvailable(false);

}

EvMainWindow::~EvMainWindow()
{
    delete d_ptr;
}

EvMainWindow *EvMainWindow::instance()
{
    return EvMainWindowPrivate::instance;
}

int EvMainWindow::logoWidth() const
{
    return d_ptr->logoWidth;
}

int EvMainWindow::tabWidth() const
{
    return d_ptr->tabWidth;
}

EvHideShowSideBarWidget *EvMainWindow::hideShowSizeBarWidget() const
{
    return d_ptr->hideShowSidebarWidget;
}

void EvMainWindow::addIOPane(EvIOPane * pane)
{
    d_ptr->ioPanes.append(pane);
    d_ptr->ioBar->addPane(pane);
    d_ptr->ioPane->showPane(pane);
}



void EvMainWindow::addWidget(EvWidget *widget)
{
    d_ptr->widgets.append(widget);
    d_ptr->tabBar->addTab(widget);
    widget->setParent(d_ptr->stackedWidget);
    showWidget(widget);
    connect(widget,SIGNAL(showRequest(EvWidget*)),this,SLOT(showWidget(EvWidget*)));
    setCurrentWidget(widget);

}

void EvMainWindow::setCurrentIOPane(EvIOPane * pane)
{
    if(d_ptr->ioPanes.contains(pane))
        showIOPane(pane);
}

void EvMainWindow::setLogoWidth(int arg)
{
    if (d_ptr->logoWidth != arg) {
        d_ptr->logoWidth = arg;
        Q_EMIT logoWidthChanged(arg);
    }
}

void EvMainWindow::setTemporaryWidgetsHeigth(int arg)
{
    d_ptr->temporaryWidgetsHeigth = arg;
}

QRect EvMainWindow::temporaryWidgetGeometry(QWidget *ioPaneController)
{
    QRect controllerGeometry = ioPaneController->geometry();
    QRect rect(QPoint (
                controllerGeometry.x(),
                height()-temporaryWidgetsHeigth()-d_ptr->ioPane->height() -2 ),
               QPoint(
                controllerGeometry.x()+controllerGeometry.width(),
                height()-d_ptr->ioPane->height()-2 )
          );
    return rect;
}

void EvMainWindow::showObjectWidget(EvObject *object)
{
    foreach (EvWidget * child, d_ptr->widgets) {
        if(child->showObject(object)){
            return;
        }
    }
}

void EvMainWindow::setActiveWidget(EvWidget *arg)
{
    if (d_ptr->activeWidget != arg) {
        d_ptr->activeWidget = arg;
        d_ptr->toolBar->setCurrentWidget(arg);
        Q_EMIT activeWidgetChanged(arg);
    }
}



void EvMainWindow::addIOBarWidget(QWidget * widget)
{
    d_ptr->ioBar->addWidget(widget);
}


void EvMainWindow::setCurrentWidget(EvWidget * widget)
{
    if(d_ptr->widgets.contains(widget)){
        d_ptr->tabBar->setCurrentTab(widget);
    }
}

void EvMainWindow::showIOPane()
{
    if(d_ptr->ioPaneHeigth == -1)
    {
        d_ptr->ioPaneHeigth = d_ptr->ioPane->preferredSize();
    }
    QList<int> sizes = d_ptr->splitter->sizes();

    if((sizes.size() == 2 && sizes[1] ==0) || sizes.size()==1){
        sizes.clear();
        sizes <<d_ptr->splitter->height()-d_ptr->ioPaneHeigth<<d_ptr->ioPaneHeigth;
    }
    d_ptr->splitter->setSizes(sizes);
}

void EvMainWindow::hideIOPane()
{
    if(d_ptr->ioPaneHeigth != -1){
        d_ptr->ioPaneHeigth = d_ptr->splitter->sizes().at(1);

    }
    QList<int> sizes ;
    sizes <<d_ptr->splitter->height()<<0;
    d_ptr->splitter->setSizes(sizes);
}

void EvMainWindow::showWidget(EvWidget *widget)
{
    int index= d_ptr->stackedWidget->indexOf(widget);
    if(index == -1){
        index = d_ptr->stackedWidget->addWidget(widget);
    }
    d_ptr->stackedWidget->setCurrentIndex(index);
}

void EvMainWindow::showIOPane(EvIOPane * pane)
{
    d_ptr->ioPane->showPane(pane);
    showIOPane();
}

void EvMainWindow::updateStackSize()
{
    QSize size = d_ptr->splitter->size();
    size.setHeight(size.height()-1);//splitter handle
    d_ptr->stackedWidget->setFixedSize(size);
}

void EvMainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    updateStackSize();
    Q_EMIT resized();
}

void EvMainWindow::moveEvent(QMoveEvent * event)
{
    QMainWindow::moveEvent(event);
    Q_EMIT moved();
}

void EvMainWindow::hideEvent(QHideEvent * event)
{
    QMainWindow::hideEvent(event);
    Q_EMIT hidden();
}


void EvMainWindow::importantInformation(const QString &sender, const QString &content)
{
    EvMessageDialog dialog;
    dialog.setSender(sender);
    dialog.setMessageType(EvMessageDialog::Information);
    dialog.setMessage(content);

    customizeDialogAspect(dialog);

    dialog.exec();
}

void EvMainWindow::importantWarning(const QString &sender, const QString &content)
{
    EvMessageDialog dialog;
    dialog.setSender(sender);
    dialog.setMessageType(EvMessageDialog::Warning);
    dialog.setMessage(content);

    customizeDialogAspect(dialog);

    dialog.exec();
}



void EvMainWindow::importantError(const QString &sender, const QString &content)
{
    EvMessageDialog dialog;
    dialog.setSender(sender);
    dialog.setMessageType(EvMessageDialog::Error);
    dialog.setMessage(content);

    customizeDialogAspect(dialog);

    dialog.exec();
}

bool EvMainWindow::yesNoQuestion(const QString &sender, const QString &content)
{
    EvMessageDialog dialog(EvDialog::Yes | EvDialog::No);
    dialog.setSender(sender);
    dialog.setMessageType(EvMessageDialog::Question);
    dialog.setMessage(content);
    customizeDialogAspect(dialog);

    EvDialog::Button result = dialog.exec();
    return (result == EvDialog::Yes);
}


void EvMainWindow::customizeDialogAspect( EvDialog & dialog)
{
    dialog.resize(width()/4,height()/2);
    dialog.move(rect().center()-dialog.rect().center());
}


int EvMainWindow::temporaryWidgetsHeigth() const
{
    return d_ptr->temporaryWidgetsHeigth ;
}

EvWidget *EvMainWindow::activeWidget() const
{
    return d_ptr->activeWidget;
}



/*!
 * If index property is not defined, the widget is inserted at the end
 */

bool EvMainWindow_compareWidgetsIndices(QObject * mv1 , QObject * mv2){
    bool ok;
    int index1 = mv1->property("index").toInt(&ok);
    if(!ok)
        index1 = 100000;

    int index2 = mv2->property("index").toInt(&ok);
    if(!ok)
        index2 = 100000;

    return index1 < index2;
}


void EvMainWindow::loadPlugins()
{
    loadMainViews();
    loadIOPaneItems();
}

void EvMainWindow::loadMainViews()
{
    QList<QObject *> untypedMainViews = evApp->pluginsManager()->latestVersionsOf(EvPluginInfo::MainViewWidget);

    QList<EvWidget*> mainViews;
    for(int i=0;i<untypedMainViews.size();++i){
        mainViews << static_cast<EvWidget*>(untypedMainViews[i]);
    }

    qSort(mainViews.begin(),mainViews.end(),EvMainWindow_compareWidgetsIndices);
    for(int i=0;i<mainViews.size();++i){
        addWidget(mainViews[i]);
    }

    if(mainViews.size()){
        setCurrentWidget(mainViews.first());
    }
}

void EvMainWindow::loadIOPaneItems()
{
    QList<QObject *> items ;
    QWidget * spacer = new QWidget;
    spacer->setFixedWidth(5);
    addIOBarWidget(spacer);
    addIOBarWidget(d_ptr->hideShowSidebarWidget);


    items = evApp->pluginsManager()->latestVersionsOf(EvPluginInfo::IOPaneLeftWidget);
    qSort(items.begin(),items.end(),EvMainWindow_compareWidgetsIndices);
    for(int i=0;i<items.size();++i){
        addIOBarWidget(qobject_cast<QWidget*>(items[i]));
    }
    spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    addIOBarWidget(spacer);

    items = evApp->pluginsManager()->latestVersionsOf(EvPluginInfo::IOPane);
    qSort(items.begin(),items.end(),EvMainWindow_compareWidgetsIndices);
    for(int i=0;i<items.size();++i){
        addIOPane( qobject_cast<EvIOPane*>(items[i]));
    }

    spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    addIOBarWidget(spacer);

    items = evApp->pluginsManager()->latestVersionsOf(EvPluginInfo::IOPaneRightWidget);
    qSort(items.begin(),items.end(),EvMainWindow_compareWidgetsIndices);
    for(int i=0;i<items.size();++i){
        addIOBarWidget(qobject_cast<QWidget*>(items[i]));
    }
    spacer = new QWidget;
    spacer->setFixedWidth(5);
    addIOBarWidget(spacer);

}

