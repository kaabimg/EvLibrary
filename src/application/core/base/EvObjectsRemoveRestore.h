#ifndef EVOBJECTSREMOVERESTORE_H
#define EVOBJECTSREMOVERESTORE_H

class EvObject;


namespace Ev{

    bool moveObject(EvObject*object, EvObject *newParent);
    bool isObjectValid(const EvObject*object);
}


#endif // EVOBJECTSREMOVERESTORE_H
