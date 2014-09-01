#ifndef EVSCHEMATICVIEW_H
#define EVSCHEMATICVIEW_H

#include "EvWidget.h"

class EvSchematic;
class EvSchematicViewPrivate;

class EvSchematicView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvSchematicView(EvSchematic * ,QWidget *parent = 0);

Q_SIGNALS:

public Q_SLOTS:

private:
    EV_PRIVATE(EvSchematicView)

};

#endif // EVSCHEMATICVIEW_H
