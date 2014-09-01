#ifndef EVEDITPROJECTVIEW_H
#define EVEDITPROJECTVIEW_H


#include "EvWidget.h"

class EvProject;
class EvCell;
class EvCellView;
class EvEditProjectViewPrivate;

class EvEditProjectView : public EvWidget
{
    Q_OBJECT
public:
    EvEditProjectView(EvProject * project,QWidget * parent=0);
    ~EvEditProjectView();
    bool supportsProcessing()const{return true;}


private:
    EV_PRIVATE(EvEditProjectView)

};

#endif // EVEDITPROJECTVIEW_H
