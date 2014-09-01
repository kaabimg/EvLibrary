#ifndef EVVARIANTUTILS_H
#define EVVARIANTUTILS_H
#include <QVariant>
#include <QStringList>


namespace Ev
{

QStringList variantListToStringList(const QVariantList & input);
QVariantList stringListToVariantList(const QStringList &);
QByteArray variantToString(const QVariant & );
QString fontToString(const QFont & );

}

#endif // EVVARIANTUTILS_H
