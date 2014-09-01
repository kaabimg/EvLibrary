#ifndef EVOBJECTLINK_H
#define EVOBJECTLINK_H

#include "EvObject.h"

class EvObjectLink : public EvObject
{
    Q_OBJECT
    Q_PROPERTY(EvObject* target READ target)
    Q_PROPERTY(bool isValid READ isValid  NOTIFY isValidChanged)

public:
    explicit EvObjectLink(EvObject * target,QObject *parent = 0);
    EvObject* target() const;
    bool isValid() const;



    EvObject* operator ->()const;

    Q_INVOKABLE virtual EvObject* copy()const;


protected:

    void connectTarget();
    void disconnectTarget();

protected Q_SLOTS:
    void setIsValid(bool arg);
    void onTargetRemoved();

Q_SIGNALS:
    void isValidChanged(bool arg);

private:
    Q_DISABLE_COPY(EvObjectLink)
    EvObject* m_target;
    bool m_isValid;
};

#endif // EVOBJECTLINK_H
