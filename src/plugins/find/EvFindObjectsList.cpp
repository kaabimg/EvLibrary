#include "EvFindObjectsList.h"
#include "../../application/core/settings/EvAppSettings.h"
#include "../../ezverif/data/project/EvSession.h"
#include "../../application/core/base/EvObjectsManagement.h"


EvFindObjectsList::EvFindObjectsList(QWidget *parent) :
    EvObjectsListView(parent)
{
    m_findTimer.setInterval(500);
    m_findTimer.setSingleShot(true);
    connect(&m_findTimer,SIGNAL(timeout()),this,SLOT(updateObjects()));
    setContainer(&m_container);
    setSelectionMode(SingleSelection);
}

void EvFindObjectsList::setFindData(const EvObjectsFinder::FindData & data)
{
    m_findData = data;
    updateObjects();
    //m_findTimer.start();
}


void EvFindObjectsList::selectPrevious()
{
    QList<QModelIndex> selection = selectedIndexes();

    if(selection.isEmpty())
        setCurrentIndex(model()->index(0,0));
    else{
        int row = selection.first().row();
         setCurrentIndex(model()->index(qMax(0,row-1),0));
    }
}

void EvFindObjectsList::selectNext()
{
    QList<QModelIndex> selection = selectedIndexes();

    if(selection.isEmpty())
        setCurrentIndex(model()->index(0,0));
    else{
        int row = selection.first().row();
         setCurrentIndex(model()->index(qMin(m_container.count()-1,row+1),0));
    }
}

void EvFindObjectsList::selectCurrentObject()
{
    QList<QModelIndex> selection = selectedIndexes();

    if(!selection.isEmpty())
        Q_EMIT objectSelected(m_container.at(selection.first().row()));
}


void EvFindObjectsList::updateObjects()
{ 
    int selectedRow = 0;

    QList<QModelIndex> selection = selectedIndexes();

    if(!selection.isEmpty()){
        selectedRow  = selection.first().row();
    }

    setContent(EvObjectsFinder::find(m_findData,evApp->currentSession()));

    if(model()->rowCount()){
         setCurrentIndex(model()->index(qMin(m_container.count()-1,selectedRow),0));
    }


}
