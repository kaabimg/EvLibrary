#include "EvCommand.h"


EvCommand::EvCommand(QUndoCommand * parent):QUndoCommand(parent){}

void EvCommand::undo()
{
    if(isValid()){
        execUndo();
    }
}

void EvCommand::redo()
{
    if(isValid()){
        execRedo();
    }
}


