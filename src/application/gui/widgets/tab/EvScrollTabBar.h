#ifndef EVSCROLLTABBAR_H
#define EVSCROLLTABBAR_H

#include <QScrollArea>
class EvTabBar;


class EvScrollTabBar : public QScrollArea
{
    Q_OBJECT
public:
    explicit EvScrollTabBar(Qt::Orientation orientation, QWidget *parent = 0);

    EvTabBar * tabBar()const;
protected Q_SLOTS:
    void updateScrollPosition(bool mouseEvent);

private:
    EvTabBar * m_tabBar;

};

#endif // EVSCROLLTABBAR_H
