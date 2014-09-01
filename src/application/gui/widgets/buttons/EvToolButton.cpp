#include "EvToolButton.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QApplication>
#include "EvAppSettings.h"

EvToolButton::EvToolButton(int number, QWidget *parent)
    : QToolButton(parent),
     m_number(QString::number(number)),
     m_isAnimated(false),m_hover(false)
{
    setFocusPolicy(Qt::NoFocus);
    setCheckable(true);
    setMouseTracking(true);
    setFont(evApparenceSettings->buttonsFont());
    m_animationColor = evApparenceSettings->secondaryColor();
}
QSize EvToolButton::sizeHint() const
{
    ensurePolished();
    QSize s = fontMetrics().size(Qt::TextSingleLine, text());
    s *= 1.1;
    s.rwidth() += 26;
    s.rheight() += 4;
    return s.expandedTo(QApplication::globalStrut());
}


float EvToolButton::roundness()
{
    static const float factor = 5;
    return qMin(30.0f,qMax(height()/factor,width()/factor));
}

void EvToolButton::paintEvent(QPaintEvent *)
{
    const QFontMetrics fm = fontMetrics();
    const int baseLine = (height() - fm.height() + 1) / 2 + fm.ascent();
    const int numberWidth = fm.width(m_number);
    QPainter p(this);
    p.setRenderHint(QPainter::HighQualityAntialiasing,true);
    QPainterPath path;
    path.addRoundRect(rect(),roundness());
    if(m_isAnimated){
        p.fillPath(path,m_animationColor);
    }
    else {
        p.fillPath(path,evApparenceSettings->darkColor());
        if(m_hover && !isChecked()){
            QColor c = evApparenceSettings->ligthColor();
            c.setAlpha(50);
            p.fillPath(path,c);
        }
    }
    QFont f= font();
    if(isChecked() || m_isAnimated)
    {
        p.setPen(evApparenceSettings->ligthColor());
        f.setPointSizeF(f.pointSizeF()* 1.1);
    }
    else{
        p.setPen(evApparenceSettings->grayColor().lighter(250));
    }

    p.setFont(f);
    p.drawText((20 - numberWidth) / 2, baseLine, m_number);
    int leftPart = 22;
    p.drawText(leftPart, baseLine, fm.elidedText(text(), Qt::ElideRight, width() - leftPart - 1));
}



void EvToolButton::enterEvent(QEvent * e)
{
    m_hover = true;
    QToolButton::enterEvent(e);
}

void EvToolButton::leaveEvent(QEvent * e)
{
    m_hover = false;
    QToolButton::leaveEvent(e);
}

