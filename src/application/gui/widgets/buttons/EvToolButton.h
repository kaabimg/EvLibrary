#ifndef EVTOOLBUTTON_H
#define EVTOOLBUTTON_H

#include <QToolButton>


class EvToolButton : public QToolButton
{
    Q_OBJECT
public:
    EvToolButton(int id, QWidget *parent = 0);
    QSize sizeHint() const;

    void setAnimated(bool animated){
        m_isAnimated = animated;
        update();
    }


protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    float roundness();
private:
    QString m_number;
    bool m_isAnimated,m_hover;
    QColor m_animationColor;
};

#endif // EVTOOLBUTTON_H
