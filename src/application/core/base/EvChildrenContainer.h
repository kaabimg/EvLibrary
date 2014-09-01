#ifndef EVCHILDRENCONTAINER_H
#define EVCHILDRENCONTAINER_H

#include <QList>
#include <QObject>
class EvObject;


/*
struct EvChildrenContainer {

    enum Mode{Property,Container};

    EvChildrenContainer(EvObject *obj,int type);
    void setMode(Mode m){mode = m;}

    int supportedType()const ;
    int size()const;
    int indexOf(const EvObject * obj)const;
    EvObject * childAt(int i)const;

    template <typename T>
    T * childAt(int i)const{
        return qobject_cast<T*>(childAt(i));
    }
    void add(EvObject * obj);
    void remove(EvObject * obj);
    void clear();
    QString generateDefautObjectName()const;
    bool "containsName"(const QString & name)const;

protected:
    void updateFrom(const EvChildrenContainer * another);

private:
    friend class EvObject;
    Mode mode;
    EvObject * object;
    int objectsType;
    QList<EvObject*> objects;
};
*/
#endif // EVCHILDRENCONTAINER_H
