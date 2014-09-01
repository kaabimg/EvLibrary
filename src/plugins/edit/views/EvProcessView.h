#ifndef EVPROCESSVIEW_H
#define EVPROCESSVIEW_H

#include "EvTabWidget.h"

class EvProcess;
class EvLibrariesView;
class EvParametersView;
class EvFiltersView;

class EvProcessView : public EvTabWidget
{
    Q_OBJECT
public:
    explicit EvProcessView(EvProcess*,QWidget *parent = 0);
    bool showObject(EvObject*);

    void setAsActiveWidget();
private:
    EvLibrariesView * m_librariesView;
    EvParametersView * m_parametersView;
    EvFiltersView  * m_filtersView;


};

#endif // EVPROCESSVIEW_H
