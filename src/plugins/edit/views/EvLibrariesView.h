#ifndef EVLIBRARIESVIEW_H
#define EVLIBRARIESVIEW_H

#include "EvWidget.h"
class EvProcess;

class EvLibrariesView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvLibrariesView(EvProcess * process,QWidget *parent = 0);


};

#endif // EVLIBRARIESVIEW_H
