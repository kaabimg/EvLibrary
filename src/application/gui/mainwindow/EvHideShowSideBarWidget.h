#ifndef EVHIDESHOWSIDEBARWIDGET_H
#define EVHIDESHOWSIDEBARWIDGET_H

#include <QWidget>

class EvButton;

class EvHideShowSideBarWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool maximizeAvailable READ maximizeAvailable WRITE setMaximizeAvailable)
    Q_PROPERTY(bool minimizeAvailable READ minimizeAvailable WRITE setMinimizeAvailable)

public:
    explicit EvHideShowSideBarWidget(QWidget *parent = 0);

    bool maximizeAvailable() const;
    bool minimizeAvailable() const;

Q_SIGNALS:
    void minimizeRequest();
    void maximizeRequest();

public Q_SLOTS:

    void setMaximizeAvailable(bool arg);
    void setMinimizeAvailable(bool arg);


private:

    EvButton * m_maximizeButton;
    EvButton * m_minimizeButton;
};

#endif // EVHIDESHOWSIDEBARWIDGET_H
