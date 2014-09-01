#include "EvObjectQmlExporter.h"

#include "EvObject.h"

#include <QStringList>

#define NEW_LINE "\n\n"
#define END_LINE "\n"

namespace ExportHelper {


QString indentToString(int i) {
    return QString(i*4,' ');
}

typedef QVariant::Type PropertyType;

struct BasicTypeProperty {
    BasicTypeProperty(const QByteArray & n,PropertyType t):name(n),type(t){}
    QByteArray name;
    PropertyType type;
};

static void writeObjectPackages(
        const EvObject * object,
        QHash<QString,EvVersion> & packages)
{

    if(packages.contains(object->packageName())){
        if(packages[object->packageName()] < object->version()){
            packages[object->packageName()] = object->version();
        }
    }
    else {
        packages[object->packageName()] = object->version();
    }


    for(int index=0;index<object->allChildrenCount();++index){
        writeObjectPackages(object->child(index),packages);
    }

}



static void writeObject(
        const EvObject * object,
        QTextStream & out,
        int i)
{
    out<<indentToString(i)<<object->typeName()<<" { "<<END_LINE;
    EvPropertiesNames properties = object->storedPropertiesNames();
    foreach (const QByteArray & propertyName, properties) {
        QVariant property = object->property(propertyName);
        QByteArray value  = Ev::variantToString(property);
        if(!(value.isEmpty() || value == "\"\"" || value == "[]")){
            out<<indentToString(i+1)<<propertyName<<" : "<<value<<END_LINE;
        }
        else {
            //TODO manage error
        }
    }
    out<<END_LINE;

    for(int index=0;index<object->allChildrenCount();++index){
        writeObject(object->child(index),out,i+1);
    }

    out<<indentToString(i)<<"}"<<END_LINE;
}

}

void EvObjectQmlExporter::exportObject(const EvObject *object, QTextStream &out)
{
    QHash<QString,EvVersion> packages;
    ExportHelper::writeObjectPackages(object,packages);

    foreach (const QString & package, packages.keys()) {
        out << "import Ev."<<package<<" "
            <<packages[package].majorVersion<<"."<<packages[package].minorVersion<<END_LINE;
    }

    ExportHelper::writeObject(object,out,0);


}
