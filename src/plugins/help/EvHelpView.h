#ifndef EVHELPVIEW_H
#define EVHELPVIEW_H

#include "EvObjectsTreeTabWidget.h"
class EvVideoPlayer;
class QWebView;


class EvHelpView : public EvObjectsTreeTabWidget
{
    Q_OBJECT
public:
    explicit EvHelpView(QWidget *parent = 0);


protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    EvWidget *createViewForObject(EvObject * );
    bool supportsObjectType(int type)const;

    void createHelpItems();


protected Q_SLOTS:
    void minimizeSideBar();
    void maximizeSideBar();
    void onObjectSelected(EvObject * object);

private:
    EvVideoPlayer * m_videoPlayer;
    QWebView  * m_webView;
};

#endif // EVHELPVIEW_H
