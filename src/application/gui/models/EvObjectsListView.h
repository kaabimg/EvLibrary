#ifndef EVOBJECTSLISTVIEW_H
#define EVOBJECTSLISTVIEW_H

#include <QListView>
#include "EvObject.h"

class EvObjectsContainer;


class EvObjectsListView : public QListView
{
    Q_OBJECT
public:
    explicit EvObjectsListView(QWidget *parent = 0);
    explicit EvObjectsListView(EvObjectsContainer *, QWidget *parent = 0);

    void setContainer(EvObjectsContainer * objects);
    void setContent(const EvObjectsList &);

};

#endif // EVOBJECTSLISTVIEW_H
