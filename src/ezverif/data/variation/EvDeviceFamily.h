#ifndef DEVICEFAMILY_H_
#define DEVICEFAMILY_H_

#include "../../../application/core/base/EvObject.h"



class EvDeviceFamily : public EvObject {

	Q_OBJECT
    EV_OBJECT(Variation,DeviceFamily,1,0)
    EV_TYPE_LABEL("Device family")
    EV_CHILDREN_INTERFACE_2(Mismatch,Corner)

    Q_PROPERTY(QString libraryPath READ libraryPath WRITE setLibraryPath
               NOTIFY libraryPathChanged STORED isStandAlone DESIGNABLE isStandAlone)

public:
    Q_INVOKABLE EvDeviceFamily(QObject * parent=0);

    EvObject * copy()const;

    bool isStandAlone()const;
    QString libraryPath() const;

public Q_SLOTS:
    void setLibraryPath(const QString & arg);

Q_SIGNALS:
    void libraryPathChanged(const QString & arg);

private:
    QString m_libraryPath;

};

#endif /* DEVICEFAMILY_H_ */
