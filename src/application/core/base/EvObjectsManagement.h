#ifndef EVOBJECTSMANAGEMENT_H
#define EVOBJECTSMANAGEMENT_H

#include <QList>
#include <QSet>
#include <QHash>
#include <QMetaObject>
#include <QtQml>


#include "EvGlobal.h"

class EvObject;



struct EvTypeMetaInfo {
    int typeId;
    QString package;
    QString name;
    QString label;
    QMap<EvVersion,QMetaObject> metaObjects;
};




struct EvObjectsManagement {

    static QHash<int,EvTypeMetaInfo> types;

    static QString typeName(int id);
    static QString typeLabel(int id);
    static int     typeFromName(const QString & name,Qt::CaseSensitivity cs = Qt::CaseInsensitive);

    static EvObject * createObject(int type,const EvVersion & version = EvVersion());

    static void registerType(const EvTypeMetaInfo & );
};


template<typename Type>
inline void mgcRegisterType()
{
    static const QByteArray libraryName("Ev");
    EvVersion version = Type::staticVersion();

    EvTypeMetaInfo info;
    info.typeId = Type::staticTypeId();
    info.name = Type::staticTypeName();
    info.label = Type::staticTypeLabel();
    info.package = libraryName+"."+Type::staticPackageName();
    info.metaObjects.insert(version,Type::staticMetaObject);


    qmlRegisterType<Type>(
                qPrintable(info.package),
                version.majorVersion,
                version.minorVersion,
                qPrintable(info.name)
                );

    EvObjectsManagement::registerType(info);

}



#endif // EVOBJECTSMANAGEMENT_H
