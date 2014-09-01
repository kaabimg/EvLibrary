#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "../../../application/core/base/EvObject.h"
#include "EvDeviceFamily.h"



class EvLibrary : public EvObject {

    Q_OBJECT
    EV_OBJECT(Variation,Library,1,0)
    EV_TYPE_LABEL("Library")
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    EV_CHILDREN_INTERFACE_1(DeviceFamily)


public:
    Q_INVOKABLE EvLibrary(QObject * parent=0);

    QString location() const;

public Q_SLOTS:
    void setLocation(const QString & arg);

Q_SIGNALS:
    void locationChanged(const QString &);

private:
    QString m_location;
};

#endif /* LIBRARY_H_ */
