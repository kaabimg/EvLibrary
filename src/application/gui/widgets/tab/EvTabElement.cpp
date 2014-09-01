#include "EvTabElement.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>

#include "EvWidget.h"
#include "EvAppSettings.h"

#include <math.h>

EvTabElement::EvTabElement(EvWidget * widget,QWidget *parent) :
    QWidget(parent),
    m_widget(widget),
    m_level(0),
    m_active(true),
    m_selected(false),
    m_fadeValue(0)
{
    setAttribute(Qt::WA_Hover, true);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    m_animator = new QPropertyAnimation(this,"fadeValue",this);






    if(m_widget->supportsProcessing()){

        m_processingAnimation.setInterval(400);
        m_processingAnimation.setSingleShot(false);
        m_processingAnimationDrawIcon = true;
        connect(m_widget,SIGNAL(isProcessingChanged(bool)),this,SLOT(onWidgetProcessingChanged(bool)));
        connect(&m_processingAnimation,SIGNAL(timeout()),this,SLOT(update()));
        onWidgetProcessingChanged(m_widget->isProcessing());

    }

}

EvWidget *EvTabElement::widget() const
{
    return m_widget;
}

int EvTabElement::level() const
{
    return m_level;
}

bool EvTabElement::selected() const
{
    return m_selected;
}

bool EvTabElement::active() const
{
    return m_active;
}

QColor EvTabElement::selectionColor() const
{
    return m_selectionColor;
}

QColor EvTabElement::outlineColor() const
{
    return m_outlineColor;
}

float EvTabElement::fadeValue() const
{
    return m_fadeValue;
}

void EvTabElement::renameTab(const QString &name)
{
    m_widget->rename(name);
    update();
}

QSize EvTabElement::minimumSizeHint() const
{
    QSize size;
    size.setHeight(m_prefferedSize.height());


    int width = m_level * m_prefferedSize.height();
    width    += m_prefferedSize.height() ; // icon
    QFontMetrics fm(font());
    width += fm.width(text()) ; //text



    if(m_widget->supportsProcessing()){
         width +=  m_prefferedSize.height();
    }


    size.setWidth(width);

    return size;
}

void EvTabElement::setPrefferedSize(const QSize &size)
{
    m_prefferedSize = size;
}

QRect EvTabElement::iconRect() const
{
    QRect rect(0,0,height(),height());
    rect.translate(m_level * height(),0);
    adjustRect(rect);
    return rect;
}

QRect EvTabElement::lockStateRect() const
{
    QRect rect(0,0,height(),height());
    rect.translate(width() - height() * 2 ,0);
    adjustRect(rect);
    return rect;
}

QRect EvTabElement::statusRect() const
{
    QRect rect(0,0,height(),height());
    rect.translate(width() - height(),0);
    adjustRect(rect);
    return rect;
}

QRect EvTabElement::textRect() const
{
    QRect rect(0,0,width() - height() ,height());

    if(m_widget->supportsProcessing()){
         rect.adjust(0,0,-height(),0);
    }
    rect.translate(height() +m_level * height(),0);
    return rect;
}

void EvTabElement::adjustRect(QRect &rect, int value) const
{
    rect.adjust(value,value,-value,-value);

}

void EvTabElement::onWidgetProcessingChanged(bool processing)
{
    if(processing){
        m_processingAnimation.start();
    }
    else {
        m_processingAnimation.stop();
    }
}

void EvTabElement::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_F2:{
        if(!m_widget->supportsRename()){
            QWidget::keyPressEvent(event);
            return;
        }
        event->accept();
        EvTabElementRenameLineEdit  * lineEdit= new EvTabElementRenameLineEdit(this);
        lineEdit->show();
        break;
    }
    case Qt::Key_Left:
    case Qt::Key_Up:{
        event->accept();
        Q_EMIT showPreviousRequest();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_Down:{
        event->accept();
        Q_EMIT showNextRequest();
        break;
    }
    case Qt::Key_C:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            Q_EMIT copyRequest(m_widget);
            break;
        }
    }
    case Qt::Key_X:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            Q_EMIT cutRequest(m_widget);
            break;
        }
    }
    case Qt::Key_V:{
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            Q_EMIT pasteRequest(m_widget);
            break;
        }
    }
    case Qt::Key_Delete:{
        Q_EMIT removeRequest(m_widget);
        break;
    }


    default:{
        QWidget::keyPressEvent(event);
        break;
    }
    }

}


void EvTabElement::setLevel(int arg)
{
    if (m_level != arg) {
        m_level = arg;
        Q_EMIT levelChanged(arg);
        update();
    }
}


void EvTabElement::setSelected(bool arg, bool mouseEvent)
{
    if(!m_active)
        return;
    if (m_selected != arg) {
        m_selected = arg;
        update();
        Q_EMIT selectedChanged(arg);
        if(m_selected)
            Q_EMIT selected(m_widget,mouseEvent);
    }
}

