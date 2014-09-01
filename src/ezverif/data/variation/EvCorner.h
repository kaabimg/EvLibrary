#ifndef CORNER_H_
#define CORNER_H_

#include "../../../application/core/base/EvObject.h"


class EvCorner : public EvObject {

	Q_OBJECT

    EV_OBJECT(Variation,Corner,1,0)
    EV_TYPE_LABEL("Corner")

    Q_PROPERTY(QString section READ section WRITE setSection NOTIFY sectionChanged)

public:
    Q_INVOKABLE EvCorner(QObject * parent=0);

public:
    QString section() const;

public Q_SLOTS:
    void setSection(const QString & arg);

Q_SIGNALS:
    void sectionChanged(const QString &);

private:
    QString m_section;
};

#endif /* CORNER_H_ */
