#ifndef EVPROPERTY_H
#define EVPROPERTY_H

#include "EvObject.h"

/*!
 * Attributes:
 * -Int
 *    min     : int
 *    max     : int
 *    step    : int
 *    suffix  : string
 * -Double :
 *    min     : double
 *    max     : double
 *    step    : double
 *    digits  : double
 *    suffix  : string
 * -Enum
 *    keys
 *
 * -File
 *    dir
 *    filters
 *
 */



class EvProperty : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Core,Property,1,0)
    EV_TYPE_LABEL("Property")
    EV_CHILDREN_INTERFACE_1(Property)

    Q_PROPERTY(EditMode editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly NOTIFY readOnlyChanged)

    Q_ENUMS(Mode)
    Q_ENUMS(EditMode)

public:
    enum Mode{OwnValue,ObjectProperty};
    enum EditMode {
        Unknown,
        Enum,
        Boolean,
        Int,
        Double,
        SpiceNumber,
        String,
        Color,
        Font,
        File,
        Directory,
        Container
    };


    Q_INVOKABLE explicit EvProperty(QObject *parent = 0);
    explicit EvProperty(const QVariant & v, QObject *parent = 0);
    explicit EvProperty(EvObject * watchedObject,const QString & propertyName,EditMode type=Unknown);


    QVariant value() const;
    Mode mode() const;

    EditMode editMode() const;
    QString label() const;
    bool visible() const;
    bool readOnly() const;
    bool enabled() const;


    bool hasSubProperties()const;
    int visibleSubPropertiesCount()const;
    EvProperty * visibleSubProperty(int index)const;
    int visiblePropertyIndex(EvProperty*)const;


Q_SIGNALS:
    void valueChanged();
    void modeChanged(Mode);
    void labelChanged(const QString&);
    void editModeChanged(EditMode);
    void visiblePropertiesChanged();
    void visibleChanged(bool);
    void readOnlyChanged(bool);
    void enabledChanged(bool arg);

public Q_SLOTS:
    void setValue(const QVariant & arg);
    void setEditMode(EditMode arg);
    void setLabel(const QString & arg);
    void setVisible(bool arg);
    void setReadOnly(bool arg);
    void setEnabled(bool arg);

protected:
    void guessType();
    void guessType(int type, int userType);
    void guessUserType(int userType);

    void finalize();
private:
    void setMode(Mode arg);

private:
    bool m_visible;
    EditMode m_propertyType;
    Mode m_mode;
    QString m_label;
    QVariant m_value;
    EvObject * m_watchedObject;
    bool m_readOnly;
    bool m_enabled;
};

#endif // EVPROPERTY_H