void EvTabElement::setSelectionColor(const QColor &arg)
{
    if (m_selectionColor != arg) {
        m_selectionColor = arg;
        update();
        Q_EMIT selectionColorChanged(arg);
    }
}

void EvTabElement::setFadeValue(float arg)
{
    m_fadeValue = arg;
    update();

}

void EvTabElement::setOutlineColor(const QColor &arg)
{
    if (m_outlineColor != arg) {
        m_outlineColor = arg;
        update();
        Q_EMIT outlineColorChanged(arg);
    }
}


QFont EvTabElement::fontFromWidth(int w) const
{
    QFont font = this->font();
    if(m_selected)
        font.setBold(true);
    for(int i=font.pointSize();i>5;--i){
        QFontMetrics metrics(font);
        if(metrics.width(text())<=w)
            return font;
        font.setPointSize(i-1);
    }

    return font;
}



void EvTabElement::fadeIn()
{
    m_animator->stop();
    m_animator->setDuration(80);
    m_animator->setEndValue(40);
    m_animator->start();
}

void EvTabElement::fadeOut()
{
    m_animator->stop();
    m_animator->setDuration(160);
    m_animator->setEndValue(0);
    m_animator->start();
}




void EvTabElement::setActive(bool arg)
{
    if (m_active != arg) {
        m_active = arg;
        update();
        Q_EMIT activeChanged(arg);
    }
}

QString EvTabElement::text() const
{
    return m_widget->windowTitle();
}

void EvTabElement::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect  backgroundRect = rect();

    if(m_outlineColor.isValid()){
        painter.setPen(QPen(QBrush(m_outlineColor),0.1f));
        painter.drawLine(QLineF(backgroundRect.topLeft(),backgroundRect.topRight()));
        painter.drawLine(QLineF(backgroundRect.bottomLeft(),backgroundRect.bottomRight()));
    }


    if (m_selected)
    {       
        painter.save();
        painter.fillRect(backgroundRect, m_selectionColor);
        painter.restore();
    }


    painter.setFont(font());
    painter.setPen(m_selected ? QColor(255, 255, 255, 160) : QColor(0, 0, 0, 110));


    if (m_active)
    {
        painter.setPen(evApparenceSettings->ligthColor());
    }
    else
    {
        painter.setPen(evApparenceSettings->grayColor());
    }
    if (!m_selected && m_active)
    {
        painter.save();
        int value = int(fadeValue());
        painter.fillRect(backgroundRect,  QColor(255, 255, 255, value));
        painter.setPen(QColor(255, 255, 255, value).darker());
        painter.drawLine(backgroundRect.topLeft(), backgroundRect.topRight());
        painter.drawLine(backgroundRect.bottomLeft(), backgroundRect.bottomRight());
        painter.restore();
    }
    if (!m_active)
        painter.setOpacity(0.7);

    QRect iconRect = this->iconRect();
    QPixmap pixmap = m_widget->windowIcon().pixmap(iconRect.size());
    painter.drawPixmap(iconRect,pixmap);


    painter.drawText(textRect(), Qt::AlignLeft | Qt::AlignVCenter, text());


    if(m_widget->supportsProcessing() &&m_widget->isProcessing() ){

        m_processingAnimationDrawIcon = !m_processingAnimationDrawIcon;

        if(m_processingAnimationDrawIcon){
            QRect statusRect = this->statusRect();

            evIconsFactory->applicationIcon(
                EvIconsFactory::Refresh,EvIconsFactory::Light).paint(
                        &painter,
                        statusRect
                        );
        }


    }
}

void EvTabElement::enterEvent(QEvent *)
{
    fadeIn();
}

void EvTabElement::leaveEvent(QEvent *)
{
    fadeOut();
}

void EvTabElement::focusInEvent(QFocusEvent * event)
{
    if(m_active){
        QWidget::focusInEvent(event);
    }
}

void EvTabElement::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    setSelected(true,true);
}



//////////////////////////////////////////

void EvTabLogoElement::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(),m_backgroundColor);
    QFont font  = evApparenceSettings->font();
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(22);
    painter.setFont(font);
    painter.setPen(evApparenceSettings->ligthColor());
    painter.drawText(rect(),Qt::AlignCenter,m_text);
}


EvTabElementRenameLineEdit::EvTabElementRenameLineEdit(EvTabElement *tab):
    QLineEdit(tab)
{
    this->tab = tab;
    setGeometry(tab->rect());
    setFocus();
    setFrame(false);
    setText(tab->widget()->windowTitle());
    selectAll();

}

void EvTabElementRenameLineEdit::focusOutEvent(QFocusEvent * event)
{
    if(event->lostFocus()){
        hide();
        deleteLater();
    }
    else
        QLineEdit::focusOutEvent(event);
}

void EvTabElementRenameLineEdit::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        event->accept();
        tab->renameTab(text());
        hide();
        deleteLater();
        tab->setFocus();
    }
    else if(event->key() == Qt::Key_Escape){
        hide();
        deleteLater();
        tab->setFocus();
    }
    else
        QLineEdit::keyPressEvent(event);
}
