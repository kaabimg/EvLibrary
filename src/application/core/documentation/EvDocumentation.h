#ifndef EVDOCUMENTATION_H
#define EVDOCUMENTATION_H

#include "EvObject.h"

class EvDocumentation : public EvObject
{
    Q_OBJECT
    EV_OBJECT(Core,Documentation,1,0)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(DocumentationType documentationType READ documentationType WRITE setDocumentationType NOTIFY documentationTypeChanged)
    Q_ENUMS(DocumentationType)

public:
    enum DocumentationType{Html,Video};
    Q_INVOKABLE explicit EvDocumentation(QObject *parent = 0);

    QString filePath() const;
    DocumentationType documentationType() const;

public Q_SLOTS:
    void setFilePath(const QString & arg);
    void setDocumentationType(DocumentationType arg);

Q_SIGNALS:
    void filePathChanged(const QString & arg);
    void documentationTypeChanged(DocumentationType arg);

private:
    QString m_filePath;
    DocumentationType m_documentationType;
};

#endif // EVDOCUMENTATION_H
