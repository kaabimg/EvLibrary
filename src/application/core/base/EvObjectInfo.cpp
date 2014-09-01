#include "EvObjectInfo.h"
#include "EvObject.h"

EvObjectInfo::EvObjectInfo(const EvObject *object):
    m_object(object)
{

}

QString EvObjectInfo::hierarchicalName() const
{
    return hierarchy().join('.');
}
QStringList EvObjectInfo::hierarchy() const
{
    QStringList h;
    h << m_object->objectName();
    EvObject * parent = m_object->parentEvObject();
    while (parent) {
         h<< parent->objectName();
    }
    return h;
 }
