#include "EvParameterValueParser.h"

#include "EvParameter.h"


namespace EvParameterValueParserUtils {

struct Expression {

    enum Type{
        Invalid,
        Value,
        Assignement
    };
    Type type;
    QString name;
    EvSpiceNumber value;

    bool isValid()const{return type != Invalid;}


    Type fromString(const QString & str){

        type = Invalid;
        QStringList values = str.split('=');

        switch (values.size()) {
        case 1:{
            value = EvSpiceNumber(values.first());
            type = Value;
            break;
        }
        case 2:{
            name = values.first();
            value = EvSpiceNumber(values.last());
            type = Assignement;
            break;
        }
        default:
            type = Invalid;
            break;
        }
        return type;
    }
};



bool isListType(const QHash<QString,Expression> & expressions){

    QHash<QString,Expression> ::const_iterator iterator = expressions.constBegin();
    while (iterator != expressions.constEnd())  {
        if(!iterator.key().isEmpty() || !iterator->isValid() ){
            return false;
        }
        ++iterator;
    }
    return true;
}


bool checkTokens(const QHash<QString,Expression> & expressions, const QStringList & tokens){
    foreach(const QString & token, tokens){
        if(!expressions.contains(token)){
            return false;
        }
        if(!expressions[token].isValid()){
            return false;
        }
    }
    return true;
}

bool isRange(const QHash<QString,Expression> & expressions){

    return checkTokens(expressions,
                       QStringList()<<"start"<<"stop"<<"step"
                       );
}

/*
bool isLotDevMc(const QHash<QString,Expression> & expressions){
    return checkTokens(expressions,
                       QStringList()<<"value"
                                    <<"samplesCount"
                                    <<"lotTolerance"
                                    <<"lotDistribution"
                                    <<"devTolerance"
                                    <<"devDistribution"
                       );
}


bool isDistributionMc(const QHash<QString,Expression> & expressions){
    return checkTokens(expressions,
                       QStringList()<<"nominal"
                                    <<"relativeVariation"
                                    <<"multiplier"
                       );
}

bool isDevXMc(const QHash<QString,Expression> & expressions){
    return checkTokens(expressions,
                       QStringList()<<"value"
                                    <<"samplesCount"
                                    <<"lotTolerance"
                                    <<"lotDistribution"
                                    <<"devTolerance"
                                    <<"devDistribution"
                       );
}

bool isLotGroupMc(const QHash<QString,Expression> & expressions){
    return checkTokens(expressions,
                       QStringList()<<"start"<<"stop"<<"step"
                       );
}
*/


}


using namespace EvParameterValueParserUtils;

bool EvParameterValueParser::parseAndSet(const QString & value, EvParameter * parameter)
{
    QString copy = value.trimmed();

    QStringList list = copy.split(' ');

    for(int i=0;i<list.size();++i){
        list[i] = list[i].trimmed();
        if(list[i].isEmpty()){
            list.removeAt(i);
            --i;
        }
    }

    bool invalid = false;

    QHash<QString,Expression> expressions;

    for(int i=0;i<list.size();++i){
        Expression expression;
        if(expression.fromString(list[i]) == Expression::Invalid){
            invalid = true;
            break;
        }
        expressions.insert(expression.name,expression);
    }

    if(invalid) {
        return false;
    }

    if(expressions.size() == 1 ){ // value
        if(expressions.contains("") && expressions[""].value.isValid()){
            parameter->setValue(expressions[""].value);
            return true;
        }
        return false;
    }

    if(isListType(expressions)){
        QList<EvSpiceNumber> values;
        QHash<QString,Expression> ::const_iterator iterator = expressions.constBegin();
        while (iterator != expressions.constEnd())  {
            values << iterator->value;
            ++iterator;
        }
        parameter->setValues(values);
        return true;
    }


    if(isRange(expressions)){
        parameter->setParamterType(EvParameter::Range);
        parameter->setStart(expressions["start"].value);
        parameter->setStop(expressions["stop"].value);
        parameter->setStep(expressions["step"].value);
        return true;
    }


    return false;
}

QString EvParameterValueParser::textualValueOf(const EvParameter * parameter)
{
    //TODO
    QString value;

    switch (parameter->parameterType()) {
    case EvParameter::Value:

        break;
    case EvParameter::List:

        break;
    case EvParameter::Range:

        break;
    case EvParameter::LotDevMc:

        break;
    case EvParameter::DistributionMc:

        break;
    case EvParameter::DevXMc:

        break;
    case EvParameter::LotGroupMc:

        break;
    default:
        break;
    }


    return value;
}
