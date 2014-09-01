#ifndef EVGLOBAL_H
#define EVGLOBAL_H

#include <QDebug>
#include <QObject>


#include "EvBinding.h"
#include "EvMacros.h"


struct EvVersion{
    uint majorVersion, minorVersion;
    EvVersion():majorVersion(0),minorVersion(0){}
    EvVersion(uint _major, uint _minor):majorVersion(_major),minorVersion(_minor){}

    bool isValid()const{
        return majorVersion>0 && minorVersion > 0;
    }


    bool operator < (const EvVersion & another)const{
        if(majorVersion == another.majorVersion)
            return minorVersion < another.minorVersion;
        return majorVersion < another.majorVersion;
    }

    bool operator > (const EvVersion & another)const{
        if(majorVersion == another.majorVersion)
            return minorVersion > another.minorVersion;
        return majorVersion > another.majorVersion;
    }

    bool operator == (const EvVersion & another)const{
        return ( majorVersion == another.majorVersion
                 && minorVersion == another.minorVersion);
    }


    operator QByteArray ()const{
        QByteArray str;
        str += QByteArray::number(majorVersion);
        str += ".";
        str += QByteArray::number(minorVersion);
        return str;
    }
};




namespace Ev {

enum ObjectDiskState {
    Saved,
    Modified
};


enum ObjectStatus {
    Inactive,
    Loading ,
    Saving,
    Processing
};

Q_ENUMS(ObjectDiskState ObjectStatus)

}





#endif // EVGLOBAL_H
