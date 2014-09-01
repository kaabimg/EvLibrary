#ifndef EVSPICENUMBER_H
#define EVSPICENUMBER_H

#include <QMetaType>
#include <QVariant>




struct EvSpiceNumberData {
    EvSpiceNumberData();
    QMap<int,QString> suffices;
    QMap<int,QString> labels;
};


class EvSpiceNumber
{
public:

    enum Unit {
        Yota    =  24 , // Y
        Zetta   =  21 , // Z
        Exa     =  18 , // E
        Peta    =  15 , // P
        Tera    =  12 , // T
        Giga    =   9 , // G
        Mega    =   6 , // M
        Kilo    =   3 , // k
        Hecto   =   2 , // h
        Deca    =   1 , // da
        None    =   0 , // none
        Deci    = - 1 , // d
        Centi   = - 2 , // c
        Milli   = - 3 , // m
        Micro   = - 6 , // µ
        Nano    = - 9 , // n
        Pico    = -12 , // p
        Femto   = -15 , // f
        Atto    = -18 , // z
        Yocto   = -21   // y
    };

    enum Notation {
        Engineering,
        Scientific,
        Spice
    };


    Q_ENUMS(Unit Notation)

    EvSpiceNumber(double value=0,Unit unit = None);
    EvSpiceNumber(const QString & );
    EvSpiceNumber(const EvSpiceNumber & );


    bool isValid()const;

    void operator = (double);
    void operator = (QString);
    void operator = (const char *);


    void changeUnit(Unit );

    bool operator < (const EvSpiceNumber & another)const;
    bool operator > (const EvSpiceNumber & another)const;
    bool operator == (const EvSpiceNumber & another)const;
    bool operator != (const EvSpiceNumber & another)const;


    static EvSpiceNumber fromString(const QString &);
    QString toString(Notation notation = Spice)const;

    operator QVariant()const;
    static  Unit unitFromSuffix(const QChar &suffix);



private:
    bool m_valid;
    double m_value;
    Unit m_unit;

    friend QDataStream &operator<<(QDataStream &out,const EvSpiceNumber &number);
    friend QDataStream &operator>>(QDataStream &in,EvSpiceNumber &number);
    static EvSpiceNumberData data;
};

Q_DECLARE_METATYPE(EvSpiceNumber)

QDataStream &operator<<(QDataStream &out,const EvSpiceNumber &number);
QDataStream &operator>>(QDataStream &in,EvSpiceNumber &number);

QDebug operator<<(QDebug dbg, const EvSpiceNumber &number);

#endif // EVSPICENUMBER_H
