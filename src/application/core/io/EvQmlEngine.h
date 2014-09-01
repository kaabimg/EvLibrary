#ifndef EVQMLENGINE_H
#define EVQMLENGINE_H
#include <QObject>
#include <QHash>
#include <QQmlEngine>
#include <QQmlComponent>

class EvSystem;

class EvQmlEngine
{
public:
    EvQmlEngine();

    static QQmlEngine * qmlEngine(){return engine;}

    template <typename T>
    T *create(const QString & fileName);

    bool hasErrors()const;
    QString errorString()const;


    void setGlobalObject(const QString & name,QObject * obj);
    void removeGlobalObject(const QString & name);

    void setGlobalProperty(const QString & name , const QVariant & value);
    void removeGlobalProperty(const QString & name);


protected:
    void prepareEngine(QQmlEngine *)const;


private:
    bool m_hasErrors;
    QString m_errorStrings;
    QHash<QString,QObject*> m_globalContextObjects;
    QHash<QString,QVariant> m_globalContextProperties;
    static QQmlEngine * engine;
};



template <typename T>
T * EvQmlEngine::create(const QString & fileName){
    m_errorStrings.clear();
    m_hasErrors = false;

    QQmlComponent component(engine, fileName);

    prepareEngine(engine);

    QObject  * obj = component.create();
    if(obj == NULL){
        m_errorStrings = component.errorString();
        m_hasErrors = true;
        return 0;
    }

    T * t = qobject_cast<T*>(obj);
    if(!t) {
        m_errorStrings = "Unable to cast the root item to ";
        m_errorStrings += T::staticMetaObject.className();
        m_hasErrors = true;
        delete obj;
        return 0;
    }

    return t;
}

#endif // EVQMLENGINE_H
