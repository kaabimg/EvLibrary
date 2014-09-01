#ifndef QMLSYNTAXHIGHLIGHTER_H
#define QMLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class EvQmlSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit EvQmlSyntaxHighlighter(QObject *parent = 0);

signals:

public slots:

};

#endif // QMLSYNTAXHIGHLIGHTER_H
