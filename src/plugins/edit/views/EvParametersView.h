#ifndef EVPARAMETERSVIEW_H
#define EVPARAMETERSVIEW_H

#include "EvWidget.h"

class EvProcess;
class QTableView;

class EvParametersView : public EvWidget
{
    Q_OBJECT
public:
    explicit EvParametersView(EvProcess * process,QWidget *parent = 0);

    bool containsObject(const EvObject*)const;
    bool showObject(EvObject*parameter);

    QStringList selectedParametersNames()const;

    void paste();
protected:
    void resizeEvent(QResizeEvent *);

protected Q_SLOTS:
    void onSelectionChanged();
    void addParameter();
    void removeSelectedParameters();

private:
    QTableView * m_parametersTable ;

};

#endif // EVPARAMETERSVIEW_H
