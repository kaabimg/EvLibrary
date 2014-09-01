#ifndef EVEDITVIEW_H
#define EVEDITVIEW_H

#include "EvObjectsTreeTabWidget.h"

class EvEditViewPrivate;
class EvEditView : public EvObjectsTreeTabWidget
{
    Q_OBJECT
public:
    explicit EvEditView(QWidget *parent = 0);
    ~EvEditView();

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

    void onSideBarFocusIn();
    void onSideBarFocusOut();



private:
    EV_PRIVATE(EvEditView)

};

#endif // EVEDITVIEW_H
