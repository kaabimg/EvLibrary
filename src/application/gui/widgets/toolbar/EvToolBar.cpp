#include "EvToolBar.h"
#include <QPainter>
#include <QLinearGradient>
#include <QAction>
#include <QLabel>

#include "EvAppSettings.h"
#include "EvWidget.h"
#include "EvGuiUtils.h"


EvToolBar::EvToolBar(int labelWidth, float labelPointSize,QWidget *parent) :
    QToolBar(parent),m_currentWidget(0)
{     
    setStyleSheet(" QToolButton{color: rgba(255,255,255,200);} QToolButton:hover{background: rgba(255,255,255,40);}");
    setOrientation(Qt::Horizontal);

    m_label = new QLabel(this);
    m_label->setFixedWidth(labelWidth);
    m_label->setAlignment(Qt::AlignCenter);

    QFont font = evApparenceSettings->font();
    font.setPointSizeF(labelPointSize);
    m_label->setFont(font);

    QPalette palette = m_label->palette();
    palette.setColor(m_label->foregroundRole(),evApparenceSettings->ligthColor());
    m_label->setPalette(palette);

    addWidget(m_label);
    addSeparator();

}

void EvToolBar::setCurrentWidget(EvWidget * widget)
{
    if(m_currentWidget == widget)
        return;

    m_currentWidget = widget;

    QList<QAction*> acts = actions();
    for (int i = 2; i < acts.size(); ++i) {//bypass the label and the separator
        removeAction(acts[i]);
        if(acts[i]->isSeparator() && acts[i]->parent() == this){
            acts[i]->deleteLater();
        }
    }

    if(m_currentWidget->behaviorFlags().testFlag(EvWidget::SupportsCopyPaste)){
        addActions(m_currentWidget->clipboardActions());
        addSeparator()->setParent(this);
    }
    if(m_currentWidget->behaviorFlags().testFlag(EvWidget::SupportsUndoRedo)){
        addActions(m_currentWidget->undoRedoActions());
        addSeparator()->setParent(this);
    }

    addActions(m_currentWidget->actions());
    m_label->setText(m_currentWidget->windowTitle());
    Q_EMIT currentWidgetChanged(m_currentWidget);
}


void EvToolBar::setActions(const QList<QAction *> & actions)
{
    for (int i = 0; i < actions.size(); ++i) {
        QWidget * spacer = new QWidget(this);
        spacer->setMinimumWidth(10);
        spacer->setProperty("spacer",true);
        addWidget(spacer);
        addAction(actions[i]);
    }
}



void EvToolBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Ev::paintBarGradient(&painter,rect());
    QToolBar::paintEvent(event);
}
