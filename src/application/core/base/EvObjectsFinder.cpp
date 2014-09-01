#include "EvObjectsFinder.h"
#include "EvObject.h"
#include "EvObjectsManagement.h"

QList<EvObject *> EvObjectsFinder::find(
        const EvObjectsFinder::FindData &data,
        const EvObject *parent)
{
    EvObjectsList objects = parent->findChildren<EvObject*>(
                QRegExp(data.regexp,Qt::CaseInsensitive),
                Qt::FindChildrenRecursively
                );

    if(data.objectType==Ev::Object)
        return objects;

    for(int i=0;i<objects.size();++i){
        if(objects[i]->typeId() != data.objectType){
            objects.removeAt(i);
            --i;
        }
    }

    return objects;
}
