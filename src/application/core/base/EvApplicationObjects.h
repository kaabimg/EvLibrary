#ifndef EVAPPLICATIONOBJECTS_H
#define EVAPPLICATIONOBJECTS_H

#include <QObject>
#include <QHash>
#include <QSet>

class EvObject;

class EvApplicationObjects : public QObject
{
    Q_OBJECT
public:
    explicit EvApplicationObjects(QObject *parent = 0);


    void addObject(EvObject*);
    void removeObject(EvObject*);
    EvObject * object(uint id)const;

    bool contains(uint id)const;
    bool isPointerValid(const EvObject*)const;

private:
    QHash<uint,EvObject*> m_objectsIds;
    QSet<EvObject*> m_objects ;

};

#endif // EVAPPLICATIONOBJECTS_H
