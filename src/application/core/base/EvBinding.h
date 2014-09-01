#ifndef EVBINDING_H
#define EVBINDING_H
#include <QObject>



/*!
 * Usage:
 *  Property to property
 *
 *     Ev::bind(object1,"propertyName1",object2,"propertyName2");
 *
 *     Ev::unbind(object1,"propertyName1",object2,"propertyName2");
 *
 *     The object2 should have a unbindRequest(QByteArray) signal
 *
 *
 *  Property to function
 *
 *     Ev::bind(object1,"propertyName1",object2,SIGNAL(signalName());
 *     Ev::bind(object1,"propertyName1",object2,SLOT(slotName());
 *
 *     Ev::unbind(object1,"propertyName1",object2,SIGNAL(signalName()));
 *     Ev::unbind(object1,"propertyName1",object2,SLOT(slotName()));
 *
 *  Signal to function
 *
 *     Ev::bind(object1,SIGNAL(signalName1()),object2,SIGNAL(signalName2());
 *     Ev::bind(object1,SIGNAL(signalName()),object2,SLOT(slotName());
 *
 *     Ev::unbind(object1,SIGNAL(signalName1()),object2,SIGNAL(signalName2());
 *     Ev::unbind(object1,SIGNAL(signalName()),object2,SLOT(slotName());
 *
*/




namespace Ev {

    QByteArray notifySignalSignature(const QObject * ,const QByteArray & propertyName);

    bool bind(
            QObject* sourceObject,
            const QByteArray & sourceMember,
            QObject*destinationObject,
            const QByteArray & destinationMember
            );
    bool unbind(
            QObject* sourceObject,
            const QByteArray & sourceMember,
            QObject*destinationObject,
            const QByteArray & destinationMember
            );

}

#endif // EVBINDING_H
