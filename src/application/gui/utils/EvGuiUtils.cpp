#include "EvGuiUtils.h"

#include "EvAppSettings.h"

#include <QPainter>

void Ev::paintBarGradient(QPainter *painter, const QRect &rect)
{



    static const qreal epsilon = 0.000001;

    static const qreal stop1 = 0;
    static const qreal stop2 = 0.02;
    static const qreal stop3 = stop2 +epsilon;
    static const qreal stop4 = 0.07;
    static const qreal stop5 = stop4 + epsilon;
    static const qreal stop6 = 1;


    QLinearGradient linearGrad(rect.topLeft(),rect.bottomLeft());
    linearGrad.setColorAt(stop1, evApparenceSettings->darkColor());
    linearGrad.setColorAt(stop2, evApparenceSettings->darkColor());

    linearGrad.setColorAt(stop3, evApparenceSettings->ligthGraycolor());
    linearGrad.setColorAt(stop4, evApparenceSettings->ligthGraycolor());

    linearGrad.setColorAt(stop5, evApparenceSettings->grayColor());
    linearGrad.setColorAt(stop6, evApparenceSettings->grayColor());

    painter->fillRect(rect,linearGrad);


}


QFont Ev::fontForRect(const QString &text, const QRect &rect, bool bold)
{
    QFont font = evApparenceSettings->font();
    font.setBold(bold);


    for(int i=font.pointSize();i>5;--i){
        QFontMetrics metrics(font);
        if(metrics.width(text)<=rect.width() && metrics.height() < rect.height())
            return font;
        font.setPointSize(i-1);
    }

    return font;
}
