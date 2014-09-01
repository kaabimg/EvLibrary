#ifndef EVADDOBJECTCOMMAND_H
#define EVADDOBJECTCOMMAND_H

#include "EvCommand.h"

class EvObject;

class EvAddObjectCommand : public EvCommand
{

public:
    explicit EvAddObjectCommand(EvObject *parentObject ,int type,EvCommand  * parent=0);
    explicit EvAddObjectCommand(EvObject *parentObject ,EvObject * object,EvCommand  * parent=0);


    ~EvAddObjectCommand();

    bool isValid()const;

    void execRedo();
    void execUndo();

private:

   EvObject * m_parent;
   EvObject * m_object;
   int m_type;
   bool m_removed;



};

#endif // EVADDOBJECTCOMMAND_H
