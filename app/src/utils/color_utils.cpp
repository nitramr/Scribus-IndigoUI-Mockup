#include "color_utils.h"
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

double ColorUtils::getCurveYValue(FPointArray &curve, double x, bool linear)
{

    double t;
    FPoint p;
    FPoint p0, p1, p2, p3;
    double c0, c1, c2, c3;
    double val = 0.5;
    if (curve.isEmpty())
        return 0.5;
    // First find curve segment
    p = curve.point(0);
    if (x < p.x())
        return p.y();
    p = curve.point(curve.size()-1);
    if (x >= p.x())
        return p.y();
    int cc = 0;
    // Find the four control points (two on each side of x)
    p = curve.point(0);
    while (x >= p.x())
    {
        cc++;
        p = curve.point(cc);
    }
    if (cc > 1)
    {
        p0 = curve.point(cc-2);
        p1 = curve.point(cc-1);
    }
    else
        p1 = p0 = curve.point(0);
    p2 = p;
    if (cc < curve.size()-1)
        p3 = curve.point(cc+1);
    else
        p3 = p;
    // Calculate the value
    if (linear)
    {
        double mc;
        if (p1.x() - p2.x() != 0.0)
            mc = (p1.y() - p2.y()) / (p1.x() - p2.x());
        else
            mc = p2.y() / p2.x();
        val = (x - p1.x()) * mc + p1.y();
    }
    else
    {
        t = (x - p1.x()) / (p2.x() - p1.x());
        c2 = (p2.y() - p0.y()) * (p2.x() - p1.x()) / (p2.x() - p0.x());
        c3 = p1.y();
        c0 = -2 * p2.y() + 2 * c3 + c2 + (p3.y() - p1.y()) * (p2.x() - p1.x()) / (p3.x() - p1.x());
        c1 = p2.y() - c3 - c2 - c0;
        val = ((c0 * t + c1) * t + c2) * t + c3;

    }
    if (val < 0.0)
        val = 0.0;
    if (val > 1.0)
        val = 1.0;
    return val;
}
