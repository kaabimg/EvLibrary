#include "EvMimeData.h"
#include "EvObjectsContainer.h"
#include "EvObjectQmlExporter.h"

EvMimeData::EvMimeData() :
    QMimeData(),m_objects(new EvObjectsContainer(this))
{
}


void EvMimeData::setObject(EvObject * object)
{
    m_objects->clear();
    m_objects->addObject(object);
}

void EvMimeData::setObjects(const QList<EvObject *> & objects)
{
    m_objects->clear();
    m_objects->addObjects(objects);
}

bool EvMimeData::hasObjects() const
{
    return m_objects->count();
}

const EvObjectsContainer *EvMimeData::objects() const
{
    return m_objects;
}


QStringList EvMimeData::formats() const
{  
    QStringList formats ;
    formats << "application/evobject";
    if(hasObjects() && m_objects->count() == 1){
        formats <<"text/plain";
    }
    return formats;
}

bool EvMimeData::hasFormat(const QString &mimeType) const
{
    if(hasObjects()){
        if(mimeType == "application/evobject"){
            return true;
        }
        if(mimeType == "text/plain"){
            return m_objects->count() == 1;
        }
        return false;
    }

    return QMimeData::hasFormat(mimeType);
}

QVariant EvMimeData::retrieveData(const QString &mimeType, QVariant::Type type) const
{
    if(hasObjects()){
        if(mimeType == "application/evobject"){
            return QVariant::fromValue((QObject*)m_objects);
        }
        if(mimeType == "text/plain"){
            if(m_objects->count() && Ev::isObjectValid(m_objects->at(0))){
                EvObjectQmlExporter exporter;
                return exporter.objectToString(m_objects->at(0));
            }
        }
        return "";
    }

    return QMimeData::retrieveData(mimeType,type);
}

