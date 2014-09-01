#include "EvParameter.h"
#include "EvParameterValueParser.h"
#include "EvSystem.h"

#include <EvProperty.h>

EvParameter::EvParameter(QObject * parent) :
    EvObject(parent) ,
    m_parameterType(Value),
    m_samplesCount(0),
    m_lotDistribution(UniformDistribution),
    m_devDistribution(UniformDistribution),
    m_nominal(true)
{

}

QString EvParameter::textualValue() const
{
    return m_textualValue;
}


EvSpiceNumber EvParameter::value() const
{
    return m_value;
}

QList<EvSpiceNumber> EvParameter::values() const
{
    return m_values;
}

EvParameter::ParameterType EvParameter::parameterType() const
{
    return m_parameterType;
}

uint EvParameter::samplesCount() const
{
    return m_samplesCount;
}

EvSpiceNumber EvParameter::start() const
{
    return m_start;
}

EvSpiceNumber EvParameter::stop() const
{
    return m_stop;
}

EvSpiceNumber EvParameter::step() const
{
    return m_step;
}

EvSpiceNumber EvParameter::lotTolerance() const
{
    return m_lotTolerance;
}

EvParameter::Distribution EvParameter::lotDistribution() const
{
    return m_lotDistribution;
}

EvSpiceNumber EvParameter::devTolerance() const
{
    return m_devTolerance;
}

EvParameter::Distribution EvParameter::devDistribution() const
{
    return m_devDistribution;
}

EvSpiceNumber EvParameter::nominal() const
{
    return m_nominal;
}

EvSpiceNumber EvParameter::relativeVariation() const
{
    return m_relativeVariation;
}

EvSpiceNumber EvParameter::multiplier() const
{
    return m_multiplier;
}

EvSpiceNumber EvParameter::devXTolerance() const
{
    return m_devXTolerance;
}

QString EvParameter::groupName() const
{
    return m_groupName;
}


bool EvParameter::setTextualValue(const QString &arg)
{
    if (m_textualValue != arg) {            
        if(!EvParameterValueParser::parseAndSet(arg,this)){
            EvSystem system("Parameter "+objectName());
            EvSystem::Message message;
            message << " Failed to set parameter value of"<<this<<" to "<<arg;
            system.error(message);
            return false;
        }
        m_textualValue = arg;
        Q_EMIT textualValueChanged(arg);
        return true;
    }
    return false;
}

void EvParameter::setParamterType(EvParameter::ParameterType arg)
{
    if (m_parameterType != arg) {
        m_parameterType = arg;
        Q_EMIT parameterTypeChanged(arg);
        Q_EMIT designablePropertiesChanged();
    }
}

QString EvParameter::parameterTypeName() const
{
    switch (m_parameterType) {
    case Value:
        return "Value";
    case List:
        return "List";
    case Range:
        return "Range";
    case LotDevMc:
        return "LotDevMc";
    case DistributionMc:
        return "DistributionMc";
    case DevXMc:
        return "DevXMc";
    case LotGroupMc:
        return "LotGroupMc";
    default:
        break;
    }
    Q_ASSERT(false);

    return "";
}
void EvParameter::setValue(const EvSpiceNumber & arg)
{
    if (m_value != arg) {
        m_value = arg;
        Q_EMIT valueChanged(arg);
    }
}


void EvParameter::setValues(const QList<EvSpiceNumber> &arg)
{
    if (m_values != arg) {
        m_values = arg;
        Q_EMIT valuesChanged(arg);
    }
}

void EvParameter::setSamplesCount(uint arg)
{
    if (m_samplesCount != arg) {
        m_samplesCount = arg;
        Q_EMIT samplesCountChanged(arg);
    }
}

void EvParameter::setStart(const EvSpiceNumber & arg)
{
    if (m_start != arg) {
        m_start = arg;
        Q_EMIT startChanged(arg);
    }
}

void EvParameter::setStop(const EvSpiceNumber &arg)
{
    if (m_stop != arg) {
        m_stop = arg;
        Q_EMIT stopChanged(arg);
    }
}

void EvParameter::setStep(const EvSpiceNumber & arg)
{
    if (m_step != arg) {
        m_step = arg;
        Q_EMIT stepChanged(arg);
    }
}

void EvParameter::setLotTolerance(const EvSpiceNumber & arg)
{
    if (m_lotTolerance != arg) {
        m_lotTolerance = arg;
        Q_EMIT lotToleranceChanged(arg);
    }
}

void EvParameter::setlotDistribution(EvParameter::Distribution arg)
{
    if (m_lotDistribution != arg) {
        m_lotDistribution = arg;
        Q_EMIT lotDistributionChanged(arg);
    }
}

void EvParameter::setDevTolerance(const EvSpiceNumber & arg)
{
    if (m_devTolerance != arg) {
        m_devTolerance = arg;
        Q_EMIT devToleranceChanged(arg);
    }
}

void EvParameter::setDevDistribution(EvParameter::Distribution arg)
{
    if (m_devDistribution != arg) {
        m_devDistribution = arg;
        Q_EMIT devDistributionChanged(arg);
    }
}

void EvParameter::setNominal(const EvSpiceNumber & arg)
{
    if (m_nominal != arg) {
        m_nominal = arg;
        Q_EMIT nominalChanged(arg);
    }
}

void EvParameter::setRelativeVariation(const EvSpiceNumber & arg)
{
    if (m_relativeVariation != arg) {
        m_relativeVariation = arg;
        Q_EMIT relativeVariationChanged(arg);
    }
}

void EvParameter::setMultiplier(const EvSpiceNumber & arg)
{
    if (m_multiplier != arg) {
        m_multiplier = arg;
        Q_EMIT multiplierChanged(arg);
    }
}

void EvParameter::setDevXTolerance(const EvSpiceNumber & arg)
{
    if (m_devXTolerance != arg) {
        m_devXTolerance = arg;
        Q_EMIT devXToleranceChanged(arg);
    }
}

void EvParameter::setGroupName(const QString &arg)
{
    if (m_groupName != arg) {
        m_groupName = arg;
        Q_EMIT groupNameChanged(arg);
    }
}

QString EvParameter::buildTextualValue()
{
    switch (parameterType()) {
    case Value:{
        return m_value.toString();
    }
    case List:{
        QStringList list;
        foreach(const EvSpiceNumber & number,m_values){
            list << number.toString();
        }
        return list.join("  ");
    }
    case Range:{
        QString range;
        range +=  "start="+m_start.toString();
        range +=  "  ";
        range +=  "stop="+m_stop.toString();
        range +=  "  ";
        range +=  "step="+m_step.toString();
        return range;
    }
        //TODO : other types
    default:
        break;
    }
    return "";
}

void EvParameter::customizePropertiesWrappers(QHash<QString, EvProperty *> & properties) const
{
    EvObject::customizePropertiesWrappers(properties);
    if(properties.contains("parameterType")){
        properties["parameterType"]->setLabel("Parameter type");
    }
}

void EvParameter::onValueChanged()
{

}

