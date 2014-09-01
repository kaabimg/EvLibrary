#ifndef EVIOPANECONTAINER_H
#define EVIOPANECONTAINER_H

#include <QWidget>
#include "EvGlobal.h"
class EvIOPane;

class EvIOPaneContainerPrivate;

class EvIOPaneContainer : public QWidget
{
    Q_OBJECT
public:
    explicit EvIOPaneContainer(QWidget *parent = 0);
    int preferredSize()const;
Q_SIGNALS:
    void showRequest();
    void hideRequest();

public Q_SLOTS:
    void showPane(EvIOPane*);

private:
    EV_PRIVATE(EvIOPaneContainer)
};

#endif // EVIOPANECONTAINER_H
