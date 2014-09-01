#include "EvObject.h"
#include "EvProperty.h"
#include "EvObjectsManagement.h"
#include "EvObjectsContainer.h"
#include "EvSystem.h"
#include "EvApplication.h"
#include "EvObjectLink.h"
#include "EvApplicationObjects.h"

#include <QMetaClassInfo>
#include <QMetaProperty>


uint EvObject::objectsIds(0);

EvObject::EvObject(QObject *parent):
    QObject(parent),m_isLink(false)
{ 
    m_id = objectsIds++;
    connect(this,SIGNAL(objectNameChanged(QString)),this,SIGNAL(nameChanged(QString)));

    evApp->applicationObjects()->addObject(this);
}

EvObject::~EvObject()
{
    evApp->applicationObjects()->removeObject(this);
}

uint EvObject::objectId() const
{
    return m_id;
}


void EvObject::classBegin(){
    foreach (int type,supportedChildrenTypes()) {
        createChildrenContainer(type);
    }
}


void EvObject::componentComplete()
{
    EvSystem system;
    int size = m_genericChildren.size();
    int offset = 0;
    for(int i=0;i+offset<size;++i){
        EvObject * object = m_genericChildren[i-offset];
        if(!addObject(object)){
            system.warn(QString("Item of type '%0' can't be loaded as child of item of type '%1'.")
                        .arg(object->typeName())
                        .arg(typeName()));
            system.warn("Item will be deleted");
            delete m_genericChildren.takeAt(i-offset);
            offset++;
        }
    }
    finalize();
    m_diskState = Ev::Saved; // just loaded
}




void EvObject::finalize(){
    setTemporaryObject(false);
    m_diskState = Ev::Modified;
    m_status = Ev::Inactive;

    connectDesingableProperties();
    connect(this,SIGNAL(objectAdded(EvObject*,EvObject*)),this,SLOT(setModified()));
    connect(this,SIGNAL(objectRemoved(EvObject*,EvObject*)),this,SLOT(setModified()));
    connect(this,SIGNAL(designablePropertiesChanged()),this,SLOT(connectDesingableProperties()));
}

EvObject *EvObject::parentEvObject() const
{
    EvObject  * parent = qobject_cast<EvObject*>(this->parent());
    if(parent && parent->contains(this)){
        return parent;
    }
    return NULL;
}

bool EvObject::isAncestorOf(const EvObject * object) const
{
    EvObject * parent = object->parentEvObject();

    if(!parent){
        return false;
    }
    if(parent == this){
        return true;
    }
    return isAncestorOf(parent);
}


bool EvObject::supportsChildrenType(int type) const
{
    return m_typedChildren.contains(type);
}



EvObject *EvObject::createObject(int type, QObject *parent)
{
    EvObject * object = EvObjectsManagement::createObject(type);
    if(object){
        object->setParent(parent);
        object->classBegin();
        object->finalize();
    }
    return object;
}


QString EvObject::description() const {return m_description;}

int EvObject::allChildrenCount() const{
    return m_genericChildren.count();
}


EvObject *EvObject::child(int index) const
{
    int count = 0;
    foreach (int type, supportedChildrenTypes()) {
        if ( index< (count + m_typedChildren[type]->count()) ){
            return m_typedChildren[type]->at(index-count);
        }
        count += m_typedChildren[type]->count();
    }
    return NULL;
}



int EvObject::indexOf(const EvObject * child) const
{
    Q_ASSERT(child);
    int offset=0;

    if(child->parent() != this)
        return -1;

    foreach (int type, supportedChildrenTypes()) {
        if(type != child->typeId())
            offset += m_typedChildren[type]->count();
        else
            return offset + m_typedChildren[type]->indexOf(child);
    }
    Q_ASSERT(false);
    return -1;
}

int EvObject::indexInParent() const
{
    if(parentEvObject())
        return  parentEvObject()->indexOf(this);
    return 0;
}

