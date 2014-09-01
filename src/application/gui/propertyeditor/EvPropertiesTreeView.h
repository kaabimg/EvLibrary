#ifndef EVPROPERTIESTREEVIEW_H
#define EVPROPERTIESTREEVIEW_H

#include <QTreeView>

#include "EvProperty.h"

class EvPropertiesTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit EvPropertiesTreeView(EvProperty * group, QWidget *parent = 0);
    explicit EvPropertiesTreeView(const EvPropertiesList & list,QWidget *parent = 0);
    explicit EvPropertiesTreeView(EvObject  * object,QWidget *parent = 0);

};

#endif // EVPROPERTIESTREEVIEW_H
