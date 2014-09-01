#ifndef EVPARAMETERVALUEPARSER_H
#define EVPARAMETERVALUEPARSER_H

class EvParameter;

#include <QString>

struct EvParameterValueParser
{
    static bool parseAndSet(const QString & value, EvParameter*parameter);
    static QString textualValueOf(const EvParameter *);
};

#endif // EVPARAMETERVALUEPARSER_H
