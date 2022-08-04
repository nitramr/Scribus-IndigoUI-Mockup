#include "util_color.h"
#include "qdebug.h"
#include <QPainter>

ColorUtils::ColorUtils()
{

}

QColor ColorUtils::colorBlend(QColor color1, QColor color2, double ratio)
{
    ratio = qBound(0., ratio, 1.);

    return QColor(
                color1.red()* (1-ratio) + color2.red()*ratio,
                color1.green()* (1-ratio) + color2.green()*ratio,
                color1.blue()* (1-ratio) + color2.blue()*ratio,
                color1.alpha()* (1-ratio) + color2.alpha()*ratio
                );
}

ScColor ColorUtils::colorBlend(ScColor color1, ScColor color2, double ratio)
{

    ratio = qBound(0., ratio, 1.);

    ScColor col;
    col.setRgb(
                color1.red()* (1-ratio) + color2.red()*ratio,
                color1.green()* (1-ratio) + color2.green()*ratio,
                color1.blue()* (1-ratio) + color2.blue()*ratio
                );
    col.setAlpha( color1.alpha()* (1-ratio) + color2.alpha()*ratio );
    col.setShade( color1.shade()* (1-ratio) + color2.shade()*ratio );

    return col;
}

QColor ColorUtils::colorAlpha(QColor color, double alpha)
{
    alpha = qBound(0.0, alpha, 1.0);
    return QColor::fromRgbF(color.redF(), color.greenF(), color.blueF(), alpha);
}

//QColor ColorUtils::colorDarken(QColor color, double dark)
//{
//    dark = qBound(0.0, color.lightnessF() - dark, 1.0);
//    return QColor::fromHslF(color.hslHueF(), color.hslSaturationF(), dark, color.alphaF());
//}

//QColor ColorUtils::colorLighten(QColor color, double light)
//{
//    light = qBound(0.0, color.lightnessF() + light, 1.0);
//    return QColor::fromHslF(color.hslHueF(), color.hslSaturationF(), light, color.alphaF());
//}

QColor ColorUtils::colorTint(QColor color, double tint)
{
    double r = color.redF() + (1 - color.redF()) * tint;
    double g = color.greenF() + (1 - color.greenF()) * tint;
    double b = color.blueF() + (1 - color.blueF()) * tint;

    return QColor::fromRgbF(r,g,b, color.alphaF());
}

QColor ColorUtils::colorShade(QColor color, double shade)
{
    double r = color.redF() * (1 - shade);
    double g = color.greenF() * (1 - shade);
    double b = color.blueF() * (1 - shade);

    return QColor::fromRgbF(r,g,b, color.alphaF());
}

QColor ColorUtils::colorLuminosity(QColor color, double luminosity)
{
    double r = 1 - (1 - color.redF()) * luminosity;
    double g = 1 - (1 - color.greenF()) * luminosity;
    double b = 1 - (1 - color.blueF()) * luminosity;

     return QColor::fromRgbF(r,g,b, color.alphaF());
}

