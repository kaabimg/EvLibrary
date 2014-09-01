#include "EvLibrary.h"

EvLibrary::EvLibrary(QObject * parent) :EvObject(parent){


}

QString EvLibrary::location() const
{
    return m_location;
}


void EvLibrary::setLocation(const QString &arg)
{
    if (m_location != arg) {
        m_location = arg;
        Q_EMIT locationChanged(arg);
    }
}


