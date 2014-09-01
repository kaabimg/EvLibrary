#ifndef EVSESSIONTYPES_H
#define EVSESSIONTYPES_H


#include "EvObjectsManagement.h"
#include "EvProject.h"
#include "EvSession.h"


namespace EvSessionModule {
void registerTypes () {

    qmlRegisterType<EvProject>("Ev.Session",1,0,"Project");
    qmlRegisterType<EvSession>("Ev.Session",1,0,"Session");
    mgcRegisterType<EvProject>();
    mgcRegisterType<EvSession>();


}
}


#endif // EVSESSIONTYPES_H
