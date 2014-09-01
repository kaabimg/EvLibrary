#include "EvFindLineEdit.h"

#include <QPaintEvent>

EvFindLineEdit::EvFindLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setPlaceholderText("Type to locate an object");
}

void EvFindLineEdit::focusInEvent(QFocusEvent * e)
{
    QLineEdit::focusInEvent(e);
    Q_EMIT focusIn();

}

void EvFindLineEdit::focusOutEvent(QFocusEvent * e)
{
    QLineEdit::focusOutEvent(e);
    Q_EMIT focusOut();
}

void EvFindLineEdit::keyPressEvent(QKeyEvent * e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        Q_EMIT upKey();
        break;
    case Qt::Key_Down:
        Q_EMIT downKey();
        break;
    case Qt::Key_End:
    case Qt::Key_Return:
        Q_EMIT enterKey();
        break;
    case Qt::Key_Escape:
        clearFocus();
        break;
    default:
        QLineEdit::keyPressEvent(e);
        break;
    }
}
