#ifndef EVMAINWINDOWIOBAR_H
#define EVMAINWINDOWIOBAR_H

#include <QWidget>
#include "EvGlobal.h"


class EvToolButton;
class EvMainWindowIOBarPrivate;
class EvIOPane;
class EvMainWindowIOBar : public QWidget
{
    Q_OBJECT
public:
    EvMainWindowIOBar(QWidget * parent =0);
    virtual ~EvMainWindowIOBar();
    void addWidget(QWidget *);
    void addPane(EvIOPane*);

Q_SIGNALS:
    void showRequest(EvIOPane*);
    void hideRequest();

protected:
    void paintEvent(QPaintEvent *e);
protected Q_SLOTS:
    void paneButtonToggled(bool);
    void animatePanes();
    void animatePane();
    void animatePane(EvIOPane*);
private:
    EV_PRIVATE(EvMainWindowIOBar)
};


#endif // EVMAINWINDOWIOBAR_H
