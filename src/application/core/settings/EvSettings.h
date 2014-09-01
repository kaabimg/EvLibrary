#ifndef EVSETTINGS_H
#define EVSETTINGS_H

#include "EvObject.h"
#include <QIcon>


class EvSettings : public EvObject
{
    Q_OBJECT
    Q_PROPERTY(QString presentationName READ presentationName NOTIFY presentationNameChanged)
    Q_PROPERTY(QIcon icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)

public:
    explicit EvSettings(QObject *parent = 0);

    QString presentationName() const;
    QIcon icon() const;
    bool enabled() const;

    virtual void resetToDefault() = 0;

Q_SIGNALS:
    void presentationNameChanged(const QString &);
    void iconChanged(const QIcon& );
    void enabledChanged(bool);

protected:

    void setPresentationName(const QString &);
    void setIcon(const QIcon &);
    void setEnabled(bool);

private:
    QString m_presentationName;
    QIcon m_icon;
    bool m_enabled;

};

#endif // EVSETTINGS_H
