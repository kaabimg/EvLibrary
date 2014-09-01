#ifndef EVGUIUTILS_H
#define EVGUIUTILS_H
#include <QFont>
class QPainter;
class QRect;


namespace Ev {
    void paintBarGradient(QPainter * painter, const QRect & rect);
    QFont fontForRect(const QString & text,const QRect & rect, bool bold=false);

}

#endif // EVGUIUTILS_H
