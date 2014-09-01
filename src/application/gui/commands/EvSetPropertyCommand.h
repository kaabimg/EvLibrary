#ifndef EVSETPROPERTYCOMMAND_H
#define EVSETPROPERTYCOMMAND_H

#include "EvCommand.h"

#include <QVariant>

class EvObject;

class EvSetPropertyCommand : public EvCommand
{
public:
    explicit EvSetPropertyCommand(
            EvObject *object ,
            const QByteArray & propertyName,
            const QVariant & value,
            EvCommand  * parent=0);

    bool isValid() const;
protected:

    void execUndo();
    void execRedo();

private:
    EvObject * m_object;
    QByteArray m_propetyName;
    QVariant m_oldValue,m_newValue;

};

#endif // EVSETPROPERTYCOMMAND_H
