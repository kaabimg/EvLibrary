#include "EvEditWidget.h"

#include "EvAppSettings.h"
#include "EvButton.h"
#include <QHBoxLayout>



EvEditWidget::EvEditWidget(QWidget *widget, QWidget *parent) :
    QWidget(parent),m_widget(widget),m_data(NULL)
{
    QHBoxLayout * layout =new QHBoxLayout(this);

    m_editButton = new EvButton(this);
    m_editButton->setText("Edit ...");
    m_editButton->setIcon(evApp->iconsFactory()->applicationIcon(
                              EvIconsFactory::Edit,EvIconsFactory::Light));

    m_widget->setParent(this);
    m_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    m_editButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);

    layout->addWidget(m_widget);
    layout->addWidget(m_editButton);

    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    connect(m_editButton,SIGNAL(clicked()),this,SIGNAL(editRequest()));
}

void *EvEditWidget::data() const
{
    return m_data;
}

void EvEditWidget::setData(void * data)
{
    m_data = data;
}

QWidget *EvEditWidget::widget() const
{
    return m_widget;
}


