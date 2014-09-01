#ifndef EVWIDGET_H
#define EVWIDGET_H

#include <QWidget>
#include <QList>
#include <QIcon>
#include "EvGlobal.h"

#include "EvWidgetFlagsInterface.h"
#include "EvCommandsInterface.h"
#include "EvClipboardInterface.h"

class QShowEvent;
class QVBoxLayout;
class EvObject;

class EvWidget :
        public QWidget,
        public EvWidgetFlagsInterface
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool activeOnShow READ activeOnShow WRITE setActiveOnShow)
    Q_PROPERTY(bool supportsRename READ supportsRename)
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

public:


    explicit EvWidget(QWidget *parent = 0);
    explicit EvWidget(EvObject * ,QWidget *parent = 0);
    void setContent(QWidget*);



    EvObject* evObject() const;

    bool enabled() const;
    void setEnabled(bool arg);

    bool activeOnShow() const;
    void setActiveOnShow(bool arg);

    bool supportsRename() const;
    virtual void rename(const QString & );
    virtual void setAsActiveWidget();

    bool isProcessing() const;
    virtual bool supportsProcessing()const{return false;}

    // actions

    QList<QAction*> clipboardActions()const;
    void setCopyEnabled(bool);
    void setCutEnabled(bool);
    void setPasteEnabled(bool);

    QList<QAction*> undoRedoActions()const;



public Q_SLOTS:// EvWidget generic api

    virtual void add(EvWidget * ,int index = -1){Q_UNUSED(index);}
    virtual void remove(EvWidget * ){}

    virtual bool contains(EvWidget * ){return false;}
    virtual int indexOf(EvWidget *){return -1;}

    virtual QList<EvWidget*> chilrenWidgets()const{return QList<EvWidget*>();}
    virtual int childrenWidgetsCount()const;

    virtual void setCurrentWidget(EvWidget*){}
    virtual void setCurrentIndex(int){}

    virtual  EvWidget* currentWidget()const{return NULL;}
    virtual  int currentIndex()const{return -1;}

    // for search feature
    virtual bool showObject(EvObject*);

    // clipboard

    virtual void copy();
    virtual void cut();
    virtual void paste();


Q_SIGNALS:
    void showRequest(EvWidget*);
    void removeRequest(EvWidget*);
    void currentWidgetChanged(EvWidget*);
    void currentIndexChanged(int);


public:

    EvWidget * parentEvWidget()const;
    void setParentEvWidget(EvWidget *);


    EvCommandsInterface * commandsInterface()const;
    EvClipboardInterface * clipboardInterface()const;



public Q_SLOTS:
    void setEvObject(EvObject* arg);
    void setIsProcessing(bool arg);



Q_SIGNALS:
    void labelChanged(const QString & );
    void enabledChanged(bool);
    void iconChanged(const QIcon &);
    void objectChanged(EvObject* arg);
    void controlledObjectDeleted();
    void isProcessingChanged(bool arg);

protected:
    QAction * createAction(const QIcon &,const QString & text,const char * member);
    QAction * createAction(const QIcon &,const QString & text,QObject * object,const char * member);

    QAction * createSeparator();

    void setSupportsRename(bool arg);
    void connectEvObject(EvObject*);
    void disconnectEvObject(EvObject*);

protected Q_SLOTS:
    void updateClipboardActions();

protected:
    void showEvent(QShowEvent *);
    void createClipboardActions();
    void createUndoRedoActions();
private:
    void initialize();
private:

    EvWidget * m_parentEvWidget;
    EvObject * m_object;
    EvCommandsInterface * m_commandsInterface;
    EvClipboardInterface * m_clipboardInterface;
    bool m_enabled;
    bool m_setActiveOnShow;
    bool m_supportsRename;
    bool m_isProcessing;
    QList<QAction*> m_clipboardActions;
    QList<QAction*> m_undoRedoActions;

    friend class EvMainWindow;
};



#endif // EVWIDGET_H
