#ifndef EVTOOLBAR_H
#define EVTOOLBAR_H

#include <QToolBar>
class EvWidget;
class QLabel;
class EvToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit EvToolBar(int labelWidth, float labelPointSize, QWidget *parent = 0);

Q_SIGNALS:

public Q_SLOTS:
    void setCurrentWidget(EvWidget*);

Q_SIGNALS:
    void currentWidgetChanged(EvWidget*);

protected:
    void setActions(const QList<QAction*> &actions);
    void paintEvent(QPaintEvent*);


private:
    QLabel * m_label;
    EvWidget* m_currentWidget;
};


#endif // EVTOOLBAR_H
