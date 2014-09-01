#ifndef EVTABELEMENT_H
#define EVTABELEMENT_H

#include <QWidget>
#include <QLineEdit>
#include <QTimer>

class EvWidget;
class QPropertyAnimation;

class EvTabElement : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor NOTIFY selectionColorChanged)
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor NOTIFY outlineColorChanged)
    Q_PROPERTY(float fadeValue READ fadeValue WRITE setFadeValue)

public:
    explicit EvTabElement(EvWidget *widget ,QWidget *parent = 0);

    EvWidget * widget()const;

    int level() const;
    bool selected() const;
    bool active() const;
    QColor selectionColor() const;
    QColor outlineColor() const;
    float fadeValue() const;
    void renameTab(const QString & name);

    QSize minimumSizeHint()const;
    void setPrefferedSize(const QSize & size);



protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void focusInEvent(QFocusEvent * );
    void fadeIn();
    void fadeOut();
    QString text()const;
    friend class EvTabBar;

Q_SIGNALS:
    void levelChanged(int);
    void selectedChanged(bool);
    void activeChanged(bool);
    void selectionColorChanged(const QColor &);
    void outlineColorChanged(const QColor &);


    void selected(EvWidget*,bool mouseEvent=false);
    void showNextRequest();
    void showPreviousRequest();


    void copyRequest(EvWidget*);
    void cutRequest(EvWidget*);
    void pasteRequest(EvWidget*);
    void removeRequest(EvWidget*);


public Q_SLOTS:
    void setLevel(int arg);
    void setActive(bool arg);
    void setSelectionColor(const QColor & arg);
    void setFadeValue(float arg);
    void setOutlineColor(const QColor & arg);

    void setSelected(bool arg,bool mouseEvent=false);



protected:
    QFont fontFromWidth(int w)const;

    QRect iconRect()const;
    QRect lockStateRect()const;
    QRect statusRect()const;
    QRect textRect()const;
    void adjustRect(QRect& rect,int value=4)const;

protected  Q_SLOTS:
    void onWidgetProcessingChanged(bool);


private:
    EvWidget * m_widget;
    QPropertyAnimation * m_animator;
    int m_level;
    bool m_active;
    bool m_selected;
    QColor m_selectionColor;
    QColor m_outlineColor;
    float m_fadeValue;
    QSize m_prefferedSize;
    QTimer m_processingAnimation;
    bool m_processingAnimationDrawIcon;
};








class EvTabLogoElement : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit EvTabLogoElement(QWidget *parent = 0):QWidget(parent){}

    void paintEvent(QPaintEvent *);

    QString text() const
    {
        return m_text;
    }
    QColor backgroundColor() const
    {
        return m_backgroundColor;
    }

public Q_SLOTS:
    void setText(const QString & arg)
    {
        m_text = arg;
        update();
    }
    void setBackgroundColor(const QColor & arg)
    {
        m_backgroundColor = arg;
        update();
    }

private:
    QString m_text;
    QColor m_backgroundColor;
};




class EvTabElementRenameLineEdit  : public QLineEdit {
    Q_OBJECT
public:
    EvTabElementRenameLineEdit(EvTabElement  * tab);
    void focusOutEvent(QFocusEvent *);
    void keyPressEvent(QKeyEvent*event);
    EvTabElement  * tab;


};


#endif // EVTABELEMENT_H
