#ifndef EVMIMEDATA_H
#define EVMIMEDATA_H
#include <QMimeData>
class EvObjectsContainer;
class EvObject;

class EvMimeData : public QMimeData
{
    Q_OBJECT
public:

    // dynamic property "mode" : "copy"/"cut"/"move"

    EvMimeData();

    QStringList formats()const;
    bool hasFormat(const QString & mimeType)const;


    void setObject(EvObject* );
    void setObjects(const QList<EvObject*>& );
    bool hasObjects()const;
    const EvObjectsContainer *objects()const;

protected:
    QVariant retrieveData(const QString & mimeType, QVariant::Type type) const;

private:
    EvObjectsContainer * m_objects;
};

#endif // EVMIMEDATA_H