bool EvObject::contains(const EvObject *child,bool recursive) const
{
    if(m_typedChildren.contains(child->typeId())) {
        if(m_typedChildren[child->typeId()]->contains(child)){
            return true;
        }
    }
    if(recursive){
        for(int i=0;i<m_genericChildren.size();++i){
            if(m_genericChildren[i]->contains(child,recursive)){
                return true;
            }
        }
    }
    return false;
}

bool EvObject::contains(int type, const QString &name) const
{
    if(!m_typedChildren.contains(type)){
        return false;
    }

    return m_typedChildren[type]->contains(name);
}

int EvObject::childrenCount(int type) const
{
    if(m_typedChildren.contains(type))
        return  m_typedChildren[type]->count();
    return 0;
}


EvObject * EvObject::child(int type,int index)const{
    if(m_typedChildren.contains(type)){
        return m_typedChildren[type]->at(index);
    }
    return NULL;

}
int EvObject::indexOf(int type,const EvObject * object)const{
    if(m_typedChildren.contains(type)){
        return m_typedChildren[type]->indexOf(object);
    }
    return -1;
}


void EvObject::bindOjects(EvObject *from, EvObject *to)
{
    foreach(const QByteArray & property,from->designablePropertiesNames()){
        Ev::bind(from,property,to,property);

        for(int i=0;i<from->m_genericChildren.size();++i){
            bindOjects(from->m_genericChildren[i],to->m_genericChildren[i]);
        }
    }
}


EvObjectLink *EvObject::createLink()
{
    return new EvObjectLink(this);
}

bool EvObject::isLink() const
{
    return m_isLink;
}

void EvObject::setObject(EvObject * object)
{
    addObject(object);
}

bool EvObject::addObject(EvObject * object, int index)
{
    Q_ASSERT(object);

    EvSystem system("Objects manager");
    if(m_typedChildren.contains(object->typeId())){
        if(contains(object)){
            EvSystem::Message message;
            message << "Can't add "<<object<<" to "<<this<<"\n";
            message << "Object already exists";
            system.warn(message);
            return false;
        }
        if(!m_genericChildren.contains(object)){// could be already added when this is created from qml
            m_genericChildren.append(object);
        }
        connectChild(object);
        if(object->objectName().isEmpty()){
            EvSystem::Message message;
            message << "Renaming  "<< object;
            object->setObjectName(generateDefaultName(object->typeId()));
            message << "  to a default name  "<<object<<"  when adding it to "<<this;
            system.warn(message);

        }
        m_typedChildren[object->typeId()]->addObject(object,index);
        Q_EMIT objectAdded(object,this);
        return true;
    }
    return false;
}

bool EvObject::removeObject(EvObject *object)
{
    if(!object)
        return false;
    if(m_typedChildren.contains(object->typeId()) &&
            m_typedChildren[object->typeId()]->contains(object)){

        Q_EMIT objectToBeRemoved(object,this);
        m_genericChildren.removeOne(object);
        m_typedChildren[object->typeId()]->removeObject(object);
        disconnetChild(object);
        Q_EMIT objectRemoved(object,this);
        return true;
    }
    return false;
}

bool EvObject::canAdd(EvObject * object) const
{
    return supportsChildrenType(object->typeId());
}

bool EvObject::renameChild(EvObject * object, const QString &name)
{
    if(!m_typedChildren[object->typeId()]->contains(name)){
        object->setObjectName(name);
        return true;
    }
    EvSystem output("Objects manager");
    EvSystem::Message message;
    message << "Failed to rename "<<object<<" to "<<name
            << ". An object with the same name already exists";
    output.error(message);
    return false;
}

void EvObject::setDescription(const QString &arg)
{
    if (m_description != arg) {
        m_description = arg;
        Q_EMIT descriptionChanged(arg);
    }
}


void EvObject::createChildrenContainer(int type)
{
    m_typedChildren[type] = new EvObjectsContainer(this);
    m_typedChildren[type]->setDeleteRemovedObjects(false);
}



QQmlListProperty<EvObject> EvObject::subObjects()
{
    return QQmlListProperty<EvObject>(this,m_genericChildren);
}

