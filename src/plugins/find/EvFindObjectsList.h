#ifndef EVFINDOBJECTSLIST_H
#define EVFINDOBJECTSLIST_H

#include <QListWidget>
#include <QTimer>

#include "EvObjectsContainer.h"

#include "EvObjectsFinder.h"
#include "EvObjectsListView.h"

class EvObject;


class EvFindObjectsList : public EvObjectsListView
{
    Q_OBJECT
public:
    explicit EvFindObjectsList(QWidget *parent = 0);


Q_SIGNALS:
    void objectSelected(EvObject*);

public Q_SLOTS:
    void setFindData(const EvObjectsFinder::FindData &);
    void selectNext();
    void selectPrevious();
    void selectCurrentObject();

protected Q_SLOTS:
    void updateObjects();

private:
    QTimer m_findTimer;
    EvObjectsContainer m_container;
    EvObjectsFinder::FindData m_findData;


};

#endif // EVFINDOBJECTSLIST_H
