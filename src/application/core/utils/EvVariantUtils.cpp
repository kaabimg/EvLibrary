#include "EvVariantUtils.h"
#include <QFont>
#include <QVariant>
namespace Ev {

QStringList variantListToStringList(const QVariantList &input)
{
    QStringList output;
    foreach (const QVariant & v, input) {
        if(v.type() == QVariant::String){
            output<<v.toString();
        }
    }
    return output;
}

QVariantList stringListToVariantList(const QStringList & input)
{
    QVariantList output;
    foreach (const QString & str, input) {
            output<<str;
    }
    return output;
}

QByteArray variantToString(const QVariant & variant)
{
    switch (variant.type()) {
    case QVariant::Bool:
        return variant.toBool() ? "true" : "false";
        break;
    case QVariant::Int:
        return QByteArray::number(variant.toInt());
        break;
    case QVariant::Double:
        return QByteArray::number(variant.toDouble());
        break;

    case QVariant::String:
        return "\""+variant.toString().toLatin1()+"\"";
        break;
    case QVariant::ByteArray:
        return variant.toByteArray();
        break;

    case QVariant::List:{
        QVariantList list = variant.toList();
        QByteArray data = "[";
        foreach (const QVariant & item, list) {
            QByteArray d = variantToString(item);
            if(!d.isEmpty())
                data +=  d+',';
        }
        if(data.size()>1)
            data[data.size()-1] = ']';
        else
            data += ']';
        return data;
        break;
    }
    case QVariant::StringList: {
        QStringList items = variant.toStringList();
        for(int j=0;j<items.size();++j){
            items[j].prepend("\"");
            items[j].append("\"");
        }
        return "[ "+items.join(",").toLatin1()+" ]";
        break;
    }
    default:
        return "";
        break;
    }
    return "";
}

QString fontToString(const QFont & font)
{
    QString string = font.family();
    string += QString(", bold : ")+(font.bold() ? "yes" : "no");
    string += QString(", italic : ")+(font.italic() ? "yes" : "no");
    string += ", point size : "+QString::number(font.pointSize());
    return string;
}

}