QVariant EvObject::toVariant() const
{
    return QVariant::fromValue((QObject*)this);
}




EvPropertiesList EvObject::designablePropertiesWrappers()
{
    return designablePropertiesWrappers(designablePropertiesNames());
}


EvPropertiesNames EvObject::designablePropertiesNames() const
{
    EvPropertiesNames properties;
    const QMetaObject  * mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); ++i) {
        QMetaProperty p = mo->property(i);
        if(p.isDesignable(this)){
            if(!properties.contains(p.name()))
                properties.append(p.name());
        }
        else{
            if(properties.contains(p.name()))
                properties.removeOne(p.name());
        }
    }
    return properties;
}


EvPropertiesList EvObject::designablePropertiesWrappers(const EvPropertiesNames & propertiesNames)
{
    EvPropertiesList wrappers;//list to keep creation order
    QHash<QString,EvProperty*> propertiesHash;// for access by name during customization
    foreach(const QByteArray & name,propertiesNames){
        EvProperty * wrapper = new EvProperty(this,name.constData());
        wrapper->setLabel(name);
        if(!metaObject()->property(metaObject()->indexOfProperty(name)).isWritable()){
            wrapper->setReadOnly(true);
        }

        wrappers<<wrapper;
        propertiesHash.insert(wrapper->objectName(),wrapper);
    }

    customizePropertiesWrappers(propertiesHash);

    return wrappers;
}

EvPropertiesNames EvObject::storedPropertiesNames() const
{
    EvPropertiesNames properties;
    const QMetaObject  * mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); ++i) {
        QMetaProperty p = mo->property(i);
        if(p.isStored(this)){
            if(!properties.contains(p.name()))
                properties.append(p.name());
        }
        else{
            if(properties.contains(p.name()))
                properties.removeOne(p.name());
        }
    }
    return properties;
}

QVariant EvObject::attribute(const QByteArray &name) const
{
    return property(EV_ATTRIBUTE_PREFIX+name);
}

bool EvObject::hasAttribute(const QByteArray &name) const
{
    return metaObject()->indexOfProperty(EV_ATTRIBUTE_PREFIX+name)>-1;
}

EvPropertiesNames EvObject::attributesNames() const
{
    EvPropertiesNames names= dynamicPropertyNames();
    for(int i=0;i<names.size();++i){
        if(!names[i].startsWith(EV_ATTRIBUTE_PREFIX)){
            names.removeAt(i);
            --i;
        }
    }
    return names;
}

bool EvObject::remove()
{
    if(parentEvObject()){
        return parentEvObject()->removeObject(this);
    }
    return false;
}


void EvObject::setAttribute(const QByteArray &name, const QVariant &value)
{
    setProperty(EV_ATTRIBUTE_PREFIX+name,value);
    Q_EMIT attributesChanged();
}


void EvObject::customizePropertiesWrappers(QHash<QString, EvProperty *> & propertiesHash) const
{
    propertiesHash["objectName"]->setLabel("Name");
    propertiesHash["description"]->setLabel("Description");
}



EvObject *EvObject::copy() const
{
    EvObject * object =  createObject(typeId());
    foreach(const QByteArray & propertyName,designablePropertiesNames()){
        object->setProperty(propertyName,this->property(propertyName));
    }
    foreach (const EvObject * child, m_genericChildren) {
        object->addObject(child->copy());
    }
    return object;
}

void EvObject::updateFrom(const EvObject *another)
{
    if(typeId() != another->typeId()){
        return;
    }

    foreach (const QByteArray & propertyName, designablePropertiesNames()) {
        setProperty(propertyName,another->property(propertyName));
    }
    foreach (int type, supportedChildrenTypes()) {
        EvObjectsContainer * container = m_typedChildren[type];
        container->clear();
        const EvObjectsContainer * anotherContainer = another->m_typedChildren[type];

        for(int i=0;i<anotherContainer->count();++i){
            addObject(anotherContainer->at(i)->copy());
        }
    }
}


/******************************************************************/


Ev::ObjectStatus EvObject::status() const
{
    return m_status;
}

