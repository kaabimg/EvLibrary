#include "EvApparenceSettings.h"

EvApparenceSettings::EvApparenceSettings(QObject *parent) :
    EvSettings(parent)
{
    resetToDefault();
}

QSize EvApparenceSettings::logoSize() const
{
    return m_logoSize;
}

QSize EvApparenceSettings::mainTabSize() const
{
    return m_mainTabSize;
}

QColor EvApparenceSettings::primaryColor() const
{
    return m_primaryColor;
}

QColor EvApparenceSettings::secondaryColor() const
{
    return m_secondaryColor;
}

QColor EvApparenceSettings::darkColor() const
{
    return m_darkColor;
}

QColor EvApparenceSettings::ligthColor() const
{
    return m_ligthColor;
}

QColor EvApparenceSettings::grayColor() const
{
    return m_grayColor;
}

QColor EvApparenceSettings::ligthGraycolor() const
{
    return m_ligthGraycolor;
}

QFont EvApparenceSettings::font() const
{
    return m_font;
}

QFont EvApparenceSettings::buttonsFont() const
{
    return m_buttonsFont;
}



void EvApparenceSettings::setPrimaryColor(const QColor &arg)
{
    if (m_primaryColor != arg) {
        m_primaryColor = arg;
        Q_EMIT primaryColorChanged(arg);
    }
}

void EvApparenceSettings::setSecondaryColor(const QColor &arg)
{
    if (m_secondaryColor != arg) {
        m_secondaryColor = arg;
        Q_EMIT secondaryColorChanged(arg);
    }
}

void EvApparenceSettings::setDarkColor(const QColor &arg)
{
    if (m_darkColor != arg) {
        m_darkColor = arg;
        Q_EMIT darkColorChanged(arg);
    }
}

void EvApparenceSettings::setLigthColor(const QColor &arg)
{
    if (m_ligthColor != arg) {
        m_ligthColor = arg;
        Q_EMIT grayColorChanged(arg);
    }
}

void EvApparenceSettings::setGrayColor(const QColor &arg)
{
    if (m_grayColor != arg) {
        m_grayColor = arg;
        Q_EMIT grayColorChanged(arg);
    }
}

void EvApparenceSettings::setLigthGraycolor(const QColor &arg)
{
    if (m_ligthGraycolor != arg) {
        m_ligthGraycolor = arg;
        Q_EMIT ligthGraycolorChanged(arg);
    }
}

void EvApparenceSettings::setFont(const QFont &arg)
{
    if (m_font != arg) {
        m_font = arg;
        Q_EMIT fontChanged(arg);
    }
}

void EvApparenceSettings::setButtonsFont(const QFont &arg)
{
    if (m_buttonsFont != arg) {
        m_buttonsFont = arg;
        Q_EMIT buttonsFontChanged(arg);
    }
}

void EvApparenceSettings::setLogoSize(const QSize &arg)
{
    if (m_logoSize != arg) {
        m_logoSize = arg;
        Q_EMIT logoSizeChanged(arg);
    }
}

void EvApparenceSettings::setMainTabSize(const QSize &arg)
{
    if (m_mainTabSize != arg) {
        m_mainTabSize = arg;
        Q_EMIT mainTabSizeChanged(arg);
    }
}


void EvApparenceSettings::resetToDefault()
{
    m_logoSize = QSize(230,50);
    m_mainTabSize = QSize(170,50);
    m_primaryColor = "#0866C6";
    m_secondaryColor = "#A5002C";
    m_darkColor = "#050505";
    m_grayColor = "#282828";
    m_ligthGraycolor = "#444444";
    m_ligthColor = "#E6E6E6";
    m_font.setFamily("Ubuntu");
    m_font.setPointSize(16);

    m_buttonsFont.setFamily("Ubuntu");
    m_font.setPointSize(13);
}
