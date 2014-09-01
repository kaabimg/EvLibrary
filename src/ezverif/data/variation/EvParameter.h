#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "../../../application/core/base/EvObject.h"

#include "../../../application/core/utils/EvSpiceNumber.h"


class EvParameter: public EvObject {

    Q_OBJECT

    EV_OBJECT(Variation,Parameter,1,0)
    EV_TYPE_LABEL("Parameter")
    Q_PROPERTY(QString textualValue READ textualValue WRITE setTextualValue NOTIFY textualValueChanged STORED true DESIGNABLE true)

    Q_PROPERTY(ParameterType parameterType READ parameterType WRITE setParamterType NOTIFY parameterTypeChanged)

    // Value, LotDevMc, DevXMc,LotGroupMc
    Q_PROPERTY(EvSpiceNumber value READ value WRITE setValue NOTIFY valueChanged DESIGNABLE valueVisible STORED valueVisible)
    bool valueVisible()const{return m_parameterType == Value || m_parameterType == LotDevMc || m_parameterType == DevXMc || m_parameterType == LotGroupMc ;}

    // LotDevMc, DevXMc,LotGroupMc
    Q_PROPERTY(uint samplesCount READ samplesCount WRITE setSamplesCount NOTIFY samplesCountChanged DESIGNABLE samplesCountVisible STORED samplesCountVisible)
    bool samplesCountVisible()const{return m_parameterType == LotDevMc || m_parameterType == DevXMc || m_parameterType == LotGroupMc ;}

    // Values
    Q_PROPERTY(QList<EvSpiceNumber> values READ values WRITE setValues NOTIFY valuesChanged  DESIGNABLE valuesVisible STORED valuesVisible)
    bool valuesVisible()const{return m_parameterType == List;}

    // Range type
    Q_PROPERTY(EvSpiceNumber start READ start WRITE setStart NOTIFY startChanged  DESIGNABLE isRange STORED isRange)
    Q_PROPERTY(EvSpiceNumber stop READ stop WRITE setStop NOTIFY stopChanged  DESIGNABLE isRange STORED isRange)
    Q_PROPERTY(EvSpiceNumber step READ step WRITE setStep NOTIFY stepChanged  DESIGNABLE isRange STORED isRange)
    bool isRange()const{return m_parameterType == Range;}


    // LotDevMc
    Q_PROPERTY(EvSpiceNumber lotTolerance READ lotTolerance WRITE setLotTolerance NOTIFY lotToleranceChanged  DESIGNABLE isLotDevMc STORED isLotDevMc)
    Q_PROPERTY(Distribution lotDistribution READ lotDistribution WRITE setlotDistribution NOTIFY lotDistributionChanged  DESIGNABLE isLotDevMc STORED isLotDevMc)
    Q_PROPERTY(EvSpiceNumber devTolerance READ devTolerance WRITE setDevTolerance NOTIFY devToleranceChanged  DESIGNABLE isLotDevMc STORED isLotDevMc)
    Q_PROPERTY(Distribution devDistribution READ devDistribution WRITE setDevDistribution NOTIFY devDistributionChanged  DESIGNABLE isLotDevMc STORED isLotDevMc)
    bool isLotDevMc()const{return m_parameterType == LotDevMc;}


    // DistributionMc

    Q_PROPERTY(EvSpiceNumber nominal READ nominal WRITE setNominal NOTIFY nominalChanged DESIGNABLE isDistributionMc STORED isDistributionMc)
    Q_PROPERTY(EvSpiceNumber relativeVariation READ relativeVariation WRITE setRelativeVariation NOTIFY relativeVariationChanged DESIGNABLE isDistributionMc STORED isDistributionMc)
    Q_PROPERTY(EvSpiceNumber multiplier READ multiplier WRITE setMultiplier NOTIFY multiplierChanged DESIGNABLE isDistributionMc STORED isDistributionMc)
    bool isDistributionMc()const{return m_parameterType == DistributionMc;}

    // DevXMc

    Q_PROPERTY(EvSpiceNumber devXTolerance READ devXTolerance  WRITE setDevXTolerance  NOTIFY devXToleranceChanged DESIGNABLE isDevXMc STORED isDevXMc)
    bool isDevXMc()const{return m_parameterType == DevXMc;}


    // LotGroupMc

    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged DESIGNABLE isLotGroupMc STORED isLotGroupMc)
    bool isLotGroupMc()const{return m_parameterType == LotGroupMc;}


