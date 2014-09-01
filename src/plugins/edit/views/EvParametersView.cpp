#include "EvParametersView.h"
#include "EvProcess.h"
#include "EvAppSettings.h"
#include <QTextEdit>
#include <QTableView>
#include <QResizeEvent>
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>
#include "EvObjectsContainer.h"
#include "EvMimeData.h"
#include "EvParameter.h"
#include "EvSystem.h"
#include "../models/EvParameterValueDelegate.h"
#include "../models/EvParametersModel.h"


EvParametersView::EvParametersView(EvProcess *process, QWidget *parent) :
    EvWidget(process,parent)
{
    setWindowTitle("Parameters");
    setWindowIcon(evIconsFactory->objectIcon(Ev::Parameter,EvIconsFactory::Light));

    setBehaviorFlags(
                SupportsCopyPaste |
                SupportsUndoRedo
                );

    m_parametersTable = new QTableView(this);
    EvParametersModel * model = new EvParametersModel(
                process,
                this->commandsInterface(),
                m_parametersTable
                );
    m_parametersTable->setModel(model);
    m_parametersTable->setSelectionBehavior(QTableView::SelectRows);
    m_parametersTable->setItemDelegateForColumn(2,new EvParameterValueDelegate(m_parametersTable));

    setContent(m_parametersTable);


    addAction(createAction(
                  evIconsFactory->applicationIcon(EvIconsFactory::Add,EvIconsFactory::Colored),
                  "Add paramter",
                  SLOT(addParameter())
                  )
              );
    addAction(createAction(
                  evIconsFactory->applicationIcon(EvIconsFactory::Remove,EvIconsFactory::Colored),
                  "Remove selected parameter(s)",
                  SLOT(removeSelectedParameters())
                  )
              );


    connect(m_parametersTable->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(onSelectionChanged()));

}

bool EvParametersView::containsObject(const EvObject * object) const
{
    return object->is<EvParameter>() && evObject()->contains(object);
}

bool EvParametersView::showObject(EvObject * parameter)
{
    int row = evObject()->indexOf(Ev::Parameter,parameter);
    if(row != -1){
        QModelIndex index = m_parametersTable->model()->index(row,0);
        m_parametersTable->selectionModel()->select(
                        index,
                        QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows
                    );
        Q_EMIT showRequest(this);
        return true;
    }
    return false;
}



void EvParametersView::resizeEvent(QResizeEvent * e)
{
    EvWidget::resizeEvent(e);

    int w = e->size().width();
    w -= m_parametersTable->verticalHeader()->width();
    w -= 1;


    m_parametersTable->setColumnWidth(0,w/4);
    m_parametersTable->setColumnWidth(1,w/4);
    m_parametersTable->setColumnWidth(2,w/2);
}

void EvParametersView::onSelectionChanged()
{
    QModelIndexList selection = m_parametersTable->selectionModel()->selectedIndexes();
    EvObjectsList parameters;
    foreach (const QModelIndex & index, selection) {
        if(index.column() == 0){
            parameters << evObject()->child<EvParameter>(index.row());
        }
    }
    if(parameters.isEmpty()){
        clipboardInterface()->clearSelection();
        setCopyEnabled(false);
        setCutEnabled(false);
    }
    else {
        clipboardInterface()->setSelection(parameters);
    }

}

QStringList EvParametersView::selectedParametersNames() const
{
    QStringList names;
    foreach(const QModelIndex & index, m_parametersTable->selectionModel()->selectedRows()){
        if(index.column() == 0){
            names << m_parametersTable->model()->data(index).toString();
        }
    }
    return names;
}

void EvParametersView::paste()
{
    qDebug()<<" =========  EvParametersView::paste";
    const QMimeData * data = qApp->clipboard()->mimeData();
    if(data->hasFormat("application/evobject")){

        const EvMimeData * evData = qobject_cast<const  EvMimeData * >(data);
        const EvObjectsContainer * container = evData->objects();

        const EvObjectsContainer * selection = clipboardInterface()->selectedObjects();

        qDebug()<<"---------------  paste , mode "<<data->property("mode");
        for(int i=0;i<container->count();++i){
            qDebug()<<container->at(i);
        }
        qDebug()<<"-- into";
        for(int i=0;i<selection->count();++i){
            qDebug()<<selection->at(i);
        }
    }
}


void EvParametersView::addParameter()
{
    qobject_cast<EvParametersModel*>(m_parametersTable->model())->addParameter();
}

void EvParametersView::removeSelectedParameters()
{
    QStringList parameters =selectedParametersNames();
    if(parameters.size()){
        EvSystem out("Objects manager");

        if(out.question("Remove parameter(s) "+parameters.join(", ")+" ?")){
            qobject_cast<EvParametersModel*>(m_parametersTable->model())->removeParameters();
        }
    }
}
