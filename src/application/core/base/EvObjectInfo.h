#ifndef EVOBJECTINFO_H
#define EVOBJECTINFO_H

class EvObject;
#include <QString>

class EvObjectInfo
{
public:
    EvObjectInfo( const EvObject * object);

    QString hierarchicalName()const;
    QStringList hierarchy()const;

private:
    const EvObject * m_object;
};

#endif // EVOBJECTINFO_H
