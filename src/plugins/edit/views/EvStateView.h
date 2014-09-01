#ifndef EVSTATEVIEW_H
#define EVSTATEVIEW_H

#include "EvWidget.h"


class EvState;
class EvStateViewPrivate;

class EvStateView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvStateView(EvState* state,QWidget *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

private:
    EV_PRIVATE(EvStateView)

};

#endif // EVSTATEVIEW_H
