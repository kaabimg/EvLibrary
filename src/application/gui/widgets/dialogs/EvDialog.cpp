#include "EvDialog.h"

#include "EvButton.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QEventLoop>
#include <QApplication>


#include "EvAppSettings.h"

EvDialog::EvDialog(Buttons buttons, QWidget *parent) :
    QWidget(parent)

{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    QPalette palette;
    QWidget * separator;

    static const int labelHeight = 45;

    // sender
    m_sender = new QLabel(this);
    m_sender->setFixedHeight(labelHeight);
    m_sender->setText("Title");
    m_sender->setAlignment(Qt::AlignCenter);

    palette = m_sender->palette();
    palette.setColor(QPalette::Window,evApparenceSettings->grayColor());
    palette.setColor(QPalette::WindowText,evApparenceSettings->ligthColor());
    m_sender->setAutoFillBackground(true);
    m_sender->setPalette(palette);

    mainLayout->addWidget(m_sender);

    separator = new QWidget(this);
    separator->setFixedHeight(3);
    palette = separator->palette();
    palette.setColor(QPalette::Window,evApparenceSettings->primaryColor());
    separator->setAutoFillBackground(true);
    separator->setPalette(palette);
    mainLayout->addWidget(separator);


    // title
    m_title = new QLabel(this);
    m_title->setFixedHeight(labelHeight);
    m_title->setText("Title");
    m_title->setAlignment(Qt::AlignCenter);

    palette = m_title->palette();
    palette.setColor(QPalette::Window,evApparenceSettings->grayColor());
    palette.setColor(QPalette::WindowText,evApparenceSettings->ligthColor());
    m_title->setAutoFillBackground(true);
    m_title->setPalette(palette);

    mainLayout->addWidget(m_title);

    separator = new QWidget(this);
    separator->setFixedHeight(3);
    palette = separator->palette();
    palette.setColor(QPalette::Window,evApparenceSettings->primaryColor());

    separator->setAutoFillBackground(true);
    separator->setPalette(palette);
    mainLayout->addWidget(separator);


    // content
    m_contentLayout = new QVBoxLayout;
    m_contentLayout->setSpacing(0);
    m_contentLayout->setContentsMargins(0,0,0,0);
    mainLayout->addLayout(m_contentLayout);

    // buttons
    mainLayout->addLayout(createButtons(buttons));
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);
    setSender(qApp->applicationName());

}

EvDialog::Button EvDialog::exec()
{
    QEventLoop loop;
    connect(this, SIGNAL(terminated()), &loop, SLOT(quit()));

    show();
    loop.exec();

    close();
    return m_returnStauts;
}

QString EvDialog::title() const
{
    return m_title->text();
}

void EvDialog::addContent(QWidget * widget)
{
    m_contentLayout->addWidget(widget);
}

QString EvDialog::sender() const
{
    return m_sender->text();
}

void EvDialog::setTitle(const QString &arg)
{
    m_title->setText(arg);
}

void EvDialog::setSender(const QString &arg)
{
    m_sender->setText(arg);
}



EvButton *EvDialog::createButton(Button type)
{
    EvButton * button =new EvButton(this);

    button->setRounded(false);
    button->setPaintMode(EvButton::TextOnly);
    button->setFixedHeight(40);
    connect(button,SIGNAL(clicked()),this,SLOT(onButtonClicked()));

    switch (type) {
    case Ok:
        button->setText("Ok");
        break;
    case Apply:
        button->setText("Apply");
        break;
    case Cancel:
        button->setText("Cancel");
        break;
    case Yes:
        button->setText("Yes");
        break;
    case No:
        button->setText("No");
        break;
    default:
        break;
    }


    return button;
}

QHBoxLayout *EvDialog::createButtons(EvDialog::Buttons buttons)
{
    QHBoxLayout * buttonsLayout = new QHBoxLayout;

    if(buttons.testFlag(Cancel)){
        buttonsLayout->addWidget(createButton(Cancel));
    }

    if(buttons.testFlag(Apply)){
        buttonsLayout->addWidget(createButton(Apply));
    }

    if(buttons.testFlag(Ok)){
        buttonsLayout->addWidget(createButton(Ok));
    }


    if(buttons.testFlag(No)){
        buttonsLayout->addWidget(createButton(No));
    }

    if(buttons.testFlag(Yes)){
        buttonsLayout->addWidget(createButton(Yes));
    }

    return buttonsLayout;
}

void EvDialog::onButtonClicked()
{
    EvButton * button = qobject_cast<EvButton*>(QObject::sender());
    if(button->text() ==  "Ok"){
        m_returnStauts = Ok;
    }
    else if (button->text() ==  "Cancel"){
        m_returnStauts = Cancel;
    }
    else if (button->text() ==  "Apply"){
        m_returnStauts = Apply;
    }

    if(button->text() ==  "Yes"){
        m_returnStauts = Yes;
    }
    else if (button->text() ==  "No"){
        m_returnStauts = No;
    }

    Q_EMIT terminated();

}