Ev::ObjectDiskState EvObject::diskState() const
{
    return m_diskState;
}

void EvObject::setDiskState(Ev::ObjectDiskState arg)
{
    if (m_diskState != arg) {
        m_diskState = arg;
        Q_EMIT diskStateChanged(arg);
    }
}

bool EvObject::isTopLevelObject() const
{
    return false;
}


void EvObject::setModified()
{
    setDiskState(Ev::Modified);
    Q_EMIT modified(this);
}

QString EvObject::generateDefaultName(int type) const
{
    QString name = EvObjectsManagement::typeName(type);
    name = name.toLower()+"_";
    int index = 1;
    while(m_typedChildren[type]->contains(name+QString::number(index)))
        index++;
    return name+QString::number(index);
}



void EvObject::connectDesingableProperties()
{

    foreach(const QByteArray & property,m_lastConnectedDesignableProperties){
        Ev::unbind(this,property,this,SLOT(setModified()));

    }
    m_lastConnectedDesignableProperties = designablePropertiesNames();
    foreach(const QByteArray & property,m_lastConnectedDesignableProperties){
        Ev::bind(this,property,this,SLOT(setModified()));
    }
}

void EvObject::connectChild(EvObject * object)
{
    connect(object,SIGNAL(objectAdded(EvObject*,EvObject*)),
            this,SIGNAL(objectAdded(EvObject*,EvObject*)));
    connect(object,SIGNAL(objectToBeRemoved(EvObject*,EvObject*)),
            this,SIGNAL(objectToBeRemoved(EvObject*,EvObject*)));
    connect(object,SIGNAL(objectRemoved(EvObject*,EvObject*)),
            this,SIGNAL(objectRemoved(EvObject*,EvObject*)));
    connect(object,SIGNAL(modified(EvObject*)),
            this,SIGNAL(modified(EvObject*)));

    object->setParent(this);
}

void EvObject::disconnetChild(EvObject *object)
{
    disconnect(object,SIGNAL(objectAdded(EvObject*,EvObject*)),
            this,SIGNAL(objectAdded(EvObject*,EvObject*)));
    disconnect(object,SIGNAL(objectToBeRemoved(EvObject*,EvObject*)),
            this,SIGNAL(objectToBeRemoved(EvObject*,EvObject*)));
    disconnect(object,SIGNAL(objectRemoved(EvObject*,EvObject*)),
            this,SIGNAL(objectRemoved(EvObject*,EvObject*)));
    disconnect(object,SIGNAL(modified(EvObject*)),
            this,SIGNAL(modified(EvObject*)));


    object->setParent(NULL);
}






void EvObject::setStatus(Ev::ObjectStatus arg)
{
    if (m_status != arg) {
        m_status = arg;
        Q_EMIT statusChanged(arg);
    }
}

QVariant EvObject::property(const QByteArray &name) const
{
    return QObject::property(name);

}

bool EvObject::setProperty(const QByteArray &name, const QVariant &value)
{
    return QObject::setProperty(name,value);
}

bool EvObject::isTemporaryObject() const
{
    return m_temporary;
}

void EvObject::setTemporaryObject(bool temp)
{
    m_temporary = temp;
    for(int i=0;i<m_genericChildren.size();++i){
        m_genericChildren[i]->setTemporaryObject(m_temporary);
    }

}



/************************************************************************/


/************************************************************************/

void Ev::debugObject(const EvObject *object, int ident)
{
    QString i(ident,'\t');
    QStringList hierarchy;

    const QMetaObject * metaObject = object->metaObject();
    while (metaObject) {
        hierarchy<<metaObject->className();
        metaObject = metaObject->superClass();
    }
    qDebug()<<qPrintable(i)<<object<<hierarchy;
    foreach(const QByteArray & pName , object->designablePropertiesNames()){
        qDebug()<<i+'\t'<<pName<<object->property(pName.constData());
    }

    foreach (const QObject * child,object->children()) {
        debugObject(qobject_cast<const EvObject*>(child),ident+2);
    }
}








