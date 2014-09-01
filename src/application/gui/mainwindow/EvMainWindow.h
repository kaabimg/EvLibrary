#ifndef EVMAINWINDOW_H
#define EVMAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QMap>

#include "EvUserInteractionsInterface.h"
#include "EvGlobal.h"

class EvObject;
class EvIOPane;
class EvWidget;
class EvHideShowSideBarWidget;
class EvMainWindowPrivate;
class EvDialog;

#define evMainWindow EvMainWindow::instance()

class EvMainWindow : public QMainWindow, public EvUserInteractionsInterface
{
    Q_OBJECT
    Q_PROPERTY(int logoWidth READ logoWidth WRITE setLogoWidth NOTIFY logoWidthChanged)
    Q_PROPERTY(int temporaryWidgetsHeigth READ temporaryWidgetsHeigth WRITE setTemporaryWidgetsHeigth)
    Q_PROPERTY(EvWidget* activeWidget READ activeWidget  WRITE setActiveWidget NOTIFY activeWidgetChanged)
public:
    EvMainWindow(QWidget *parent = 0);
    ~EvMainWindow();
    static EvMainWindow *instance();

    int logoWidth() const;
    int tabWidth()const;


    EvHideShowSideBarWidget * hideShowSizeBarWidget()const;

public Q_SLOTS:
    void addIOPane(EvIOPane * );
    void addIOBarWidget(QWidget*);
    void addWidget(EvWidget*);

    void setCurrentWidget(EvWidget*);
    void setCurrentIOPane(EvIOPane*);
    void setLogoWidth(int arg);

    void setTemporaryWidgetsHeigth(int arg);
    QRect temporaryWidgetGeometry(QWidget * ioPaneController);

    void showObjectWidget(EvObject *);

    void setActiveWidget(EvWidget* arg);

public:// user interactions interface
    void importantInformation(const QString &sender, const QString &content);
    void importantWarning(const QString &sender, const QString &content);
    void importantError(const QString &sender, const QString &content);
    bool yesNoQuestion(const QString &sender, const QString &content);
    int temporaryWidgetsHeigth() const;
    EvWidget* activeWidget() const;

Q_SIGNALS:
    void logoWidthChanged(int);
    void resized();
    void moved();
    void hidden();

    void activeWidgetChanged(EvWidget* arg);

protected Q_SLOTS:
    void showIOPane();
    void hideIOPane();

    void showWidget(EvWidget*);
    void showIOPane(EvIOPane*);
    void updateStackSize();

    void resizeEvent(QResizeEvent* );
    void moveEvent(QMoveEvent *);
    void hideEvent(QHideEvent *);

protected:
    void loadPlugins();
    void loadMainViews();
    void loadIOPaneItems();

    void customizeDialogAspect(EvDialog & );

private:
    EV_PRIVATE(EvMainWindow)

};

#endif // EVMAINWINDOW_H
