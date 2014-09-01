#include "EvIconsfactory.h"
#include "EvObjectsTypes.h"

EvIconsFactory::EvIconsFactory()
{
    registerApplicationIcon(Home,"home.png");
    registerApplicationIcon(Help,"help.png");
    registerApplicationIcon(Edit,"edit.png");
    registerApplicationIcon(Play,"play.png");
    registerApplicationIcon(MiniPlay,"mini_play.png");
    registerApplicationIcon(Stop,"stop.png");
    registerApplicationIcon(Settings,"settings.png");
    registerApplicationIcon(Circuit,"circuit.png");
    registerApplicationIcon(Open,"open.png");
    registerApplicationIcon(Close,"close.png");
    registerApplicationIcon(Add,"add.png");
    registerApplicationIcon(Remove,"remove.png");
    registerApplicationIcon(Clear,"clear.png");
    registerApplicationIcon(Copy,"copy.png");
    registerApplicationIcon(Cut,"cut.png");
    registerApplicationIcon(Paste,"paste.png");
    registerApplicationIcon(Import,"import.png");
    registerApplicationIcon(Export,"export.png");
    registerApplicationIcon(Search,"search.png");
    registerApplicationIcon(UpArrow,"up_arrow.png");
    registerApplicationIcon(DownArrow,"down_arrow.png");
    registerApplicationIcon(LeftArrow,"left_arrow.png");
    registerApplicationIcon(RightArrow,"right_arrow.png");
    registerApplicationIcon(LeftShortArrow,"left_short_arrow.png");
    registerApplicationIcon(RightShortArrow,"right_short_arrow.png");
    registerApplicationIcon(Information,"information.png");
    registerApplicationIcon(Warning,"warning.png");
    registerApplicationIcon(Error,"error.png");
    registerApplicationIcon(Log,"log.png");
    registerApplicationIcon(Lock,"lock.png");
    registerApplicationIcon(Unlock,"unlock.png");
    registerApplicationIcon(Refresh,"refresh.png");
    registerApplicationIcon(Trash,"trash.png");
    registerApplicationIcon(Undo,"undo.png");
    registerApplicationIcon(Redo,"redo.png");

    registerObjectIcon(Ev::Cell,"cell.png");
    registerObjectIcon(Ev::Project,"project.png");
    registerObjectIcon(Ev::State,"state.png");
    registerObjectIcon(Ev::Process,"process.png");
    registerObjectIcon(Ev::Library,"library.png");
    registerObjectIcon(Ev::Schematic,"schematic.png");
    registerObjectIcon(Ev::Parameter,"parameter.png");
    registerObjectIcon(Ev::DeviceFamily,"device_family.png");
    registerObjectIcon(Ev::Corner,"corner.png");
    registerObjectIcon(Ev::Filter,"filter.png");
    registerObjectIcon(Ev::Simulation,"simulation.png");
    registerObjectIcon(Ev::Scenario,"scenario.png");




}


void EvIconsFactory::registerObjectIcon(int type, const QString & name)
{
    registerObjectIcon(type,Light,name);
    registerObjectIcon(type,Dark,name);
    registerObjectIcon(type,Colored,name);
}

void EvIconsFactory::registerApplicationIcon(int type, const QString &name)
{
    registerApplicationIcon(type,Light,name);
    registerApplicationIcon(type,Dark,name);
    registerApplicationIcon(type,Colored,name);
}
void EvIconsFactory::registerApplicationIcon(int type , IconStyle style, const QString & name)
{
    static const QString qrcPath = ":/ressources/icons/";
    QHash<int,QIcon> * hash;

    QString styleFolder ;
    switch (style) {
    case Light:
        styleFolder = "light/";
        hash = & m_applicationIconsLight;
        break;
    case Dark:
        styleFolder = "dark/";
        hash = & m_applicationIconsDark;
        break;
    case Colored:
        styleFolder = "colored/";
        hash = & m_applicationIconsColored;
        break;
    default:
        break;
    }
    styleFolder += "application/";
    hash->insert(type,QIcon(qrcPath+styleFolder+name));
}


void EvIconsFactory::registerObjectIcon(int type, IconStyle style, const QString & name)
{
    static const QString qrcPath = ":/ressources/icons/";
    QHash<int,QIcon> * hash;

    QString styleFolder ;
    switch (style) {
    case Light:
        styleFolder = "light/";
        hash = & m_objectsIconsLight;
        break;
    case Dark:
        styleFolder = "dark/";
        hash = & m_objectsIconsDark;
        break;
    case Colored:
        styleFolder = "colored/";
        hash = & m_objectsIconsColored;
        break;
    default:
        break;
    }
    styleFolder += "spice/";
    hash->insert(type,QIcon(qrcPath+styleFolder+name));

}

QIcon EvIconsFactory::objectIcon(int type, IconStyle style) const
{
    switch (style) {
    case Light:{
        if(m_objectsIconsLight.contains(type))
            return  m_objectsIconsLight[type];
        break;
    }
    case Dark:{
        if(m_objectsIconsDark.contains(type))
            return  m_objectsIconsDark[type];
        break;
    }
    case Colored:{
        if(m_objectsIconsColored.contains(type))
            return  m_objectsIconsColored[type];
        break;
    }
    default:
        break;
    }
    return QIcon();
}


QIcon EvIconsFactory::applicationIcon(int type, IconStyle style) const
{
    switch (style) {
    case Light:{
        if(m_applicationIconsLight.contains(type))
            return m_applicationIconsLight[type];
        break;
    }
    case Dark:{
        if(m_applicationIconsDark.contains(type))
            return  m_applicationIconsDark[type];
        break;
    }
    case Colored:{
        if(m_applicationIconsColored.contains(type))
            return  m_applicationIconsColored[type];
        break;
    }
    default:
        break;
    }
    return QIcon();
}
