#ifndef EVUSERINTERACTIONSINTERFACE_H
#define EVUSERINTERACTIONSINTERFACE_H



class EvUserInteractionsInterface
{
public:
    EvUserInteractionsInterface(){}
    virtual ~EvUserInteractionsInterface(){}

    virtual void importantInformation(const QString &sender, const QString &content)=0;
    virtual void importantWarning(const QString &sender, const QString &content)=0;
    virtual void importantError(const QString &sender, const QString &content)=0;
    virtual bool yesNoQuestion(const QString &sender, const QString &content)=0;

};

#endif // EVUSERINTERACTIONSINTERFACE_H
