#include "EvTabBar.h"

#include "EvWidget.h"
#include "EvAppSettings.h"
#include "EvTabElement.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>


struct EvTabBarPrivate {
    Qt::Orientation orientation;
    EvTabLogoElement * logo;
    QBoxLayout *mainLayout,*tabsLayout,*widgetsLayout,*spacerLayout;
    QWidget * spacer;
    QList<EvTabElement*> tabs;
    QColor backgroundColor;
    QColor selectionColor;
    QColor outlineColor;
    QSize tabSize;
    QSize logoSize;
    int maximumSize;
    QFont tabsFont;

};

EvTabBar::EvTabBar(Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    d_ptr(new EvTabBarPrivate)
{
    d_ptr->orientation = orientation;
    d_ptr->maximumSize = -1;
    if(orientation == Qt::Vertical){
        d_ptr->mainLayout = new QVBoxLayout;
        d_ptr->tabsLayout = new QVBoxLayout;
        d_ptr->widgetsLayout = new QVBoxLayout;
        d_ptr->spacerLayout = new QVBoxLayout;
    }
    else {
        d_ptr->mainLayout = new QHBoxLayout;
        d_ptr->tabsLayout = new QHBoxLayout;
        d_ptr->widgetsLayout = new QHBoxLayout;
        d_ptr->spacerLayout = new QHBoxLayout;
    }

    d_ptr->spacer = new QWidget(this);
    d_ptr->spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    d_ptr->spacerLayout->addWidget(d_ptr->spacer);


    d_ptr->mainLayout->setSpacing(0);
    d_ptr->mainLayout->setMargin(0);
    d_ptr->mainLayout->setContentsMargins(0,0,0,0);

    d_ptr->tabsLayout->setSpacing(0);
    d_ptr->tabsLayout->setMargin(0);
    d_ptr->tabsLayout->setContentsMargins(0,0,0,0);

    d_ptr->widgetsLayout->setSpacing(0);
    d_ptr->widgetsLayout->setMargin(0);
    d_ptr->widgetsLayout->setContentsMargins(0,0,0,0);


    d_ptr->spacerLayout->setSpacing(0);
    d_ptr->spacerLayout->setMargin(0);
    d_ptr->spacerLayout->setContentsMargins(0,0,0,0);


    setLayout(d_ptr->mainLayout);

    d_ptr->tabSize = QSize(200,70);
    d_ptr->logoSize = QSize(0,0);
    d_ptr->tabsFont = evApparenceSettings->font();

    d_ptr->logo = new EvTabLogoElement(this);
    d_ptr->mainLayout->insertWidget(0,d_ptr->logo);
    d_ptr->mainLayout->addLayout(d_ptr->tabsLayout);
    d_ptr->mainLayout->addLayout(d_ptr->widgetsLayout);
    d_ptr->mainLayout->addLayout(d_ptr->spacerLayout);

    updateSize();
}

Qt::Orientation EvTabBar::orientation() const
{
    return d_ptr->orientation;
}

int EvTabBar::currentIndex() const
{
    EvTabElement * current = currentTabElement();
    if(current)
        return d_ptr->tabsLayout->indexOf(current);
    return -1;
}



EvWidget *EvTabBar::currentTab() const
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        if(d_ptr->tabs[i]->selected()){

            return d_ptr->tabs[i]->widget();
        }
    }
    return NULL;
}

EvTabElement *EvTabBar::currentTabElement() const
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        if(d_ptr->tabs[i]->selected()){

            return d_ptr->tabs[i];
        }
    }
    return NULL;
}


int EvTabBar::tabsCount() const
{
    return d_ptr->tabs.size();
}


EvTabElement *EvTabBar::createTabElement(EvWidget * widget,int level)
{
    EvTabElement * tabElement = new EvTabElement(widget,this);
    tabElement->setLevel(level);

    d_ptr->tabs<<tabElement;
    tabElement->setPrefferedSize(d_ptr->tabSize);
    tabElement->setSelectionColor(d_ptr->selectionColor);
    tabElement->setOutlineColor(d_ptr->outlineColor);
    tabElement->setFont(d_ptr->tabsFont);
    connect(tabElement,SIGNAL(selected(EvWidget*,bool)),this,SLOT(onTabSelected(EvWidget*,bool)));
    connect(tabElement,SIGNAL(showNextRequest()),this,SLOT(showNextTab()));
    connect(tabElement,SIGNAL(showPreviousRequest()),this,SLOT(showPrevioustab()));
    connect(widget,SIGNAL(showRequest(EvWidget*)),this,SLOT(setCurrentTab(EvWidget*)));
    return tabElement;
}





void EvTabBar::addTab(EvWidget * widget, int level)
{
    EvTabElement * tabElement = createTabElement(widget,level);
    d_ptr->tabsLayout->addWidget(tabElement);
    updateSize();
}

void EvTabBar::insertTab(EvWidget * widget, int position, int level)
{
    EvTabElement * tabElement = createTabElement(widget,level);
    d_ptr->tabsLayout->insertWidget(position,tabElement);
    updateSize();
}

void EvTabBar::removeTab(EvWidget * widget)
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        if(d_ptr->tabs[i]->widget() == widget){
            EvTabElement * tab = d_ptr->tabs.takeAt(i);
            d_ptr->tabsLayout->removeWidget(tab);
            delete tab;
            updateSize();
            return;
        }
    }
}

void EvTabBar::addWidget(QWidget * widget)
{
    d_ptr->widgetsLayout->addWidget(widget);
}

void EvTabBar::insertWidget(QWidget * widget, int position)
{
    d_ptr->widgetsLayout->insertWidget(position,widget);

}

void EvTabBar::removeWidget(EvWidget * widget)
{
    d_ptr->widgetsLayout->removeWidget(widget);
}

