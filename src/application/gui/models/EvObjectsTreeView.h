#ifndef EVOBJECTSTREEVIEW_H
#define EVOBJECTSTREEVIEW_H

#include <QTreeView>
class EvObject;
class EvObjectsTreeModel;
class EvObjectsTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit EvObjectsTreeView(EvObject * rootItem,QWidget *parent = 0);
    explicit EvObjectsTreeView(QWidget *parent = 0);

    void setObjectsModel(EvObjectsTreeModel *);
    EvObjectsTreeModel *objectsModel()const;

    EvObject * selectedObject()const;
    void setCurrentSelection(EvObject *);

public Q_SLOTS:
    void expandIndex(const QModelIndex &index);


Q_SIGNALS:

    void objectSelected(EvObject*);
    void removeRequest(EvObject*);
    void copyRequest(EvObject*);
    void cutRequest(EvObject*);
    void pasteRequest(EvObject*);
    void saveRequest(EvObject*);

    void focusIn();
    void focusOut();

protected Q_SLOTS:
    void onSelectionChanged();


protected:
    void customizeStyle();
    void drawBranches(QPainter *, const QRect &, const QModelIndex &) const;   
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

};

#endif // EVOBJECTSTREEVIEW_H
