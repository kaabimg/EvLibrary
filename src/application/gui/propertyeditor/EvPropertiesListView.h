#ifndef EVPROPERTIESLISTVIEW_H
#define EVPROPERTIESLISTVIEW_H

#include <QTreeView>
#include "EvProperty.h"

class EvPropertiesListView : public QTreeView
{
    Q_OBJECT
public:
    explicit EvPropertiesListView(EvProperty * group, QWidget *parent = 0);
    explicit EvPropertiesListView(const EvPropertiesList & list,QWidget *parent = 0);
    explicit EvPropertiesListView(EvObject  * object,QWidget *parent = 0);

};

#endif // EVPROPERTIESLISTVIEW_H
