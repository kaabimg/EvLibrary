#include "EvBinding.h"
#include "EvGlobal.h"

#include <QMetaProperty>
#include "EvPropertyBinding.h"


#define EV_SLOT(a)     qPrintable("1"+a)
#define EV_SIGNAL(a)   qPrintable("2"+a)

namespace EvBindingPrivate {

    inline bool bindProperties(
            QObject * sourceObject,
            const QByteArray &sourcePropertyName,
            QObject * destinationObject,
            const QByteArray &destinationPropertyName
            ) {


        EvPropertyBinding * binding = new EvPropertyBinding(
                    sourceObject,
                    sourcePropertyName,
                    destinationObject,
                    destinationPropertyName);



        if(!binding->isValid){
            qDebug()<<"Faild to bind property ("<<sourceObject<<","<<sourcePropertyName<<") to property ("
                    <<destinationObject<<","<<destinationPropertyName<<")";

            qDebug()<<"Did you forgert to define the  unbindRequest(QByteArray) signal in the destination object ?";
            delete binding;
            return false;
        }


        return true;

    }

    inline bool unbindProperties(
            QObject * sourceObject,
            const QByteArray &sourcePropertyName,
            QObject * destinationObject,
            const QByteArray &destinationPropertyName)
    {

        bool ok = destinationObject->metaObject()->invokeMethod(
                    destinationObject,"unbindRequest",
                    Q_ARG(QObject*,sourceObject),
                    Q_ARG(QByteArray,sourcePropertyName),
                    Q_ARG(QByteArray,destinationPropertyName)

                    );
         if(!ok){
             qDebug()<<"Faild to unbind property ("<<sourceObject<<","<<sourcePropertyName<<") to property ("
                     <<destinationObject<<","<<destinationPropertyName<<")";
             qDebug()<<"Did you forgert to define the  unbindRequest(QByteArray) signal in the destination object ?";

         }

         return ok;
    }

     bool bindFunctions(
            QObject * sourceObject,
            const QByteArray &sourceSignal,
            QObject * destinationObject,
            const QByteArray &destinationSignalOrSlot
            ){
         bool ok = QObject::connect(sourceObject,sourceSignal,destinationObject,destinationSignalOrSlot);

         if(!ok)
             qDebug()<<"Faild to bind signal ("<<sourceObject<<","<<sourceSignal<<") to signal/slot ("
                     <<destinationObject<<","<<destinationSignalOrSlot<<")";

         return ok;
    }


     bool bindPropertyToFunction(
            QObject * sourceObject,
            const QByteArray &sourceProperty,
            QObject * destinationObject,
            const QByteArray &destinationSignalOrSlot
            ){
        bool ok = QObject::connect(sourceObject,
                            Ev::notifySignalSignature(sourceObject,sourceProperty),
                            destinationObject,
                            destinationSignalOrSlot);

        if(!ok)
            qDebug()<<"Faild to bind property ("<<sourceObject<<","<<sourceProperty<<") to signal/slot ("
                    <<destinationObject<<","<<destinationSignalOrSlot<<")";

        return ok;
    }



    bool unbindPropertyToFunction(
            QObject * sourceObject,
            const QByteArray &sourcePropery,
            QObject * destinationObject,
            const QByteArray &destinationSignalOrSlot
            ){
        bool ok = QObject::disconnect(sourceObject,
                            Ev::notifySignalSignature(sourceObject,sourcePropery),
                            destinationObject,
                            destinationSignalOrSlot);

        if(!ok)
            qDebug()<<"Faild to unbind ("<<sourceObject<<","<<sourcePropery<<") to ("
                    <<destinationObject<<","<<destinationSignalOrSlot<<")";

        return ok;
    }

    bool isProperty(const QObject * object,const QByteArray & name){
        return object->metaObject()->indexOfProperty(name) != -1;
    }


}

QByteArray Ev::notifySignalSignature(const QObject * object, const QByteArray &propertyName)
{
    const QMetaObject *  mo = object->metaObject();
    int index = mo->indexOfProperty(propertyName);
    if(index == -1)
        return "";
    QMetaProperty property = mo->property(index);
    return EV_SIGNAL(property.notifySignal().methodSignature());
}



bool Ev::bind(
        QObject * sourceObject,
        const QByteArray &source,
        QObject * destinationObject,
        const QByteArray &destination)
{
    if(EvBindingPrivate::isProperty(sourceObject,source)){
        if(EvBindingPrivate::isProperty(destinationObject,destination)){ // property to property
            return EvBindingPrivate::bindProperties(
                        sourceObject,
                        source,
                        destinationObject,
                        destination
                        );
        }
        else { // property to slot
            return EvBindingPrivate::bindPropertyToFunction(
                        sourceObject,
                        source,
                        destinationObject,
                        destination
                        );
        }
    }
    else { // the source is a signal
        return EvBindingPrivate::bindFunctions(
                    sourceObject,
                    source,
                    destinationObject,
                    destination
                    );
    }
}

bool Ev::unbind(QObject * sourceObject,
        const QByteArray &source,
        QObject * destinationObject,
        const QByteArray &destination)
{
    if(EvBindingPrivate::isProperty(sourceObject,source)){
        if(EvBindingPrivate::isProperty(destinationObject,destination)){ // property to property
            return EvBindingPrivate::bindProperties(
                        sourceObject,
                        source,
                        destinationObject,
                        destination
                        );
        }
        else { // property to slot
            return EvBindingPrivate::bindPropertyToFunction(
                        sourceObject,
                        source,
                        destinationObject,
                        destination
                        );
        }
    }
    else { // the source is a signal
        return EvBindingPrivate::bindFunctions(
                    sourceObject,
                    source,
                    destinationObject,
                    destination
                    );
    }
}


