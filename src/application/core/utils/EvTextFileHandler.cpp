#include "EvTextFileHandler.h"

#include <QFile>
#include <QFileInfo>

EvTextFileHandler::EvTextFileHandler(QObject *parent) :
    QObject(parent),m_state(Uninitialized)
{
}

EvTextFileHandler::State EvTextFileHandler::state() const
{
    return m_state;
}

QByteArray EvTextFileHandler::data() const
{
    return m_data;
}

QString EvTextFileHandler::filePath() const
{
    return m_filePath;
}

QString EvTextFileHandler::errorString() const
{
    return m_errorString;
}

QDateTime EvTextFileHandler::lastModifed() const
{
    return m_lastModifed;
}

void EvTextFileHandler::appendData(const QByteArray &arg)
{
    m_data.append(arg);
    setState(ModifiedInApplication);
}

void EvTextFileHandler::chopData(int length)
{
    m_data.chop(length);
    setState(ModifiedInApplication);
}

void EvTextFileHandler::setLastModifed(const QDateTime &arg)
{
    if (m_lastModifed != arg) {
        m_lastModifed = arg;
        Q_EMIT lastModifedChanged(arg);
    }
}

bool EvTextFileHandler::load()
{
    QFile file(m_filePath);
    if(file.open(QFile::ReadOnly))
    {
        m_errorString = file.errorString();
        Q_EMIT errorOccured();
        return false;
    }

    setData(file.readAll());
    file.close();
    QFileInfo info(m_filePath);
    setLastModifed(info.lastModified());
    setState(Saved);
    return true;
}

bool EvTextFileHandler::save()
{
    QFile file(m_filePath);
    if(file.open(QFile::WriteOnly))
    {
        m_errorString = file.errorString();
        Q_EMIT errorOccured();
        return false;
    }

    if(file.write(m_data) == -1){
        m_errorString = file.errorString();
        Q_EMIT errorOccured();
        return false;
    }
    file.close();
    QFileInfo info(m_filePath);
    setLastModifed(info.lastModified());
    setState(Saved);
    return true;
}

void EvTextFileHandler::setData(const QByteArray& arg)
{
    m_data = arg;
    Q_EMIT dataChanged(arg);

}

void EvTextFileHandler::setFilePath(const QString & arg)
{
    if (m_filePath != arg) {
        m_filePath = arg;
        Q_EMIT filePathChanged(arg);
    }
}

void EvTextFileHandler::setState(EvTextFileHandler::State arg)
{
    if (m_state != arg) {
        m_state = arg;
        Q_EMIT stateChanged(arg);
    }
}

void EvTextFileHandler::checkModifiedFile(const QString & file)
{
    if(m_filePath == file){
        QFileInfo info(m_filePath);
        QDateTime lastModifed = info.lastModified();
        if(lastModifed != m_lastModifed){
            setLastModifed(lastModifed);
            setState(ModifiedOutOfApplication);
        }
    }
}
