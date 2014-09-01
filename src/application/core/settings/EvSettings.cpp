#include "EvSettings.h"

EvSettings::EvSettings(QObject *parent) :
    EvObject(parent)
{
}

QString EvSettings::presentationName() const
{
    return m_presentationName;
}

QIcon EvSettings::icon() const
{
    return m_icon;
}

bool EvSettings::enabled() const
{
    return m_enabled;
}

void EvSettings::setPresentationName(const QString & name)
{
    if(name != m_presentationName){
        m_presentationName = name;
        Q_EMIT presentationNameChanged(name);
    }
}

void EvSettings::setIcon(const QIcon & icon)
{
    m_icon = icon;
    Q_EMIT iconChanged(icon);

}

void EvSettings::setEnabled(bool enabled)
{
    if(enabled != m_enabled){
        m_enabled = enabled;
        Q_EMIT enabledChanged(enabled);
    }
}
