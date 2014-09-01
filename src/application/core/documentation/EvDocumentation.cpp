#include "EvDocumentation.h"

EvDocumentation::EvDocumentation(QObject *parent) :
    EvObject(parent)
{
}

QString EvDocumentation::filePath() const
{
    return m_filePath;
}

EvDocumentation::DocumentationType EvDocumentation::documentationType() const
{
    return m_documentationType;
}

void EvDocumentation::setDocumentationType(EvDocumentation::DocumentationType arg)
{
    if (m_documentationType != arg) {
        m_documentationType = arg;
        Q_EMIT documentationTypeChanged(arg);
    }
}

void EvDocumentation::setFilePath(const QString &arg)
{
    if (m_filePath != arg) {
        m_filePath = arg;
        Q_EMIT filePathChanged(arg);
    }
}
