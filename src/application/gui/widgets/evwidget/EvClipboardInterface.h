#ifndef EVCLIPBOARDINTERFACE_H
#define EVCLIPBOARDINTERFACE_H
class EvWidget;
class EvObject;
class EvObjectsContainer;

#include <QList>
#include <QObject>


struct EvClipboardInterfacePrivate;

class  EvClipboardInterface : public QObject
{
    Q_OBJECT
public:
    EvClipboardInterface(QObject* parent = 0);
    virtual ~EvClipboardInterface();

    void setSelection(EvObject*);
    void setSelection(const QList<EvObject*> &);
    bool hasSelection()const;
    void clearSelection();
    const EvObjectsContainer * selectedObjects()const;

    void setCopyObject(EvObject* );
    void setCutObject(EvObject* );

    void setCopyObjects(const QList<EvObject*> &);
    void setCutObjects(const QList<EvObject*> &);

    void clearClipboardObject();

    bool canCopy()const;
    bool canPaste()const;
    bool canPaste(const EvObjectsContainer *)const;


public Q_SLOTS:

    void copy();
    void cut();
    void paste();


Q_SIGNALS:

    void selectionChanged();
    void clipboardObjectsChanged();
    void clipboardObjectsCleared();


private:
    EvClipboardInterfacePrivate * d_ptr;

};

#endif // EVCLIPBOARDINTERFACE_H
