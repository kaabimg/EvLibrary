#ifndef EVFILTERSVIEW_H
#define EVFILTERSVIEW_H

#include "EvWidget.h"
class EvProcess;

class EvFiltersView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvFiltersView(EvProcess * process,QWidget *parent = 0);

signals:

public slots:

};

#endif // EVFILTERSVIEW_H
