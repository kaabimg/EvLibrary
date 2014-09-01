#ifndef EVTEXTFILEHANDLER_H
#define EVTEXTFILEHANDLER_H

#include <QDateTime>
#include <QObject>

class EvTextFileHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QByteArray data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QDateTime lastModifed READ lastModifed NOTIFY lastModifedChanged)

public:
    enum State {
        Uninitialized,
        Saved,
        ModifiedInApplication,
        ModifiedOutOfApplication
    };
    Q_ENUMS(State)

    explicit EvTextFileHandler(QObject *parent = 0);

    State state() const;
    QByteArray data() const;
    QString filePath() const;
    QString errorString() const;
    QDateTime lastModifed() const;

Q_SIGNALS:

    void stateChanged(State arg);
    void dataChanged(const QByteArray &  arg);
    void filePathChanged(QString arg);
    void lastModifedChanged(const QDateTime arg);
    void errorOccured();

public Q_SLOTS:

    void setData(const QByteArray& arg);
    void appendData(const QByteArray& arg);
    void chopData(int length);
    void setFilePath(const QString&  arg);

    bool load();
    bool save();

protected:
    void setState(State arg);
    void setLastModifed(const QDateTime & arg);



protected Q_SLOTS:
    void checkModifiedFile(const QString &);

private:

    State m_state;
    QByteArray m_data;
    QString m_filePath;
    QString m_errorString;
    QDateTime m_lastModifed;
};

#endif // EVTEXTFILEHANDLER_H
