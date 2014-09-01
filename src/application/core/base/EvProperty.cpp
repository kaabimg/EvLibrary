#include "EvProperty.h"

#include <QMetaProperty>
#include "EvSpiceNumber.h"

EvProperty::EvProperty(QObject *parent):
    EvObject(parent),
    m_visible(true),
    m_readOnly(false),
    m_enabled(true)
{
    setMode(OwnValue);
    setEditMode(Unknown);
}

EvProperty::EvProperty(const QVariant &v, QObject *parent):
    EvObject(parent),
    m_visible(true),
    m_value(v),
    m_readOnly(false),
    m_enabled(true)
{
    setMode(OwnValue);
    guessType(m_value.type(),m_value.userType());   
}

EvProperty::EvProperty(
        EvObject *watchedObject,
        const QString &propertyName,
        EvProperty::EditMode type):
    EvObject(watchedObject),
    m_visible(true),
    m_readOnly(false),
    m_enabled(true)
{
    m_watchedObject  =watchedObject;
    setObjectName(propertyName);
    setMode(ObjectProperty);

    if(type == Unknown)
        guessType();
    else
        setEditMode(type);

    Ev::bind(m_watchedObject,propertyName.toLatin1(),this,SIGNAL(valueChanged()));

    int index = m_watchedObject->metaObject()->indexOfProperty(qPrintable(propertyName));

    if(!m_watchedObject->metaObject()->property(index).isWritable()){
        setReadOnly(true);
    }
}


void EvProperty::finalize()
{
    EvObject::finalize();
    EvProperty * property ;
    for(int i=0;i<count<EvProperty>();++i){
        property = child<EvProperty>(i);
        connect(property,SIGNAL(visibleChanged(bool)),this,SIGNAL(visiblePropertiesChanged()));
    }
}



QVariant EvProperty::value() const{
    if(m_mode == OwnValue){
        return m_value;
    }
    else {
        if(editMode() == Enum){
            int value = m_watchedObject->property(qPrintable(objectName())).toInt();
            return attribute("keys").toStringList().at(value);
        }
        return m_watchedObject->property(qPrintable(objectName()));
    }
}

EvProperty::Mode EvProperty::mode() const
{
    return m_mode;
}

EvProperty::EditMode EvProperty::editMode() const
{
    return m_propertyType;
}

QString EvProperty::label() const
{
    return m_label;
}

bool EvProperty::visible() const
{
    return m_visible;
}

bool EvProperty::readOnly() const
{
    return m_readOnly;
}

bool EvProperty::hasSubProperties() const
{
    return count<EvProperty>();
}

int EvProperty::visibleSubPropertiesCount() const
{
    int count = 0;
    int total = this->count<EvProperty>();
    for(int i=0;i < total;++i) {
        if(child<EvProperty>(i)->visible()){
            ++count;
        }
    }
    return count;
}

EvProperty *EvProperty::visibleSubProperty(int index) const
{
    int visibleIndex = 0;
    int total = this->count<EvProperty>();
    for(int i=0;i < total;++i) {
        if(child<EvProperty>(i)->visible()){
            ++visibleIndex;
        }
        if(visibleIndex == index){
            return child<EvProperty>(i);
        }
    }
    return NULL;
}

int EvProperty::visiblePropertyIndex(EvProperty * property) const
{
    int visibleIndex = 0;
    int total = this->count<EvProperty>();
    for(int i=0;i < total;++i) {
        if(child<EvProperty>(i)->visible()){
            ++visibleIndex;
        }
        if(property == child<EvProperty>(i)){
            return visibleIndex;
        }
    }
    return -1;
}

bool EvProperty::enabled() const
{
    return m_enabled;
}

void EvProperty::setVisible(bool arg)
{
    if (m_visible != arg) {
        m_visible = arg;
        Q_EMIT visibleChanged(arg);
    }
}

void EvProperty::setReadOnly(bool arg)
{
    if (m_readOnly != arg) {
        m_readOnly = arg;
        Q_EMIT readOnlyChanged(arg);
    }
}

void EvProperty::setEnabled(bool arg)
{
    if (m_enabled != arg) {
        m_enabled = arg;
        Q_EMIT enabledChanged(arg);
    }
}

void EvProperty::setValue(const QVariant &arg)
{
    if(mode() == OwnValue){
        if (m_value != arg) {
            m_value = arg;
            Q_EMIT valueChanged();
        }
    }
    else {
        m_watchedObject->setProperty(qPrintable(objectName()),arg);
    }
}

void EvProperty::setMode(EvProperty::Mode arg)
{
    if (m_mode != arg) {
        m_mode = arg;
        Q_EMIT modeChanged(arg);
    }
}

void EvProperty::setEditMode(EvProperty::EditMode arg)
{
    if(m_propertyType != arg){
        m_propertyType = arg;
        Q_EMIT editModeChanged(arg);
    }
}

void EvProperty::setLabel(const QString &arg)
{
    if (m_label != arg) {
        m_label = arg;
        Q_EMIT labelChanged(arg);
    }
}



void EvProperty::guessType()
{
    const QMetaObject *  mo = m_watchedObject->metaObject();
    int index = mo->indexOfProperty(qPrintable(objectName()));
    if(index == -1)
        return ;
    QMetaProperty property = mo->property(index);

    if(property.isEnumType()){
       setEditMode(Enum);

       QStringList keys;
       QMetaEnum pEnum = property.enumerator();
       for(int i=0;i<pEnum.keyCount();++i){
           keys << pEnum.key(i);
       }
       setAttribute("keys",keys);
    }
    else {
        guessType(property.type(),property.userType());
    }



}

void EvProperty::guessType(int type,int userType)
{
    switch (type) {
    case QVariant::Bool:
        setEditMode(Boolean);
        break;
    case QVariant::Int:
        setEditMode(Int);
        break;
    case QVariant::UInt:{
        setEditMode(Int);
        setAttribute("min",0);
        break;
    }
    case QVariant::Double:
        setEditMode(Double);
        break;
    case QVariant::String:
        setEditMode(String);
        break;
    case QVariant::Color:
        setEditMode(Color);
        break;
    case QVariant::Font:
        setEditMode(Font);
        break;
    case QVariant::UserType:
        guessUserType(userType);
        break;
    default:
        setEditMode(Unknown);
        break;
    }

}

void EvProperty::guessUserType(int userType)
{
    if(userType == qMetaTypeId<EvSpiceNumber>()){
        setEditMode(SpiceNumber);
        return;
    }
    setEditMode(Unknown);
}


