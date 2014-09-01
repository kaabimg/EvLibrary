#ifndef EVWIDGETFLAGSINTERFACE_H
#define EVWIDGETFLAGSINTERFACE_H
#include <QObject>


struct EvWidgetFlagsInterface {


    enum BehaviorFlag{
        NoBehaviorFlags       =      0,
        HasSideBarInteractions= 1 << 1,
        HasHideSideBarFeature = 1 << 2,
        HasShowSideBarFeature = 1 << 3,
        SupportsUndoRedo      = 1 << 4,
        SupportsCopyPaste     = 1 << 5

    };

    Q_DECLARE_FLAGS(BehaviorFlags,BehaviorFlag)

    BehaviorFlags behaviorFlags()const{
        return m_behaviorFlags;
    }
    void setBehaviorFlags(BehaviorFlags arg){
        m_behaviorFlags = arg;
    }





protected:
    BehaviorFlags m_behaviorFlags;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(EvWidgetFlagsInterface::BehaviorFlags)

#endif // EVWIDGETFLAGSINTERFACE_H
