#include "EvSpiceNumber.h"
#include <math.h>
#include <QVector>
#include <QDebug>


static const int  EvSpiceNumber_powers [] = {
    24, // Y
    21, // Z
    18, // E
    15, // P
    12, // T
    9 , // G
    6 , // M
    3 , // k
    2 , // h
    1 , // da
    0 , // none
    -1 , // d
    -2 , // c
    -3 , // m
    -6 , // µ
    -9 , // n
    -12, // p
    -15, // f
    18, // z
    -21 // y
};





static const QString EvSpiceNumber_sufficesNames [] = {


};


static const QString EvSpiceNumber_suffices [] = {
    "Y",
    "Z",
    "E",
    "P",
    "T",
    "G",
    "M",
    "k",
    "h",
    "da",
    "",
    "d",
    "c",
    "m",
    "µ",
    "n",
    "p",
    "f",
    "z",
    "y"

};


static const  int EvSpiceNumber_minPower = -42;
static const  int EvSpiceNumber_maxPower = 48;

inline QVector<double> EvSpiceNumber_createPowers(){
    QVector<double> powers(EvSpiceNumber_maxPower-EvSpiceNumber_minPower+1);
    for(int i=EvSpiceNumber_minPower;i<=EvSpiceNumber_maxPower;++i){
        powers[i-EvSpiceNumber_minPower] = pow(10,i);
    }
    return powers;
}

static const QVector<double>  EvSpiceNumber_powersValues = EvSpiceNumber_createPowers();



EvSpiceNumberData::EvSpiceNumberData()
{
    suffices[EvSpiceNumber::Yota]    =  "Y";
    suffices[EvSpiceNumber::Zetta]   =  "Z";
    suffices[EvSpiceNumber::Exa]     =  "E";
    suffices[EvSpiceNumber::Peta]    =  "P";
    suffices[EvSpiceNumber::Tera]    =  "T";
    suffices[EvSpiceNumber::Giga]    =  "G";
    suffices[EvSpiceNumber::Mega]    =  "M";
    suffices[EvSpiceNumber::Kilo]    =  "k";
    suffices[EvSpiceNumber::Hecto]   =  "h";
    suffices[EvSpiceNumber::Deca]    =  "da";
    suffices[EvSpiceNumber::None]    =  "";
    suffices[EvSpiceNumber::Deci]    =  "d";
    suffices[EvSpiceNumber::Centi]   =  "c";
    suffices[EvSpiceNumber::Milli]   =  "m";
    suffices[EvSpiceNumber::Micro]   =  "µ";
    suffices[EvSpiceNumber::Nano ]   =  "n";
    suffices[EvSpiceNumber::Pico ]   =  "p";
    suffices[EvSpiceNumber::Femto]   =  "f";
    suffices[EvSpiceNumber::Atto ]   =  "z";
    suffices[EvSpiceNumber::Yocto]   =  "y";



    labels[EvSpiceNumber::Yota]    =  "Yota";
    labels[EvSpiceNumber::Zetta]   =  "Zetta";
    labels[EvSpiceNumber::Exa]     =  "Exa";
    labels[EvSpiceNumber::Peta]    =  "Peta";
    labels[EvSpiceNumber::Tera]    =  "Tera";
    labels[EvSpiceNumber::Giga]    =  "Giga";
    labels[EvSpiceNumber::Mega]    =  "Mega";
    labels[EvSpiceNumber::Kilo]    =  "Kilo";
    labels[EvSpiceNumber::Hecto]   =  "Hecto";
    labels[EvSpiceNumber::Deca]    =  "Deca";
    labels[EvSpiceNumber::None]    =  "None";
    labels[EvSpiceNumber::Deci]    =  "Deci";
    labels[EvSpiceNumber::Centi]   =  "Centi";
    labels[EvSpiceNumber::Milli]   =  "Milli";
    labels[EvSpiceNumber::Micro]   =  "Micro";
    labels[EvSpiceNumber::Nano ]   =  "Nano";
    labels[EvSpiceNumber::Pico ]   =  "Pico";
    labels[EvSpiceNumber::Femto]   =  "Femto";
    labels[EvSpiceNumber::Atto ]   =  "Atto";
    labels[EvSpiceNumber::Yocto]   =  "Yocto";
}




EvSpiceNumber::Unit EvSpiceNumber::unitFromSuffix(const QChar & suffix)
{
    if(suffix.isSymbol() ){
        if(QString(suffix)== "µ")
            return Micro;
        return None;
    }
    switch (suffix.toLatin1()){
        case  'Y' : return Yota;
        case  'Z' : return Zetta;
        case  'E' : return Exa;
        case  'P' : return Peta ;
        case  'T' : return Tera ;
        case  'G' : return Giga;
        case  'M' : return Mega;
        case  'k' : return Kilo;
        case  'h' : return Hecto ;
        case  'a' : return Deca;//must chech 'da' string
        case  'd' : return Deci;
        case  'c' : return Centi;
        case  'm' : return Milli;
        case  'n' : return Nano;
        case  'p' : return Pico;
        case  'f' : return Femto;
        case  'z' : return Atto;
        case  'y' : return Yocto;
    }
    return None;

}

///////////////////////////////////////////////
///////////////////////////////////////////////


