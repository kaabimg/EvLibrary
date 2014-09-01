#ifndef EVSCHEMATIC_H
#define EVSCHEMATIC_H

#include "../../../application/core/base/EvObject.h"


class EvSchematic : public EvObject
{
    Q_OBJECT

    EV_OBJECT(Design,Schematic,1,0)
    EV_TYPE_LABEL("Schematic")

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

public:
    Q_INVOKABLE explicit EvSchematic(QObject *parent = 0);
    QString filePath() const;

Q_SIGNALS:
    void filePathChanged(const QString & arg);

public Q_SLOTS:
    void setFilePath(const QString & arg);
private:
    QString m_filePath;

};

#endif // EVSCHEMATIC_H
