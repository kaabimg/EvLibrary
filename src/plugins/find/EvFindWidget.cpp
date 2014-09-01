#include "EvFindWidget.h"

#include "EvObjectsManagement.h"
#include "EvAppSettings.h"
#include "EvObjectsFinder.h"
#include "EvMainWindow.h"



#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include "EvFindLineEdit.h"

#include "EvFindObjectsList.h"

EvFindWidget::EvFindWidget(QWidget *parent) :
    QWidget(parent)
{
    setMaximumWidth(350);
    setProperty("index",0);

    QHBoxLayout * contentLayout = new QHBoxLayout(this);
    contentLayout->setMargin(0);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(2);

    m_lineEdit = new EvFindLineEdit(this);
    m_lineEdit->setMinimumWidth(300);
    m_icon = new QLabel(this);

    m_icon->setPixmap(
                evIconsFactory->applicationIcon(
                    EvIconsFactory::Search,
                    EvIconsFactory::Light).pixmap(QSize(64,64))
                );
    m_icon->setScaledContents(true);

    m_objectsList = new EvFindObjectsList(this);
    m_objectsList->hide();
    m_objectsList->setWindowFlags(Qt::ToolTip);

    contentLayout->addWidget(m_icon);
    contentLayout->addWidget(m_lineEdit);

    connect(evMainWindow,SIGNAL(resized()),this,SLOT(resizeObjectsList()));
    connect(evMainWindow,SIGNAL(moved()),this,SLOT(resizeObjectsList()));


    connect(m_lineEdit,SIGNAL(focusIn()),this,SLOT(showObjectsList()));
    connect(m_lineEdit,SIGNAL(focusOut()),this,SLOT(onLineEditFocusLost()));
    connect(m_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(parserFindText(QString)));


    connect(m_lineEdit,SIGNAL(upKey()),m_objectsList,SLOT(selectPrevious()));
    connect(m_lineEdit,SIGNAL(downKey()),m_objectsList,SLOT(selectNext()));
    connect(m_lineEdit,SIGNAL(enterKey()),m_objectsList,SLOT(selectCurrentObject()));

    connect(m_objectsList,SIGNAL(objectSelected(EvObject*)),
            this,SLOT(onObjectSelected(EvObject*)));


    connect(this,SIGNAL(showObjectWidgetRequest(EvObject*)),
            evMainWindow,SLOT(showObjectWidget(EvObject*)));
}


void EvFindWidget::resizeObjectsList()
{
    QRect mainGeometry = evMainWindow->geometry();
    int x,y,w,h;

    x = mainGeometry.x()+ geometry().x()+m_icon->width()+2;
    w = m_lineEdit->width();

    h = evMainWindow->temporaryWidgetsHeigth();

    QRect rect = evMainWindow->geometry();
    y = mainGeometry.y() + rect.height() - parentWidget()->height() -  5 - h;
    m_objectsList->setGeometry(QRect(QPoint(x,y),QPoint(x+w,y+h)));
}




EvObjectsFinder::FindData EvFindWidget_parsetText(const QString & text ){

    QString copy =text;
    while(copy.size() && copy[0].isSpace())
        copy.remove(0,1);

    QString type;
    EvObjectsFinder::FindData findData;

    for(int i=0;i<copy.size();++i){
        if(copy[i].isSpace()){
            type = copy.left(i);

            int j = i;
            while(j<copy.size() && copy[j].isSpace()){
                ++j;
            }
            while(j<copy.size() ){
                findData.regexp.append(copy[j]);
                ++j;
            }
        }
    }

    findData.objectType = Ev::Object;

    if(!type.isEmpty()){// may be type specified
        int evType = EvObjectsManagement::typeFromName(type,Qt::CaseInsensitive);
        if(evType != Ev::UnknownType){ // correct type name
            findData.objectType = evType;
        }
        else { // incorrect type, consider the hole text as regexp
            findData.regexp = copy;
        }
    }
    else { // no type specified , consider the hole text as regexp
        findData.regexp = copy;
    }

    return findData;
}





void EvFindWidget::showObjectsList()
{
    resizeObjectsList();
    m_objectsList->setVisible(true);
    m_objectsList->setFindData(EvFindWidget_parsetText(m_lineEdit->text()));
}

void EvFindWidget::hideObjectsList()
{
    m_objectsList->setVisible(false);
}



void EvFindWidget::parserFindText(const QString & text)
{
    m_objectsList->setFindData(EvFindWidget_parsetText(text));

}

void EvFindWidget::onLineEditFocusLost()
{
    if(!m_objectsList->hasFocus())
        hideObjectsList();
}

void EvFindWidget::onObjectSelected(EvObject *object)
{
    m_objectsList->hide();
    m_lineEdit->clearFocus();
    Q_EMIT showObjectWidgetRequest(object);
}

void EvFindWidget::resizeEvent(QResizeEvent * e)
{
    m_icon->setFixedSize(e->size().height(),e->size().height());
    QWidget::resizeEvent(e);


}
