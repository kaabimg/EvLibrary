#include "EvClipboardInterface.h"
#include "EvObjectsContainer.h"
#include <QApplication>
#include <QClipboard>
#include "EvMimeData.h"
#include "EvObject.h"

struct EvClipboardInterfacePrivate{
    EvObjectsContainer selection;
};

EvClipboardInterface::EvClipboardInterface(QObject *parent):
    QObject(parent),
    d_ptr(new EvClipboardInterfacePrivate)
{}

EvClipboardInterface::~EvClipboardInterface()
{
    delete d_ptr;
}

void EvClipboardInterface::setSelection(EvObject *object)
{
    d_ptr->selection.clear();
    d_ptr->selection.addObject(object);
    Q_EMIT selectionChanged();
}

void EvClipboardInterface::setSelection(const QList<EvObject *> & objects)
{
    d_ptr->selection.clear();
    d_ptr->selection.addObjects(objects);
    Q_EMIT selectionChanged();
}

bool EvClipboardInterface::hasSelection() const
{
    return d_ptr->selection.count();
}

void EvClipboardInterface::clearSelection()
{
    if(hasSelection()){
        d_ptr->selection.clear();
        Q_EMIT selectionChanged();
    }

}

const EvObjectsContainer *EvClipboardInterface::selectedObjects() const
{
    return & d_ptr->selection;
}

void EvClipboardInterface::setCopyObject(EvObject * object)
{
    EvMimeData * mimeData = new EvMimeData;
    mimeData->setObject(object);
    mimeData->setProperty("mode","copy");
    qApp->clipboard()->setMimeData(mimeData);
    Q_EMIT clipboardObjectsChanged();
}

void EvClipboardInterface::setCutObject(EvObject * object)
{
    EvMimeData * mimeData = new EvMimeData;
    mimeData->setObject(object);
    mimeData->setProperty("mode","cut");
    qApp->clipboard()->setMimeData(mimeData);
    Q_EMIT clipboardObjectsChanged();
}

void EvClipboardInterface::setCopyObjects(const QList<EvObject *> & objects)
{
    EvMimeData * mimeData = new EvMimeData;
    mimeData->setObjects(objects);
    mimeData->setProperty("mode","copy");
    qApp->clipboard()->setMimeData(mimeData);
    Q_EMIT clipboardObjectsChanged();
}

void EvClipboardInterface::setCutObjects(const QList<EvObject *> & objects)
{
    EvMimeData * mimeData = new EvMimeData;
    mimeData->setObjects(objects);
    mimeData->setProperty("mode","cut");
    qApp->clipboard()->setMimeData(mimeData);
    Q_EMIT clipboardObjectsChanged();
}

void EvClipboardInterface::copy()
{
    if(hasSelection()){
        setCopyObjects(selectedObjects()->objects());
    }
}

void EvClipboardInterface::cut()
{
    if(hasSelection()){
        setCutObjects(selectedObjects()->objects());
    }
}

void EvClipboardInterface::paste()
{
    qDebug()<<"paste";
    const QMimeData * data = qApp->clipboard()->mimeData();
    if(data->hasFormat("application/evobject")){

        const EvMimeData * evData = qobject_cast<const  EvMimeData * >(data);
        const EvObjectsContainer * container = evData->objects();

        const EvObjectsContainer * selection = selectedObjects();

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

void EvClipboardInterface::clearClipboardObject()
{
    qApp->clipboard()->clear();
    Q_EMIT clipboardObjectsCleared();
}

bool EvClipboardInterface::canCopy() const
{
    return d_ptr->selection.count();
}

bool EvClipboardInterface::canPaste() const
{
    return canPaste(&d_ptr->selection);
}

bool EvClipboardInterface::canPaste(const EvObjectsContainer * objects) const
{
    if(selectedObjects()->count() != 1)
        return false;

    for(int i=0;i<objects->count();++i){
        if(!selectedObjects()->at(0)->supportsChildrenType(objects->at(i)->typeId())){
            return false;
        }
    }
    return true;
}
