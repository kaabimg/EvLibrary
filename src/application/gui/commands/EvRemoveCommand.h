#ifndef EVREMOVECOMMAND_H
#define EVREMOVECOMMAND_H
#include "EvCommand.h"

class EvObject;

class EvRemoveCommand : public EvCommand
{

public:
    explicit EvRemoveCommand(EvObject * object,EvCommand  * parent=0);
    ~EvRemoveCommand();
    bool isValid() const;

protected:
    void execUndo();
    void execRedo();

private:
    EvObject * m_object;
    EvObject * m_parent;
    int m_oldIndex;
    bool m_removed;

};

#endif // EVREMOVECOMMAND_H
