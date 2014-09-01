#ifndef EVSPLITTER_H
#define EVSPLITTER_H

#include <QSplitter>

class EvSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit EvSplitter(Qt::Orientation orientation,QWidget *parent = 0);

protected:
    QSplitterHandle * createHandle();


public slots:

};

#endif // EVSPLITTER_H
