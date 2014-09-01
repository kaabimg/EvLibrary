#ifndef EVOBJECT_H
#define EVOBJECT_H


#include <QQmlListProperty>
#include <QQmlParserStatus>
#include "EvMacros.h"
#include "EvGlobal.h"
#include "EvVariantUtils.h"
#include "EvObjectsRemoveRestore.h"

class EvObject;
class EvObjectLink;
class EvProperty;
class EvObjectsContainer;

typedef QList<QByteArray> EvPropertiesNames;
typedef QList<EvProperty*> EvPropertiesList;
typedef QList<int> EvTypesList;
typedef QList<EvObject*> EvObjectsList;


#define EV_ATTRIBUTE_PREFIX "a_"



class EvObject :
        public QObject,
        public QQmlParserStatus
{
    Q_INTERFACES(QQmlParserStatus)

    Q_OBJECT
    EV_OBJECT(Core,Object,1,0)
    EV_TYPE_LABEL("Unknown type")

    Q_PROPERTY(uint objectId READ objectId DESIGNABLE false STORED false)
    Q_PROPERTY(int typeId READ typeId DESIGNABLE false STORED false)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(Ev::ObjectDiskState diskState READ diskState WRITE setDiskState NOTIFY diskStateChanged DESIGNABLE false STORED false)
    Q_PROPERTY(Ev::ObjectStatus status READ status WRITE setStatus NOTIFY statusChanged DESIGNABLE false STORED false)


    // for qml
    Q_PROPERTY(QQmlListProperty<EvObject> subObjects READ subObjects DESIGNABLE false STORED false)
    Q_CLASSINFO("DefaultProperty", "subObjects")

public:

    Q_INVOKABLE EvObject(QObject * parent = 0);
    virtual ~EvObject();

    uint objectId() const;

    EvObject *parentEvObject()const;

    bool isAncestorOf(const EvObject*)const;

    // generic api
    static EvObject  * createObject(int type,QObject * parent = 0);
    bool addObject(EvObject *,int index=-1);
    bool removeObject(EvObject *);
    bool canAdd(EvObject*)const;



    // children type
    Q_INVOKABLE virtual EvTypesList supportedChildrenTypes()const{return EvTypesList();}
    Q_INVOKABLE bool supportsChildrenType(int type)const;

    // children api
    int allChildrenCount()const;
    Q_INVOKABLE EvObject * child(int index)const;
    Q_INVOKABLE int indexOf(const EvObject *)const;
    Q_INVOKABLE int indexInParent()const;
    Q_INVOKABLE bool contains(const EvObject *child,bool recursive = false)const;
    Q_INVOKABLE bool contains(int type,const QString & name)const;

    // typed children api
    int childrenCount(int type)const;
    EvObject * child(int type,int index)const;
    Q_INVOKABLE int indexOf(int type,const EvObject *)const;


    // template api
    template <typename T> static T * create(QObject * parent = 0);
    template <typename T> void set(T*);
    template <typename T> bool add(T*,int index=-1);
    template <typename T> T* createAndAdd(const QString & name,int index=-1);

    template <typename T> int count()const;
    template <typename T> T * child(int index) const;
    template <typename T> bool remove(T*);
    template <typename T> T* to();

    template <typename T> bool is()const;


    // linking

    Q_INVOKABLE EvObjectLink * createLink();
    Q_INVOKABLE bool isLink()const;


    // object name
    Q_INVOKABLE QString generateDefaultName(int type)const;

    // description
    QString description() const;
    Q_INVOKABLE void setDescription(const QString & arg);



    // designable propeties (can be edited in the properties editor)
    EvPropertiesNames designablePropertiesNames()const;
    EvPropertiesList designablePropertiesWrappers();
    EvPropertiesList designablePropertiesWrappers(const EvPropertiesNames &);


    // stored properties  : saved object properties on disk
    EvPropertiesNames storedPropertiesNames()const;


    // attributes : information on object.
    // Used in properties editor as metadata (min, max, step, initial file path ...)
    Q_INVOKABLE void setAttribute(const QByteArray& name,const QVariant & value);
    Q_INVOKABLE QVariant attribute(const QByteArray & name)const;
    Q_INVOKABLE bool hasAttribute(const QByteArray & name)const;
    EvPropertiesNames attributesNames()const;


    // remove copy update
    Q_INVOKABLE bool remove();
    Q_INVOKABLE virtual EvObject* copy()const;
    Q_INVOKABLE void updateFrom(const EvObject * another);



    //state

    Ev::ObjectDiskState diskState() const;
    Q_INVOKABLE void setDiskState(Ev::ObjectDiskState arg);
    virtual bool isTopLevelObject()const;

    Ev::ObjectStatus status() const;
    Q_INVOKABLE void setStatus(Ev::ObjectStatus arg);



    // properties, for invokable interface
    Q_INVOKABLE QVariant property(const QByteArray & name)const;
    Q_INVOKABLE bool setProperty(const QByteArray & name,const QVariant & value);


    // to not be moved to trash when removed
    Q_INVOKABLE bool isTemporaryObject()const;
    Q_INVOKABLE void setTemporaryObject(bool );

    // for qml
    QQmlListProperty<EvObject> subObjects();


        // bindings
    Q_SIGNAL void unbindRequest(
            QObject * fromObject,
            const QByteArray & fpName,
            const QByteArray & tpName);


    // variant storage
    QVariant toVariant()const;





Q_SIGNALS:

    void nameChanged(const QString &);
    void descriptionChanged(const QString &);

    void designablePropertiesChanged();
    void attributesChanged();

    void removed(EvObject*,EvObject * parent);

    void objectAdded(EvObject * obj,EvObject * parent);
    void objectRemoved(EvObject * obj,EvObject * parent);
    void objectToBeRemoved(EvObject * obj,EvObject * parent);

    void diskStateChanged(Ev::ObjectDiskState arg);
    void statusChanged(Ev::ObjectStatus arg);

    void modified(EvObject*);


protected:
    void classBegin();
    virtual void finalize();
    virtual void componentComplete();

    virtual void customizePropertiesWrappers(QHash<QString,EvProperty*> & )const;

    void createChildrenContainer(int type);

    void setObject(EvObject * );
    bool renameChild(EvObject *, const QString & name);
    static void bindOjects(EvObject * from,EvObject  * to);

    void connectChild(EvObject*);
    void disconnetChild(EvObject*);
    Q_INVOKABLE void connectDesingableProperties();


protected Q_SLOTS:
    void setModified();


private:

    Q_DISABLE_COPY(EvObject)   
    uint m_id;

    bool m_isLink,m_temporary;
    QString m_description;
    Ev::ObjectDiskState m_diskState;
    Ev::ObjectStatus m_status;
    QList<EvObject*> m_genericChildren;
    QHash<int,EvObjectsContainer*> m_typedChildren;
    EvPropertiesNames m_lastConnectedDesignableProperties;

    friend class EvObjectLink;
    static uint objectsIds;


};

