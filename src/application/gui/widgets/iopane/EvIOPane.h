#ifndef EVIOPANE_H
#define EVIOPANE_H

#include "EvWidget.h"

class EvIOPane : public EvWidget
{
    Q_OBJECT
public:
    EvIOPane(QWidget * parent = 0);
    bool contentChangedOnInit()const;


Q_SIGNALS:
    void contentChanged();

protected:
    void setContentChangedOnInit(bool);

private:
    bool m_contentChangedOnInit;
};

#endif // EVIOPANE_H
