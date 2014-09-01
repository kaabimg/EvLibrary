#ifndef EVCELLVIEW_H
#define EVCELLVIEW_H


#include "EvWidget.h"

class EvCell;
class EvState;
class EvSchematic;

class EvSchematicView;
class EvStateView;
class EvCellViewPrivate;

class EvCellView : public EvWidget
{
    Q_OBJECT
public:
    EvCellView(EvCell * cell,QWidget * parent=0);
    ~EvCellView();


private:
    EV_PRIVATE(EvCellView)

};

#endif // EVCELLVIEW_H