void EvTabBar::setCurrentTab(EvWidget * widget)
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        if(d_ptr->tabs[i]->widget() == widget){
            d_ptr->tabs[i]->setSelected(true);
            return ;
        }
    }
}

void EvTabBar::removeHoverIndicator()
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        d_ptr->tabs[i]->fadeOut();
    }
}


void EvTabBar::setCurrentIndex(int index)
{
    if(index > -1 && index < tabsCount()){
        setCurrentTab(qobject_cast<EvTabElement*>(d_ptr->tabsLayout->itemAt(index)->widget())->widget());
        removeHoverIndicator();
    }
}

void EvTabBar::showNextTab()
{

    setCurrentIndex(currentIndex()+1);
}

void EvTabBar::showPrevioustab()
{
    setCurrentIndex(currentIndex()-1);
}

QColor EvTabBar::backgroundColor() const
{
    return d_ptr->backgroundColor;
}

QColor EvTabBar::selectionColor() const
{
    return d_ptr->selectionColor;
}

QColor EvTabBar::outlineColor() const
{
    return d_ptr->outlineColor;
}

QColor EvTabBar::logoBackgroundColor() const
{
    return d_ptr->logo->backgroundColor();
}

QString EvTabBar::logoText() const
{
    return d_ptr->logo->text();
}

QSize EvTabBar::logoSize() const
{
    return d_ptr->logoSize;
}

QSize EvTabBar::tabSize() const
{
    return d_ptr->tabSize;
}

int EvTabBar::maximumSize() const
{
    return d_ptr->maximumSize;
}




void EvTabBar::setBackgroundColor(const QColor &arg)
{
    d_ptr->backgroundColor = arg;
    update();

}

void EvTabBar::setSelectionColor(const QColor & arg)
{
    d_ptr->selectionColor = arg;
    for(int i=0;i<d_ptr->tabs.size();++i)
        d_ptr->tabs[i]->setSelectionColor(arg);
}

void EvTabBar::setOutlineColor(const QColor &arg)
{
    d_ptr->outlineColor = arg;
    for(int i=0;i<d_ptr->tabs.size();++i)
        d_ptr->tabs[i]->setOutlineColor(arg);
}

void EvTabBar::setLogoBackgroundColor(const QColor &arg)
{
    d_ptr->logo->setBackgroundColor(arg);
}

void EvTabBar::setLogoText(const QString &arg)
{
    d_ptr->logo->setText(arg);
}

void EvTabBar::setTabSize(const QSize &arg)
{
    d_ptr->tabSize = arg;
    updateSize();

}

void EvTabBar::setLogoSize(const QSize &arg)
{
    d_ptr->logoSize = arg;
    updateSize();

}

void EvTabBar::setMaximumSize(int arg)
{
    d_ptr->maximumSize = arg;
    updateSize();
}

void EvTabBar::setTabsFont(const QFont &arg)
{
    d_ptr->tabsFont = arg;
    for(int i=0;i<d_ptr->tabs.size();++i)
        d_ptr->tabs[i]->setFont(arg);
    updateSize();
    update();

}

QFont EvTabBar::tabsFont() const
{
    return d_ptr->tabsFont;
}

void EvTabBar::onTabSelected(EvWidget * widget, bool mouseEvent)
{
    for(int i=0;i<d_ptr->tabs.size();++i){
        if(d_ptr->tabs[i]->widget() != widget){
            d_ptr->tabs[i]->setSelected(false);
        }
    }
    Q_EMIT currentIndexChanged(mouseEvent);
    Q_EMIT currentTabChanged(mouseEvent);
    Q_EMIT showRequest(widget);
}

void EvTabBar::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QRect rect  = this->rect();
    painter.fillRect(rect,d_ptr->backgroundColor);
    QWidget::paintEvent(event);
}

int EvTabBar::minimumTabWidth()const
{
    int w=0;
    for(int i=0;i<d_ptr->tabs.size();++i){
        w = qMax(w,d_ptr->tabs[i]->minimumSizeHint().width());
    }
    return w;
}



QPoint EvTabBar::minMaxSizes() const
{
    QPoint size;

    int max = d_ptr->maximumSize<0 ? 10000000 : d_ptr->maximumSize;

    if(d_ptr->orientation == Qt::Vertical){
        size.setX(minimumTabWidth());
        size.setY(max);
    }
    else{
        size.setX(qMin(max,minimumTabWidth()));
        size.setY(max);
    }
    return size;
}


void EvTabBar::updateSize()
{
    QPoint minMax = minMaxSizes();
    if(d_ptr->orientation == Qt::Vertical){
        setMaximumWidth(minMax.y());
        d_ptr->logo->setMinimumWidth(minMax.x());
        d_ptr->logo->setMaximumWidth(minMax.y());
        d_ptr->logo->setFixedHeight(d_ptr->logoSize.height());
        for(int i=0;i<d_ptr->tabs.size();++i){
            d_ptr->tabs[i]->setMinimumWidth(minMax.x());
            d_ptr->tabs[i]->setMaximumWidth(minMax.y());
            d_ptr->tabs[i]->setFixedHeight(d_ptr->tabSize.height());
        }
    }
    else {//horizontal
        setMaximumHeight(minMax.y());
        d_ptr->logo->setFixedWidth(d_ptr->logoSize.width());
        d_ptr->logo->setMinimumHeight(minMax.x());
        d_ptr->logo->setMaximumHeight(minMax.y());
        for(int i=0;i<d_ptr->tabs.size();++i){
            d_ptr->tabs[i]->setFixedWidth(d_ptr->tabSize.width());
            d_ptr->tabs[i]->setMinimumHeight(minMax.x());
            d_ptr->tabs[i]->setMaximumHeight(minMax.y());
        }
    }
}



