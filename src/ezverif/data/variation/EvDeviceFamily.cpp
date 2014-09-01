#include "EvDeviceFamily.h"
#include "EvLibrary.h"

EvDeviceFamily::EvDeviceFamily(QObject * parent):EvObject(parent) {

}

EvObject *EvDeviceFamily::copy() const
{
    EvObject * copy = EvObject::copy();
    if(!isStandAlone()){
        copy->to<EvDeviceFamily>()->setLibraryPath(
                    parentEvObject()->to<EvLibrary>()->location()
                    );
    }
    return copy;
}

bool EvDeviceFamily::isStandAlone() const
{
    return !parentEvObject() || !parentEvObject()->is<EvLibrary>();
}

QString EvDeviceFamily::libraryPath() const
{
    return m_libraryPath;
}

void EvDeviceFamily::setLibraryPath(const QString &arg)
{
    if (m_libraryPath != arg) {
        m_libraryPath = arg;
        Q_EMIT libraryPathChanged(arg);
    }
}






