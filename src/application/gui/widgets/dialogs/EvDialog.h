#ifndef EVDIALOG_H
#define EVDIALOG_H

#include <QWidget>
class QHBoxLayout;
class EvButton;
class QLabel;
class QVBoxLayout;

class EvDialog : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString sender READ sender WRITE setSender)

public:
    enum Button {
        NoButtons = 0,
        Ok        = 1 << 1,
        Cancel    = 1 << 2,
        Apply     = 1 << 3,
        Yes       = 1 << 4,
        No        = 1 << 5,
    };
    Q_DECLARE_FLAGS(Buttons,Button)

    explicit EvDialog(Buttons buttons, QWidget *parent = 0);


    Button exec();

    QString title() const;
    QString sender() const;

    void addContent(QWidget * );

public Q_SLOTS:
    void setTitle(const QString & arg);
    void setSender(const QString & arg);

protected:
    EvButton * createButton(Button type);
    QHBoxLayout * createButtons(Buttons buttons);

protected Q_SLOTS:
    void onButtonClicked();

Q_SIGNALS:
    void terminated();

private:
    Button m_returnStauts;
    QLabel * m_title;
    QLabel * m_sender;

    QVBoxLayout * m_contentLayout;
};


Q_DECLARE_OPERATORS_FOR_FLAGS(EvDialog::Buttons)


#endif // EVDIALOG_H
