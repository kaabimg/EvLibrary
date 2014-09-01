#ifndef EVTABBARWIDGET_H
#define EVTABBARWIDGET_H

#include <QWidget>
#include "EvGlobal.h"

class QBoxLayout;
class EvWidget;
class EvTabElement;
class EvTabBarPrivate;

class EvTabBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor)
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor)
    Q_PROPERTY(QColor logoBackgroundColor READ logoBackgroundColor WRITE setLogoBackgroundColor)
    Q_PROPERTY(QString logoText READ logoText WRITE setLogoText)
    Q_PROPERTY(QSize tabSize READ tabSize WRITE setTabSize)
    Q_PROPERTY(QSize logoSize READ tabSize WRITE setLogoSize)
    Q_PROPERTY(int maximumSize READ maximumSize WRITE setMaximumSize)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(EvWidget* currentTab READ currentTab WRITE setCurrentTab NOTIFY currentTabChanged)
    Q_PROPERTY(QFont tabsFont READ tabsFont WRITE setTabsFont)

public:
    explicit EvTabBar(Qt::Orientation orientation,QWidget *parent = 0);
    Qt::Orientation orientation()const;

    int currentIndex() const;
    EvWidget *currentTab()const;
    int tabsCount() const ;

    QColor backgroundColor() const;
    QColor selectionColor() const;
    QColor outlineColor() const;

    QColor logoBackgroundColor() const;
    QString logoText() const;
    QSize logoSize()const;
    QSize tabSize() const;
    int maximumSize() const;
    QFont tabsFont() const;

Q_SIGNALS:

    void showRequest(EvWidget*);
    void currentIndexChanged(bool mouseEvent);
    void currentTabChanged(bool mouseEvent);

public Q_SLOTS:


    void addTab(EvWidget *,int level = 0);
    void insertTab(EvWidget *,int position,int level = 0);
    void removeTab(EvWidget *);

    void addWidget(QWidget * );
    void insertWidget(QWidget * ,int position);
    void removeWidget(EvWidget *);
    void setCurrentTab(EvWidget *);
    void setCurrentIndex(int);


    void showNextTab();
    void showPrevioustab();


    void setBackgroundColor(const QColor & arg);
    void setSelectionColor(const QColor & arg);
    void setOutlineColor(const QColor & arg);
    void setLogoBackgroundColor(const QColor & arg);
    void setLogoText(const QString & arg);
    void setTabSize(const QSize & arg);
    void setLogoSize(const QSize & arg);
    void setMaximumSize(int arg);

    void setTabsFont(const QFont& arg);

protected Q_SLOTS:
    void onTabSelected(EvWidget*,bool mouseEvent);

protected:
    EvTabElement * createTabElement(EvWidget * , int level);
    EvTabElement *currentTabElement()const;

    void paintEvent(QPaintEvent *);
    int minimumTabWidth()const;
    QPoint minMaxSizes()const;
    void updateSize();
    void removeHoverIndicator();

private:
    EV_PRIVATE(EvTabBar)
};

#endif // EVTABBARWIDGET_H
