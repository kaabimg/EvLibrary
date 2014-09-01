#ifndef EVCORETYPES_H
#define EVCORETYPES_H


#include "EvObject.h"
#include "EvProperty.h"
#include "EvApplicationDocumentation.h"
#include "EvDocumentation.h"
#include "EvObjectsManagement.h"
#include "EvSpiceNumber.h"

namespace EvCoreModule {


void registerV1Types(){

    qRegisterMetaTypeStreamOperators<EvSpiceNumber>();
    mgcRegisterType<EvObject>();
    mgcRegisterType<EvProperty>();
    mgcRegisterType<EvDocumentation>();
    mgcRegisterType<EvApplicationDocumentation>();

    qmlRegisterType<EvProperty>("Ev.Core",1,0,"Object");
    qmlRegisterType<EvProperty>("Ev.Core",1,0,"Property");

}

void registerTypes () {

    registerV1Types();
}



}


#endif // EVCORETYPES_H
