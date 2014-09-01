#ifndef EVOBJECTSTREETABWIDGET_H
#define EVOBJECTSTREETABWIDGET_H

#include "EvGlobal.h"
#include "EvWidget.h"

class EvObjectsTreeModel;
class EvObjectsTreeView;
class EvObjectsTreeTabWidgetPrivate;

class EvObjectsTreeTabWidget : public EvWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly)
public:
    explicit EvObjectsTreeTabWidget(
            EvObject * rootObject,
            QWidget *parent = 0);

    ~EvObjectsTreeTabWidget();

    EvObjectsTreeView * sideBar()const;

    // EvWidget api

    virtual void add(EvWidget * ,int index = -1);
    virtual void remove(EvWidget * );

    virtual bool contains(EvWidget * );
    virtual int indexOf(EvWidget *);

    virtual QList<EvWidget*> chilrenWidgets()const;
    virtual int childrenWidgetsCount()const;

    virtual void setCurrentWidget(EvWidget*);
    virtual void setCurrentIndex(int);

    virtual  EvWidget* currentWidget()const;
    virtual  int currentIndex()const;

    virtual bool containsObject(const EvObject*)const;
    virtual bool showObject(EvObject*);

    ////////

    int sideBarSize()const;
    void setSideBarSize(int);
    void setMaxSideBarSize(int);
    void setMinSideBarSize(int);
    bool readOnly() const;

    EvObjectsTreeModel * model()const;


Q_SIGNALS:
    void sideBarFocusIn();
    void sideBarFocusOut();

public Q_SLOTS:
    void setReadOnly(bool arg);

protected  Q_SLOTS:
    virtual void onObjectSelected(EvObject*);
    virtual void onRemoveRequest(EvObject*){}
    virtual void onCopyRequest(EvObject*){}
    virtual void onCutRequest(EvObject*){}
    virtual void onPasteRequest(EvObject*){}
    virtual void onSaveRequest(EvObject*){}
    void onObjectRemoved(EvObject*,EvObject*);




protected:
    virtual EvWidget * createViewForObject(EvObject * )=0;
    virtual bool supportsObjectType(int type)const=0;
    void setCurrentStackWidget(QWidget*);


private:
    EV_PRIVATE(EvObjectsTreeTabWidget)
};

#endif // EVOBJECTSTREETABWIDGET_H
