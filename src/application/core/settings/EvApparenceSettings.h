#ifndef EVAPPARENTCESETTINGS_H
#define EVAPPARENTCESETTINGS_H

#include "EvSettings.h"

#include <QFont>

class EvApparenceSettings : public EvSettings
{
    Q_OBJECT


    Q_PROPERTY(QSize logoSize READ logoSize WRITE setLogoSize NOTIFY logoSizeChanged)
    Q_PROPERTY(QSize mainTabSize READ mainTabSize WRITE setMainTabSize NOTIFY mainTabSizeChanged)

    Q_PROPERTY(QColor primaryColor READ primaryColor WRITE setPrimaryColor NOTIFY primaryColorChanged)
    Q_PROPERTY(QColor secondaryColor READ secondaryColor WRITE setSecondaryColor NOTIFY secondaryColorChanged)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor NOTIFY darkColorChanged)
    Q_PROPERTY(QColor grayColor READ grayColor WRITE setGrayColor NOTIFY grayColorChanged)
    Q_PROPERTY(QColor ligthGraycolor READ ligthGraycolor WRITE setLigthGraycolor NOTIFY ligthGraycolorChanged)
    Q_PROPERTY(QColor ligthColor READ ligthColor WRITE setLigthColor NOTIFY grayColorChanged)

    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QFont buttonsFont READ buttonsFont WRITE setButtonsFont NOTIFY buttonsFontChanged)


public:
    Q_INVOKABLE explicit EvApparenceSettings(QObject *parent = 0);

    QSize logoSize() const;
    QSize mainTabSize() const;
    QColor primaryColor() const;
    QColor secondaryColor() const;
    QColor darkColor() const;
    QColor grayColor() const;
    QColor ligthGraycolor() const;
    QColor ligthColor() const;
    QFont font() const;
    QFont buttonsFont() const;

    void resetToDefault();



Q_SIGNALS:

    void logoSizeChanged(const QSize& arg);
    void mainTabSizeChanged(const QSize& arg);

    void primaryColorChanged(const QColor &);
    void secondaryColorChanged(const QColor &);
    void darkColorChanged(const QColor &);
    void grayColorChanged(const QColor &);
    void ligthGraycolorChanged(const QColor &);
    void fontChanged(const QFont &);
    void buttonsFontChanged(QFont arg);


public Q_SLOTS:

    void setLogoSize(const QSize & arg);
    void setMainTabSize(const QSize &arg);
    void setPrimaryColor(const QColor& arg);
    void setSecondaryColor(const QColor& arg);
    void setDarkColor(const QColor& arg);
    void setGrayColor(const QColor& arg);
    void setLigthGraycolor(const QColor & arg);
    void setLigthColor(const QColor& arg);
    void setFont(const QFont& arg);
    void setButtonsFont(const QFont& arg);

private:

    QSize m_logoSize;
    QSize m_mainTabSize;
    QColor m_primaryColor;
    QColor m_secondaryColor;
    QColor m_darkColor;
    QColor m_ligthColor;
    QColor m_grayColor;
    QColor m_ligthGraycolor;
    QFont m_font;
    QFont m_buttonsFont;


};

#endif // EVAPPARENTCESETTINGS_H
