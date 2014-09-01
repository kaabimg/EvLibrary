#ifndef EVMACROS_H
#define EVMACROS_H

#include "EvObjectsTypes.h"
#include <QSet>
#include <QString>


#define _OBJECT_TYPE(Package,Type) \
public: \
static int staticTypeId(){return Ev::Type;} \
virtual int typeId()const {return staticTypeId();} \
static const char * staticTypeName(){return #Type;} \
virtual const char * typeName()const {return staticTypeName();} \
static const char * staticPackageName(){return #Package;} \
virtual const char * packageName()const {return staticPackageName();} \
private:


#define _OBJECT_VERSION(majorVersion_,minorVersion_) \
public: \
static EvVersion staticVersion(){ \
    static EvVersion version(majorVersion_,minorVersion_); \
    return version;\
    }\
virtual EvVersion version()const{ \
    return staticVersion(); \
} \
private:



#define EV_OBJECT(Package,Type,majorVersion,minorVerion) \
_OBJECT_TYPE(Package,Type) \
_OBJECT_VERSION(majorVersion,minorVerion)



#define EV_TYPE_LABEL(Label) \
public: \
static QByteArray staticTypeLabel(){\
    return Label;\
}\
virtual QByteArray typeLabel()const{\
    return staticTypeLabel();\
}\
private:


#define _SUPPORTED_CHLIDREN(Types) \
public: \
    EvTypesList supportedChildrenTypes()const{ \
        static EvTypesList types = EvTypesList()<<Types; \
        return types; \
    } \
private:



#define EV_CHILDREN_INTERFACE_1(Type1) \
_SUPPORTED_CHLIDREN(Ev::Type1)

#define EV_CHILDREN_INTERFACE_2(Type1,Type2) \
_SUPPORTED_CHLIDREN(Ev::Type1<<Ev::Type2)

#define EV_CHILDREN_INTERFACE_3(Type1,Type2,Type3) \
_SUPPORTED_CHLIDREN(Ev::Type1<<Ev::Type2<<Ev::Type3)

#define EV_CHILDREN_INTERFACE_4(Type1,Type2,Type3,Type4) \
_SUPPORTED_CHLIDREN(Ev::Type1<<Ev::Type2<<Ev::Type3<<Ev::Type4)

#define EV_CHILDREN_INTERFACE_5(Type1,Type2,Type3,Type4,Type5) \
_SUPPORTED_CHLIDREN(Ev::Type1<<Ev::Type2<<Ev::Type3<<Ev::Type4<<Ev::Type5)

#define EV_CHILDREN_INTERFACE_6(Type1,Type2,Type3,Type4,Type5,Type6) \
_SUPPORTED_CHLIDREN(Ev::Type1<<Ev::Type2<<Ev::Type3<<Ev::Type4<<Ev::Type5<<Ev::Type6)



#define EV_PRIVATE(Class) \
Q_DISABLE_COPY(Class)\
friend class Class##Private;\
Class##Private * d_ptr;


#endif // EVMACROS_H
