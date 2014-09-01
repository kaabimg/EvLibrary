#ifndef EVFINDLINEEDIT_H
#define EVFINDLINEEDIT_H

#include <QLineEdit>

class EvFindLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit EvFindLineEdit(QWidget *parent = 0);

Q_SIGNALS:
    void focusIn();
    void focusOut();

    void upKey();
    void downKey();
    void enterKey();

protected:
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void keyPressEvent(QKeyEvent *);

};

#endif // EVFINDLINEEDIT_H
