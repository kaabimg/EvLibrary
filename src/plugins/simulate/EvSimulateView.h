#ifndef EVSIMULATEVIEW_H
#define EVSIMULATEVIEW_H

#include "EvObjectsTreeTabWidget.h"

class EvSimulateViewPrivate;
class EvSimulateView : public EvObjectsTreeTabWidget
{
    Q_OBJECT
public:
    explicit EvSimulateView(QWidget *parent = 0);
    ~EvSimulateView();

protected:
    void setAsActiveWidget();
    EvWidget * createViewForObject(EvObject *);
    bool supportsObjectType(int type)const;


protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

protected Q_SLOTS:
    void minimizeSideBar();
    void maximizeSideBar();

    void onObjectSelected(EvObject*);
    void onRemoveRequest(EvObject*);
    void onCopyRequest(EvObject*);
    void onCutRequest(EvObject*);
    void onPasteRequest(EvObject*);
    void onSaveRequest(EvObject*);



private:
    EV_PRIVATE(EvSimulateView)

};

#endif // EVSIMULATEVIEW_H
