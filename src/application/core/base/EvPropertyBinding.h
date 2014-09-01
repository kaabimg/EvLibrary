#ifndef EVPROPERTYBINDING_H
#define EVPROPERTYBINDING_H

#include <QObject>
#include <QVariant>
#include "EvBinding.h"

class EvPropertyBinding  : public QObject{
    Q_OBJECT

public:
    EvPropertyBinding(QObject * _from, const QByteArray & _fpName,
                      QObject * _to  , const QByteArray & _tpName):
        QObject(NULL),
        from(_from),
        to(_to),
        fpName(_fpName),
        tpName(_tpName)

    {
        isValid = Ev::bind(
                    from,_fpName,
                    this,SLOT(updateDestinationProperty()))
                &&
                    connect(
                    to,SIGNAL(unbindRequest(QObject*,QByteArray,QByteArray)),
                    this,SLOT(tryToRemove(QObject*,QByteArray,QByteArray)));

        if(!isValid)
            return;

        connect(from,SIGNAL(destroyed()),this,SLOT(deleteLater()));
        connect(to,SIGNAL(destroyed()),this,SLOT(deleteLater()));

    }

public Q_SLOTS:
    void updateDestinationProperty()
    {
         to->setProperty(tpName,from->property(fpName));
    }
    void tryToRemove(
            QObject * _from,
            const QByteArray & _fpName,
            const QByteArray & _tpName)
    {
        if(_from == from && _fpName == fpName && _tpName == tpName)
            deleteLater();
    }

public:
    bool isValid;
    QObject * from  , *to;
    QByteArray fpName,tpName;

};




#endif // EVPROPERTYBINDING_H
