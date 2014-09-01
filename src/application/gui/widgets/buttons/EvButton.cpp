#include "EvButton.h"
#include <QPainter>
#include <QApplication>

#include "EvAppSettings.h"
#include "EvGuiUtils.h"

EvButton::EvButton(QWidget *parent) :
    QPushButton(parent),m_hover(false)
{

    setFont(evApparenceSettings->buttonsFont());
    setMouseTracking(true);
    setPressedColor(evApparenceSettings->primaryColor());
    setBackgroundColor(evApparenceSettings->darkColor());
    setHoverColor(evApparenceSettings->ligthColor());
    m_hoverColor.setAlpha(50);
    setTextColor(evApparenceSettings->ligthColor());

    setPaintMode(IconAndText);
    setRounded(true);
}

QSize EvButton::sizeHint() const
{
    ensurePolished();
    QSize s = fontMetrics().size(Qt::TextSingleLine, text());
    s *= 1.1;

    s.rheight() += 4;
    s.rwidth() += s.height();
    return s.expandedTo(QApplication::globalStrut());
}

EvButton::PaintMode EvButton::paintMode() const
{
    return m_paintMode;
}

bool EvButton::rounded() const
{
    return m_rounded;
}

QColor EvButton::backgroundColor() const
{
    return m_backgroundColor;
}

QColor EvButton::hoverColor() const
{
    return m_hoverColor;
}

void EvButton::setPaintMode(EvButton::PaintMode arg)
{
    m_paintMode = arg;
}

void EvButton::setRounded(bool arg)
{
    m_rounded = arg;
}

void EvButton::setBackgroundColor(const QColor &arg)
{
    m_backgroundColor = arg;
}

void EvButton::setHoverColor(const QColor &arg)
{
    m_hoverColor = arg;
}

void EvButton::setPressedColor(const QColor &arg)
{
    m_pressedColor = arg;
}

void EvButton::setTextColor(const QColor &arg)
{
    m_textColor = arg;
}

QColor EvButton::pressedColor() const
{
    return m_pressedColor;
}

QColor EvButton::textColor() const
{
    return m_textColor;
}


float EvButton::roundness() const
{
    if(!m_rounded)
        return 0;
    static const float factor = 5;
    return qMin(30.0f,qMax(height()/factor,width()/factor));
}

QRect EvButton::textRect()const
{
    if(m_paintMode == TextOnly){
        return rect();
    }

    if(m_paintMode == IconAndText){
        return rect().adjusted(height()+2,0,0,0);
    }
    return QRect();
}

QPainterPath EvButton::textPath() const
{
    QPainterPath path;
    path.setFillRule( Qt::WindingFill);

    QRect rect = textRect();
    if(m_rounded){
        float roundness = this->roundness();
        path.addRoundRect( rect, roundness );
        path.addRect( QRect(rect.x(),0, roundness,roundness ) );
        path.addRect( QRect( rect.x(),rect.y() , roundness,roundness ) );
    }
    else{
        path.addRect(rect);
    }
    return path.simplified();
}

QPainterPath EvButton::backgroundPath() const
{
    QPainterPath path;
    if(m_rounded){
        path.addRoundRect(rect(),roundness());
    }
    else{
        path.addRect(rect());
    }

    return path;
}

QRect EvButton::iconRect()const
{
    if(m_paintMode == TextOnly){
        return QRect();
    }

    int adjust = qMin(width(),height())/10;

    if(m_paintMode == IconAndText){

        return QRect(0,0,height(),height()).adjusted(adjust,adjust,-adjust,-adjust);
    }

    if(width() > height())
    {
        return QRect((width()-height())/2,0,height(),height()).adjusted(adjust,adjust,-adjust,-adjust);;
    }
    else{
        return QRect((height()-width())/2,0,width(),width()).adjusted(adjust,adjust,-adjust,-adjust);;
    }
}



void EvButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);


    QPainterPath backgroundPath = this->backgroundPath();

    if(isDown() || isChecked()){
        painter.fillPath(backgroundPath,m_pressedColor);
    }
    else{
        painter.fillPath(backgroundPath,m_backgroundColor);
    }

    if(m_hover){       
        painter.fillPath(backgroundPath,m_hoverColor);
    }

    switch (m_paintMode) {
    case TextOnly:{
        const QFontMetrics fm = fontMetrics();
        QRect textRect  = this->textRect();
        painter.setFont(font());
        painter.setPen(m_textColor);
        painter.drawText(textRect,Qt::AlignCenter ,fm.elidedText(text(), Qt::ElideRight, textRect.width()));
        break;
    }
    case IconOnly:{
        QRect iconRect = this->iconRect();
        painter.drawPixmap(iconRect,icon().pixmap(iconRect.size()));
        break;
    }
    case IconAndText:{
        const QFontMetrics fm = fontMetrics();
        QRect textRect  = this->textRect();
        QRect iconRect = this->iconRect();

        painter.drawPixmap(iconRect,icon().pixmap(iconRect.size()));

        painter.setFont(font());

        painter.setPen(m_textColor);
        painter.drawText(textRect,Qt::AlignCenter ,fm.elidedText(text(), Qt::ElideRight, textRect.width()));

        break;
    }
    default:
        break;
    }

}

void EvButton::enterEvent(QEvent * e)
{
    m_hover = true;
    QPushButton::enterEvent(e);
}

void EvButton::leaveEvent(QEvent * e)
{
    m_hover = false;
    QPushButton::leaveEvent(e);
}