EvSpiceNumberData EvSpiceNumber::data;

EvSpiceNumber::EvSpiceNumber(double value, Unit unit):
    m_valid(true),m_value(value),m_unit(unit)
{
}

EvSpiceNumber::EvSpiceNumber(const QString & value)
{
    *this = value;
}

EvSpiceNumber::EvSpiceNumber(const EvSpiceNumber & another)
{
    m_value = another.m_value;
    m_unit = another.m_unit;
    m_valid = another.m_valid;
}

bool EvSpiceNumber::isValid() const
{
    return m_valid;
}

void EvSpiceNumber::operator =(double value)
{
    m_value = value;
    m_unit = None;
    m_valid = true;
}


void EvSpiceNumber::operator =(const char * value)
{
    *this = QString(value);
}

void EvSpiceNumber::operator =(QString number)
{
    m_valid = false;
    m_unit = None;

    number = number.trimmed();
    if(number.isEmpty()){
        return;
    }

    m_unit = unitFromSuffix(number.at(number.size()-1));
    if(m_unit == None){ // may be a classic number notation
        m_value = number.toDouble(&m_valid);
        m_unit = None;
        return ;
    }

    number.chop(1);
    if(number.isEmpty())
        return;

    if(m_unit == Deca){
        //special check, suffix with two characters
        // the last character was 'a'
        // must check that it is preceeded with 'd'

        if(number.at(number.size()-1).toLatin1() != 'd')
            return;
        number.chop(1);

    }
    m_value = number.toDouble(&m_valid);
}


void EvSpiceNumber::changeUnit(EvSpiceNumber::Unit unit)
{
    if(m_valid && unit !=m_unit){

        int myUnit = m_unit;
        while(myUnit < unit){
            myUnit++;
            m_value *= 10;
        }
        while(myUnit > unit){
            myUnit--;
            m_value /= 10;
        }

        m_unit = (Unit)myUnit;
    }
}

bool EvSpiceNumber::operator <(const EvSpiceNumber &another) const
{
    if(m_unit == another.m_unit){
        return m_value < another.m_value;
    }

    int myUnit = m_unit;
    double value = m_value;
    while(myUnit < another.m_unit){
        myUnit++;
        value *= 10;
        if(value < another.m_value)
            return true;
    }
    while(myUnit > another.m_unit){
        myUnit--;
        value /= 10;
        if(value > another.m_value)
            return false;
    }
    return value < another.m_value;
}

bool EvSpiceNumber::operator >(const EvSpiceNumber &another)const
{
    if(m_unit == another.m_unit){
        return m_value > another.m_value;
    }

    int myUnit = m_unit;
    double value = m_value;
    while(myUnit < another.m_unit){
        myUnit++;
        value *= 10;
        if(value < another.m_value)
            return false;
    }
    while(myUnit > another.m_unit){
        myUnit--;
        value /= 10;
        if(value > another.m_value)
            return true;
    }
    return value > another.m_value;
}

bool EvSpiceNumber::operator ==(const EvSpiceNumber &another) const
{
    if(m_unit == another.m_unit){
        return m_value == another.m_value;
    }
    if(m_unit == another.m_unit){
        return m_value < another.m_value;
    }

    int myUnit = m_unit;
    double value = m_value;
    while(myUnit < another.m_unit){
        myUnit++;
        value *= 10;
    }
    while(myUnit > another.m_unit){
        myUnit--;
        value /= 10;

    }
    return value == another.m_value;
}

bool EvSpiceNumber::operator !=(const EvSpiceNumber &another)const
{
    return ! (*this == another);
}

EvSpiceNumber EvSpiceNumber::fromString(const QString & string)
{
    return EvSpiceNumber(string);
}

QString EvSpiceNumber::toString(Notation notation) const
{
    if(!m_valid){
        return "Invalid";
    }


    static const int precision = 6;
    switch (notation) {
    case Engineering:{
        if(m_unit != None){
            return QString::number(m_value,'f',precision);
        }
        EvSpiceNumber me = *this;
        me.changeUnit(None);
        return QString::number(me.m_value,'f',precision);
    }
    case Scientific:{
        if(m_unit != None){
            return QString::number(m_value,'g',precision);
        }
        EvSpiceNumber me = *this;
        me.changeUnit(None);
        return QString::number(me.m_value,'g',precision);
    }
    case Spice:
        return QString::number(m_value,'f',precision)+data.suffices[m_unit];
    default:
        break;
    }
    Q_ASSERT(false);
    return "";
}

EvSpiceNumber::operator QVariant() const
{
    return QVariant::fromValue<EvSpiceNumber>(*this);
}



QDebug operator<<(QDebug dbg, const EvSpiceNumber &number)
{
    dbg.nospace() <<"EvSpiceNumber("<<qPrintable(number.toString())<<")";
    return dbg.maybeSpace();
}




QDataStream &operator<<(QDataStream &out, const EvSpiceNumber &number)
{
    out <<number.m_value<<number.m_unit<<number.m_valid;
    return out;
}


QDataStream &operator>>(QDataStream &in, EvSpiceNumber &number)
{
    in >> number.m_value;
    int unit;
    in >> unit;
    number.m_unit = (EvSpiceNumber::Unit)unit;
    in >> number.m_valid;
    return in;

}
