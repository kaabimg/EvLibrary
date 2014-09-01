#ifndef EVCOMMANDSINTERFACE_H
#define EVCOMMANDSINTERFACE_H

#include <QObject>
class EvObject;
class QUndoStack;
class EvCommand;

class EvCommandsInterface : public QObject
{
    Q_OBJECT
public:
    explicit EvCommandsInterface(QObject *parent = 0);

    QUndoStack *commandsStack()const;



    EvCommand * createAddObjectCommand(
            EvObject * parentObject,
            int type,
            EvCommand  * parent=0)const;

    EvCommand * createAddObjectCommand(
            EvObject * parentObject,
            EvObject * object,
            EvCommand  * parent=0)const;

    EvCommand * createUpdateObjectCommand(EvObject * parent,EvObject * newValue)const;

    EvCommand * createRemoveObjectCommand(EvObject * object,EvCommand  * parent=0)const;

    EvCommand * createSetObjectPropertyCommand(
                EvObject* object,
                const QByteArray & propertyName,
                const QVariant & value,
                EvCommand  * parent=0)const;


public Q_SLOTS:

    void addObject(EvObject * parent,int type);
    void addObject(EvObject * parent,EvObject * object);

    void updateObject(EvObject * object,EvObject * newValue);

    void removeObject(EvObject*object);

    void setObjectProperty(
            EvObject* object,
            const QByteArray & propertyName,
            const QVariant & value);

private:
     QUndoStack * m_commandsStack;

};

#endif // EVCOMMANDSINTERFACE_H