template <typename T>
T *EvObject::create(QObject *parent)
{
    return qobject_cast<T*>(createObject(T::staticTypeId(),parent));
}

template <typename T>
void EvObject::set(T * obj)
{
    setObject(obj);
}


template <typename T>
bool EvObject::add(T * obj, int index)
{
    return addObject(obj,index);
}



template <typename T>
T* EvObject::createAndAdd(const QString & name,int index){
    T * obj = create<T> ();
    if(!obj){
        return NULL;
    }

    obj->rename(name);

    if(addObject(obj,index)){
        return obj;
    }
    else {
        obj->m_temporary = true;
        delete obj;
        return NULL;
    }
}

template <typename T>
int EvObject::count()const{
    return childrenCount(T::staticTypeId());
}

template <typename T>
T *EvObject::child(int index) const
{
    return qobject_cast<T*>(child(T::staticTypeId(),index));
}

template <typename T>
bool EvObject::remove(T * obj)
{
    return removeObject(obj);
}

template <typename T>
T* EvObject::to(){
    return qobject_cast<T*>(this);
}

template <typename T>
bool EvObject::is()const{
    return (this->typeId() == T::staticTypeId());
}

///////////////
///////////////


namespace Ev {
    template <typename T>
    T *createObject(QObject *parent=0){
        return EvObject::create<T>(parent);
    }

    void debugObject(const EvObject * object,int ident = 0);
}



#endif // EVOBJECT_H
