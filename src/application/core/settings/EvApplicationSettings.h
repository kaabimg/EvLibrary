#ifndef EVAPPLICATIONSETTINGS_H
#define EVAPPLICATIONSETTINGS_H

#include "EvObject.h"
#include <QMap>
#include <QSettings>

class EvSettings;
class EvApparenceSettings;
class EvApplicationSettings : public EvObject
{
    Q_OBJECT
    Q_PROPERTY(EvApparenceSettings* apparenceSettings READ apparenceSettings)

public:
    Q_INVOKABLE EvApplicationSettings(QObject * parent = 0);
    EvApparenceSettings* apparenceSettings() const; 
    void registerPluginSettings(const QString & name,EvSettings*);

public Q_SLOTS:

    void load();
    void save();


    QStringList pluginsSettingsNames()const;


    QList<EvSettings *> pluginsSettings()const;
    EvSettings * pluginSettings(const QString & name)const;


private:
    EvApparenceSettings* m_apparenceSettings;
    QMap<QString,EvSettings*> m_pluginsSettings;
    QSettings m_settings;

};

#endif // EVAPPLICATIONSETTINGS_H
