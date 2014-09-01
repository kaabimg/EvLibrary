#include "EvObjectsManagement.h"
#include "EvObject.h"

QHash<int,EvTypeMetaInfo> EvObjectsManagement::types;


QString EvObjectsManagement::typeName(int id){
    if( types.contains(id))
        return types.value(id).name;
    return "Unknown";
}

QString EvObjectsManagement::typeLabel(int id)
{
    if( types.contains(id))
        return types.value(id).label;
    return "Unknown";
}

int EvObjectsManagement::typeFromName(const QString &name, Qt::CaseSensitivity cs)
{
    QHash<int,EvTypeMetaInfo>::const_iterator i = types.constBegin();

    while(i != types.constEnd()){
        if((*i).name.compare(name,cs) ==0)
            return (*i).typeId;
        ++i;
    }
    return Ev::UnknownType;
}

EvObject *EvObjectsManagement::createObject(int type, const EvVersion &version){

    if(version.isValid()){
        if(types.contains(type)){
            if(types[type].metaObjects.contains(version)){
                return qobject_cast<EvObject*>(types[type].metaObjects[version].newInstance());
            }
        }
    }
    else{
        if(types.contains(type)){
            if(!types[type].metaObjects.isEmpty()){
                // return the latest version
                return qobject_cast<EvObject*>(types[type].metaObjects.last().newInstance());
            }
        }
    }
    qDebug()<<"Type"<<type<<typeName(type)<<version.majorVersion<<version.minorVersion<<"not found";
    return NULL;
}

void EvObjectsManagement::registerType(const EvTypeMetaInfo & info)
{

    if(types.contains(info.typeId)){
        types[info.typeId].metaObjects.insert(
                    info.metaObjects.keys().first(),
                    info.metaObjects.values().first());
    }
    else
        types.insert(info.typeId,info);
}
