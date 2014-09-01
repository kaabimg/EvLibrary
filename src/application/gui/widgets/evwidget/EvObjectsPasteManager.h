#ifndef EVOBJECTSPASTEMANAGER_H
#define EVOBJECTSPASTEMANAGER_H
class EvWidget;
class EvObject;
class EvCommand;


struct EvObjectsPasteManager
{
    EvObjectsPasteManager(EvWidget * widget);


    void paste();
    void paste(EvObject * object, EvObject * destination);

    EvCommand * createPasteCommand(EvObject * object, EvObject * destination);


private:
    EvWidget * m_widget;

};

#endif // EVOBJECTSPASTEMANAGER_H
