#include "EvHelpView.h"

#include "EvAppSettings.h"
#include "EvApplicationDocumentation.h"
#include "EvDocumentation.h"
#include "EvMainWindow.h"
#include "EvHideShowSideBarWidget.h"
#include "EvVideoPlayer.h"

#include <QWebView>

EvHelpView::EvHelpView(QWidget *parent) :
    EvObjectsTreeTabWidget(evApp->documentation(),parent)
{
    setWindowTitle("Help");
    setEnabled(true);
    setWindowIcon(evApp->iconsFactory()->applicationIcon(EvIconsFactory::Help,EvIconsFactory::Light));
    setProperty("index",4);

    setBehaviorFlags(
                HasSideBarInteractions |
                HasHideSideBarFeature |
                HasShowSideBarFeature
                );

    setMaxSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth() -1// -1 == splitter handle
                );

    setSideBarSize(
                evMainWindow->logoWidth()+
                2 * evMainWindow->tabWidth()-1
                );


    m_videoPlayer = new EvVideoPlayer(this);
    m_webView = new QWebView(this);
    setCurrentStackWidget(m_videoPlayer);
    setCurrentStackWidget(m_webView);
    createHelpItems();



}

void EvHelpView::minimizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1 ;// -1 == splitter handle
    int width = 0;

    if(sideBarSize() > mid)
        width = mid;

    setSideBarSize(width);
}

void EvHelpView::maximizeSideBar()
{
    int mid = evMainWindow->logoWidth()-1;// -1 == splitter handle
    int max = evMainWindow->logoWidth()+
            2 * evMainWindow->tabWidth()-1 ;// -1 == splitter handle

    int width = mid;

    if(sideBarSize() >= mid)
        width = max;

    setSideBarSize(width);
}

void EvHelpView::onObjectSelected(EvObject *object)
{
    EvDocumentation * doc = object->to<EvDocumentation>();
    Q_ASSERT(doc);
    if(doc->documentationType() == EvDocumentation::Video){
        m_videoPlayer->stop();
        m_videoPlayer->setMediaFile(doc->filePath());
        setCurrentStackWidget(m_videoPlayer);
    }
    else {
         m_videoPlayer->stop();
         m_webView->load(QUrl::fromLocalFile(doc->filePath()));
         setCurrentStackWidget(m_webView);
    }
}



void EvHelpView::showEvent(QShowEvent * e)
{
    EvObjectsTreeTabWidget::showEvent(e);
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
            this,SLOT(minimizeSideBar()));
    connect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
            this,SLOT(maximizeSideBar()));
}

void EvHelpView::hideEvent(QHideEvent * e)
{
    EvObjectsTreeTabWidget::hideEvent(e);
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(minimizeRequest()),
               this,SLOT(minimizeSideBar()));
    disconnect(evMainWindow->hideShowSizeBarWidget(),SIGNAL(maximizeRequest()),
               this,SLOT(maximizeSideBar()));

}

EvWidget *EvHelpView::createViewForObject(EvObject * )
{
    return NULL;
}

bool EvHelpView::supportsObjectType(int type)const
{
    return type == Ev::Documentation;
}


void EvHelpView::createHelpItems()
{
    EvDocumentation * documentation;

    documentation = EvObject::create<EvDocumentation>();


    documentation->setObjectName("Html example");
    documentation->setDocumentationType(EvDocumentation::Html);
    documentation->setFilePath("/home/ghaith/development/workspace/EzVerif/EzVerif/ressources/html/example1.html");
    evApp->documentation()->add<EvDocumentation>(documentation);

    documentation = EvObject::create<EvDocumentation>();
    documentation->setObjectName("Video example");
    documentation->setDocumentationType(EvDocumentation::Video);
    documentation->setFilePath("/home/ghaith/development/workspace/EzVerif/EzVerif/ressources/videos/tutorial1.mp4");
    evApp->documentation()->add<EvDocumentation>(documentation);




}
