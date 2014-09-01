#ifndef EVCOMMAND_H
#define EVCOMMAND_H

#include <QUndoCommand>

class EvCommand : public QUndoCommand
{    
public:
    explicit EvCommand(QUndoCommand * parent=0);
    void undo();
    void redo();
    virtual bool isValid()const{return true;}


protected:
    virtual void execUndo() = 0;
    virtual void execRedo() = 0;


};



#endif // EVCOMMAND_H
