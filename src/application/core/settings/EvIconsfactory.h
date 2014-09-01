#ifndef EVICONSFACTORY_H
#define EVICONSFACTORY_H

#include <QIcon>
#include <QHash>

class EvIconsFactory
{
public:
    enum IconStyle {
        Light,
        Dark,
        Colored
    };

    enum ApplicationIconType {
        Home,
        Help,
        Edit,
        Play,
        MiniPlay,
        Stop,
        Settings,
        Circuit,
        Open,
        Close,
        Add,
        Remove,
        Clear,
        Copy,
        Cut,
        Paste,
        Import,
        Export,
        Search,
        LeftArrow,
        RightArrow,
        UpArrow,
        DownArrow,
        LeftShortArrow,
        RightShortArrow,
        Information,
        Warning,
        Error,
        Log,
        Lock,
        Unlock,
        Refresh,
        Trash,
        Undo,
        Redo
    };

    EvIconsFactory();

    QIcon objectIcon(int type,IconStyle)const;
    QIcon applicationIcon(int type,IconStyle)const;
protected:
    void registerObjectIcon(int type,IconStyle,const QString & name);
    void registerApplicationIcon(int type, IconStyle, const QString & name);

    void registerObjectIcon(int type, const QString & name);
    void registerApplicationIcon(int type, const QString & name);

private:
    QHash<int,QIcon> m_objectsIconsLight,m_objectsIconsDark,m_objectsIconsColored;
    QHash<int,QIcon> m_applicationIconsLight,m_applicationIconsDark,m_applicationIconsColored;

};

#endif // EVICONSFACTORY_H
