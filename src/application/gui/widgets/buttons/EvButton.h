#ifndef EVBUTTON_H
#define EVBUTTON_H

#include <QPushButton>

class EvButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(PaintMode paintMode READ paintMode WRITE setPaintMode)
    Q_PROPERTY(bool rounded READ rounded WRITE setRounded)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)
    Q_PROPERTY(QColor pressedColor READ pressedColor WRITE setPressedColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)


public:
    enum PaintMode {
        TextOnly,
        IconOnly,
        IconAndText
    };

    explicit EvButton(QWidget *parent = 0);
    QSize sizeHint() const;

    PaintMode paintMode() const;
    bool rounded() const;
    QColor backgroundColor() const;
    QColor hoverColor() const;
    QColor pressedColor() const;
    QColor textColor() const;

public Q_SLOTS:
    void setPaintMode(PaintMode arg);
    void setRounded(bool arg);
    void setBackgroundColor(const QColor & arg);
    void setHoverColor(const QColor & arg);
    void setPressedColor(const QColor & arg);
    void setTextColor(const QColor & arg);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);


    float roundness()const;
    QRect textRect()const;
    QPainterPath textPath()const;
    QRect iconRect()const;
    QPainterPath backgroundPath()const;

private:
    bool m_hover;
    PaintMode m_paintMode;
    bool m_rounded;
    QColor m_backgroundColor;
    QColor m_hoverColor;
    QColor m_pressedColor;
    QColor m_textColor;
};

#endif // EVBUTTON_H
