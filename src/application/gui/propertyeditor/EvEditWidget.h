#ifndef EVEDITWIDGET_H
#define EVEDITWIDGET_H

#include <QWidget>
class EvButton;

class EvEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EvEditWidget(QWidget  * widget,QWidget *parent = 0);

    void setData(void *);
    void * data()const;
    QWidget * widget()const;

Q_SIGNALS:
    void editRequest();

private:
    EvButton * m_editButton;
    QWidget * m_widget;
    void * m_data;
};

#endif // EVEDITWIDGET_H
