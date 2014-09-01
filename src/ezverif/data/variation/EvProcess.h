#ifndef PROCESS_H_
#define PROCESS_H_

#include "../../../application/core/base/EvObject.h"




class EvProcess : public EvObject
{    
	Q_OBJECT
    EV_OBJECT(Variation,Process,1,0)
    EV_TYPE_LABEL("Process")
    EV_CHILDREN_INTERFACE_2(Library,Parameter)

public:
    Q_INVOKABLE EvProcess(QObject * parent=0);

};

#endif /* PROCESS_H_ */
