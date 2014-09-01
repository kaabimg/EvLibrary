#ifndef EVSYSTEM_H
#define EVSYSTEM_H

#include <QDateTime>
#include <QObject>
#include <QCoreApplication>

class EvObject;
class EvVersion;
class SystemPrivate;

class EvSystem : public QObject
{
    Q_OBJECT
public:
    EvSystem(const QString & name = qAppName(),
             QObject * parent=0);

    struct Message{
        QString text;
        Message & operator << (int data);
        Message & operator << (double data);
        Message & operator << (const char * data);
        Message & operator << (const QByteArray & data);
        Message & operator << (const QString & data);
        Message & operator << (const QDateTime & data);
        Message & operator << (const QDate & data);
        Message & operator << (const QTime & data);
        Message & operator << (const EvVersion & data);
        Message & operator << (const EvObject * object);
        operator QString()const;
    };

public Q_SLOTS:
    void log(const QString &);
    void info(const QString &);
    void warn(const QString &);
    void error(const QString &);

    void importantInfo(const QString &);
    void importantWarning(const QString &);
    void importantError(const QString &);
    bool question(const QString &);

    QString env(const QString &)const;

Q_SIGNALS:
    void log(const QString &,const QString &);
    void info(const QString &,const QString &,bool);
    void warn(const QString &,const QString &,bool);
    void error(const QString &,const QString &,bool);

private:
    QString m_name;

};

#endif // EVSYSTEM_H
