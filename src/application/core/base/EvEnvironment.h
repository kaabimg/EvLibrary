#ifndef EVENVIRONMENT_H
#define EVENVIRONMENT_H

#include <QObject>
#include <QHash>

class EvEnvironment : public QObject
{
    Q_OBJECT
public:
    explicit EvEnvironment(QObject *parent = 0);
    explicit EvEnvironment(EvEnvironment * parentEnv,QObject *parent = 0);

public Q_SLOTS:
    QString value(const QString & variable)const;
    void insert(const QString & variable,const QString & value);

private:
    EvEnvironment * m_parentEnv;
    QHash<QString,QString> m_variables;

};

#endif // EVENVIRONMENT_H
