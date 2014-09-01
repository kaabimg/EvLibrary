#ifndef MISMATCH_H
#define MISMATCH_H

#include "../../../application/core/base/EvObject.h"
#include "../../../application/core/utils/EvSpiceNumber.h"


class EvMismatchItem : public EvObject {

    Q_OBJECT

    EV_OBJECT(Variation,MismatchItem,1,0)
    EV_TYPE_LABEL("Mismatch item")

    Q_PROPERTY(EvSpiceNumber value READ value WRITE setValue NOTIFY valueChanged)
public:

    Q_INVOKABLE EvMismatchItem(EvObject*parent):EvObject(parent),m_value(0){}

    EvSpiceNumber value() const
    {
        return m_value;
    }

public Q_SLOTS:

    void setValue(const EvSpiceNumber& arg)
    {
        if (m_value != arg) {
            m_value = arg;
            Q_EMIT valueChanged(arg);
        }
    }
Q_SIGNALS:
    void valueChanged(const EvSpiceNumber&);

private:
    EvSpiceNumber m_value;

};


class EvMismatch : public EvObject {

    Q_OBJECT
    EV_OBJECT(Variation,Mismatch,1,0)
    EV_TYPE_LABEL("Mismatch")
    EV_CHILDREN_INTERFACE_1(MismatchItem)

public:
    EvMismatch(EvObject*parent):EvObject(parent){}
};

#endif // MISMATCH_H
