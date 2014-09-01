#ifndef CORRELATION_H_
#define CORRELATION_H_

#include "../../../application/core/base/EvObject.h"
#include "EvParameter.h"


class EvFilter: public EvObject {

	Q_OBJECT
    EV_OBJECT(Variation,Filter,1,0)
    EV_TYPE_LABEL("Filter")
    EV_CHILDREN_INTERFACE_1(Parameter)

public:
    Q_INVOKABLE EvFilter(QObject * parent=0);

public Q_SLOTS:


Q_SIGNALS:

private:

};

#endif /* CORRELATION_H_ */
