#include "EvApplicationSettings.h"


#include "EvApparenceSettings.h"
#include <QSettings>

EvApplicationSettings::EvApplicationSettings(QObject *parent):EvObject(parent)
{
    m_apparenceSettings = new EvApparenceSettings(this);
}


QStringList EvApplicationSettings::pluginsSettingsNames() const
{
    return m_pluginsSettings.keys();
}

QList<EvSettings *> EvApplicationSettings::pluginsSettings() const
{
    return m_pluginsSettings.values();
}

EvSettings *EvApplicationSettings::pluginSettings(const QString &name) const
{
    return m_pluginsSettings.value(name);
}


EvApparenceSettings *EvApplicationSettings::apparenceSettings() const
{
    return m_apparenceSettings;
}

void EvApplicationSettings::registerPluginSettings(const QString &name, EvSettings * settings)
{
    m_pluginsSettings.insert(name,settings);
}

void EvApplicationSettings::load()
{
    //TODO
}

void EvApplicationSettings::save()
{
    //TODO
}
