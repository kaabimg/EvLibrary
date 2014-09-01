#ifndef EVACTIONSHISTORYVIEW_H
#define EVACTIONSHISTORYVIEW_H
#include "EvButton.h"
class QUndoView;
class EvWidget;


class EvActionsHistoryView : public EvButton
{
    Q_OBJECT
public:
    EvActionsHistoryView(QWidget * parent=0);

protected Q_SLOTS:
    void updateViewSize();
    void onActiveWidgetChanged(EvWidget *);

private:
    QUndoView * m_lastActionsView;

};

#endif // EVACTIONSHISTORYVIEW_H
