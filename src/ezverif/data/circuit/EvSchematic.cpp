#include "EvSchematic.h"

EvSchematic::EvSchematic(QObject *parent) :
    EvObject(parent)
{
}

QString EvSchematic::filePath() const
{
    return m_filePath;
}

void EvSchematic::setFilePath(const QString &arg)
{
    if (m_filePath != arg) {
        m_filePath = arg;
        Q_EMIT filePathChanged(arg);
    }
}