public:
    enum ParameterType{Value,List,Range,LotDevMc,DistributionMc,DevXMc,LotGroupMc};
    enum Distribution {UniformDistribution,GaussDistribution,UserDefinedDistribution};
    enum Function {UniformFunction,AUniformFunction,GaussFunction,AGaussFunction,LimitFunction};


    Q_ENUMS(ParameterType)
    Q_ENUMS(Distribution)
    Q_ENUMS(Function)


public:
    Q_INVOKABLE EvParameter(QObject * parent=0);


    QString textualValue() const;

    Q_INVOKABLE bool setTextualValue(const QString & arg);

    ParameterType parameterType() const;
    Q_INVOKABLE void setParamterType(ParameterType arg);
    QString parameterTypeName()const;


    EvSpiceNumber value() const;
    Q_INVOKABLE void setValue(const EvSpiceNumber & arg);

    uint samplesCount() const;
    Q_INVOKABLE void setSamplesCount(uint arg);

    QList<EvSpiceNumber> values() const;
    Q_INVOKABLE void setValues(const QList<EvSpiceNumber> & arg);

    EvSpiceNumber start() const;
    Q_INVOKABLE void setStart(const EvSpiceNumber & arg);

    EvSpiceNumber stop() const;
    Q_INVOKABLE void setStop(const EvSpiceNumber & arg);

    EvSpiceNumber step() const;
    Q_INVOKABLE void setStep(const EvSpiceNumber & arg);

    EvSpiceNumber lotTolerance() const;
    Q_INVOKABLE void setLotTolerance(const EvSpiceNumber & arg);

    Distribution lotDistribution() const;
    Q_INVOKABLE void setlotDistribution(Distribution arg);

    EvSpiceNumber devTolerance() const;
    Q_INVOKABLE void setDevTolerance(const EvSpiceNumber & arg);

    Distribution devDistribution() const;
    Q_INVOKABLE void setDevDistribution(Distribution arg);

    EvSpiceNumber nominal() const;
    Q_INVOKABLE void setNominal(const EvSpiceNumber & arg);

    EvSpiceNumber relativeVariation() const;
    Q_INVOKABLE void setRelativeVariation(const EvSpiceNumber & arg);

    EvSpiceNumber multiplier() const;
    Q_INVOKABLE void setMultiplier(const EvSpiceNumber & arg);

    EvSpiceNumber devXTolerance() const;
    Q_INVOKABLE void setDevXTolerance(const EvSpiceNumber & arg);

    QString groupName() const;
    Q_INVOKABLE void setGroupName(const QString & arg);


    QString buildTextualValue();


protected:
    void customizePropertiesWrappers(QHash<QString, EvProperty *> &) const;
Q_SIGNALS:

    void textualValueChanged(const QString& arg);
    void parameterTypeChanged(ParameterType);
    void valueChanged(const EvSpiceNumber &);
    void samplesCountChanged(uint);
    void valuesChanged(const QList<EvSpiceNumber> & );
    void startChanged(const EvSpiceNumber &);
    void stopChanged(const EvSpiceNumber &);
    void stepChanged(const EvSpiceNumber &);
    void lotToleranceChanged(const EvSpiceNumber &);
    void lotDistributionChanged(Distribution);
    void devToleranceChanged(const EvSpiceNumber &);
    void devDistributionChanged(Distribution);
    void nominalChanged(const EvSpiceNumber &);
    void relativeVariationChanged(const EvSpiceNumber &);
    void multiplierChanged(const EvSpiceNumber &);
    void devXToleranceChanged(const EvSpiceNumber &);
    void groupNameChanged(const QString &);

protected Q_SLOTS:
    void onValueChanged();
private:

    QString m_textualValue;
    ParameterType m_parameterType;
    EvSpiceNumber m_value;
    uint m_samplesCount;
    QList<EvSpiceNumber> m_values;
    EvSpiceNumber m_start;
    EvSpiceNumber m_stop;
    EvSpiceNumber m_step;
    EvSpiceNumber m_lotTolerance;
    Distribution m_lotDistribution;
    EvSpiceNumber m_devTolerance;
    Distribution m_devDistribution;
    EvSpiceNumber m_nominal;
    EvSpiceNumber m_relativeVariation;
    EvSpiceNumber m_multiplier;
    EvSpiceNumber m_devXTolerance;
    QString m_groupName;
};




#endif /* PARAMETER_H_ */
