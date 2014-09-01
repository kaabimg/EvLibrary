#ifndef EVAPPLICATIONARGUMENTSMANAGER_H
#define EVAPPLICATIONARGUMENTSMANAGER_H


#include <QStringList>
#include <QHash>

struct EvApplicationArgument {
    QStringList options;
    QStringList values;
    QString description;
};

class EvApplicationArgumentsManager
{
public:
    EvApplicationArgumentsManager();

    void parseArguments(const QStringList &);
    bool containsOption(const QString & option)const;
    int optionArgumentsSize(const QString & option);
    QStringList optionArguments(const QString & option)const;
    QStringList options()const;



private:
    QHash<QString,QStringList> m_options;
};

#endif // EVAPPLICATIONARGUMENTSMANAGER_H
