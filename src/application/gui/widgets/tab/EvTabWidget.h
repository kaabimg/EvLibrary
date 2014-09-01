#ifndef EVTABWIDGET_H
#define EVTABWIDGET_H

#include <QWidget>

#include "EvGlobal.h"
#include "EvWidget.h"

class EvWidget;
class EvTabWidgetPrivate;
class EvTabBar;


class EvTabWidget : public EvWidget
{
    Q_OBJECT
public:
    explicit EvTabWidget(QWidget *parent = 0);
    EvTabBar * tabBar()const;



public Q_SLOTS:// EvWidget api

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

    bool showObject(EvObject *);


private:
    EV_PRIVATE(EvTabWidget)
};

#endif // EVTABWIDGET_H
