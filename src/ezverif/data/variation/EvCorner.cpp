#include "EvCorner.h"

EvCorner::EvCorner(QObject * parent):EvObject(parent) {

}



QString EvCorner::section() const
{
    return m_section;
}

void EvCorner::setSection(const QString &arg)
{
    if (m_section != arg) {
        m_section = arg;
        Q_EMIT sectionChanged(arg);
    }
}

