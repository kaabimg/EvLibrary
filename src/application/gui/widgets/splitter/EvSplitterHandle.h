#ifndef EVSPLITTERHANDLE_H
#define EVSPLITTERHANDLE_H

#include <QSplitterHandle>
class QSplitter;
class EvSplitterHandle : public QSplitterHandle
{
    Q_OBJECT
public:
    explicit EvSplitterHandle(Qt::Orientation orientation,QSplitter *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

};

#endif // EVSPLITTERHANDLE_H
