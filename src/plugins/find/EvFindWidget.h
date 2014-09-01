#ifndef EVFINDWIDGET_H
#define EVFINDWIDGET_H

#include <QWidget>
class EvFindLineEdit;
class QLabel;
class EvObject;
class EvFindObjectsList;


class EvFindWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EvFindWidget(QWidget *parent = 0);

Q_SIGNALS:
    void showObjectWidgetRequest(EvObject*);



protected Q_SLOTS:
    void resizeObjectsList();
    void showObjectsList();
    void hideObjectsList();
    void parserFindText(const QString & );

    void onLineEditFocusLost();

    void onObjectSelected(EvObject *);

protected:
    void resizeEvent(QResizeEvent *);
private:
    EvFindLineEdit * m_lineEdit;
    QLabel * m_icon;
    EvFindObjectsList * m_objectsList;
};

#endif // EVFINDWIDGET_H
