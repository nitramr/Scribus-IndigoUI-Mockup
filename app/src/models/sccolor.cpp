/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          sccolor.cpp  -  description
                             -------------------
    begin                : Sun Sep 9 2001
    copyright            : (C) 2001 by Franz Schmid
    email                : Franz.Schmid@altmuehlnet.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "sccolor.h"
#include "qdebug.h"

#include "colorspace.h"
#include "util_color.h"

// original: https://github.com/scribusproject/scribus/blob/master/scribus/sccolor.cpp

/* ********************************************************************************* *
 *
 * Constructor
 *
 * ********************************************************************************* */

ScColor::ScColor()
{
    setRgb(255,0,0); // red
}

ScColor::ScColor(int c, int m, int y, int k)
{
    setCmyk(c, m, y, k);
}

ScColor::ScColor(int r, int g, int b)
{
    setRgb(r, g, b);
}

ScColor::ScColor(double l, double a, double b)
{
    setLab(l, a, b);
}

bool ScColor::operator==(const ScColor &other) const
{
    if (m_model != other.m_model)
        return false;

    if (m_spot != other.m_spot)
        return false;

    if (m_register != other.m_register)
        return false;

    if(m_colorData.alpha != other.m_colorData.alpha)
        return false;

    if(m_colorData.shade != other.m_colorData.shade)
        return false;

    if (m_model == ColorModel::RGB)
    {
        return (m_colorData.RGB_red == other.m_colorData.RGB_red &&
                m_colorData.RGB_green == other.m_colorData.RGB_green &&
                m_colorData.RGB_blue == other.m_colorData.RGB_blue
                );
    }

    if (m_model == ColorModel::CMYK)
    {
        return (m_colorData.CMYK_cyan == other.m_colorData.CMYK_cyan &&
                m_colorData.CMYK_magenta == other.m_colorData.CMYK_magenta &&
                m_colorData.CMYK_yellow == other.m_colorData.CMYK_yellow &&
                m_colorData.CMYK_key == other.m_colorData.CMYK_key
                );
    }

    if (m_model == ColorModel::Lab)
    {
        return (m_colorData.Lab_L == other.m_colorData.Lab_L &&
                m_colorData.Lab_a == other.m_colorData.Lab_a &&
                m_colorData.Lab_b == other.m_colorData.Lab_b
                );
    }

    if (m_model == ColorModel::HSV)
    {
        return (m_colorData.HSV_Hue == other.m_colorData.HSV_Hue &&
                m_colorData.HSV_Saturation == other.m_colorData.HSV_Saturation &&
                m_colorData.HSV_Value == other.m_colorData.HSV_Value
                );
    }
    return false;
}

/* ********************************************************************************* *
 *
 * Set
 *
 * ********************************************************************************* */

void ScColor::setColor(int c, int m, int y, int k, int alpha, int shade)
{
    setCmyk(c, m, y, k, alpha, shade);
}

void ScColor::setColorF(double c, double m, double y, double k, double alpha, double shade)
{
    setCmykF(c, m, y, k, alpha, shade);
}

void ScColor::setCmyk(int c, int m, int y, int k, int alpha, int shade)
{
    setCmykF(
                qBound(0., c / 255., 1.),
                qBound(0., m / 255., 1.),
                qBound(0., y / 255., 1.),
                qBound(0., k / 255., 1.),
                qBound(0., alpha / 255., 1.),
                qBound(0., shade / 255., 1.)
                );
}

void ScColor::setCmykF(double c, double m, double y, double k, double alpha, double shade)
{
    m_model = ColorModel::CMYK;
    m_colorData.CMYK_cyan = qBound(0., c, 1.);
    m_colorData.CMYK_magenta = qBound(0., m, 1.);
    m_colorData.CMYK_yellow =qBound(0., y, 1.);
    m_colorData.CMYK_key =qBound(0., k, 1.);
    setAlphaF(alpha);
    setShadeF(shade);
//    m_colorData.alpha = qBound(0., alpha, 1.);
//    m_colorData.shade = qBound(0., shade, 1.);
}

void ScColor::setRgb(int r, int g, int b, int alpha, int shade)
{
    setRgbF(
                qBound(0., r / 255., 1.),
                qBound(0., g / 255., 1.),
                qBound(0., b / 255., 1.),
                qBound(0., alpha / 255., 1.),
                qBound(0., shade / 255., 1.)
                );
}

void ScColor::setRgbF(double r, double g, double b, double alpha, double shade)
{
    m_model = ColorModel::RGB;
    m_colorData.RGB_red = qBound(0., r, 1.);
    m_colorData.RGB_green = qBound(0., g, 1.);
    m_colorData.RGB_blue =qBound(0., b, 1.);
    setAlphaF(alpha);
    setShadeF(shade);
//    m_colorData.alpha = qBound(0., alpha, 1.);
//    m_colorData.shade = qBound(0., shade, 1.);
}

void ScColor::setHsv(int h, int s, int v, int alpha, int shade)
{
    setHsvF(
                qBound(0., h / 359., 1.),
                qBound(0., s / 255., 1.),
                qBound(0., v / 255., 1.),
                qBound(0., alpha / 255., 1.),
                qBound(0., shade / 255., 1.)
                );
}

void ScColor::setHsvF(double h, double s, double v, double alpha, double shade)
{
    m_model = ColorModel::HSV;
    m_colorData.HSV_Hue = qBound(0., h, 1.);
    m_colorData.HSV_Saturation = qBound(0., s, 1.);
    m_colorData.HSV_Value =qBound(0., v, 1.);
    setAlphaF(alpha);
    setShadeF(shade);
//    m_colorData.alpha = qBound(0., alpha, 1.);
//    m_colorData.shade = qBound(0., shade, 1.);

}

void ScColor::setLab(double l, double a, double b, int alpha, int shade)
{
    m_model = ColorModel::Lab;
    m_colorData.Lab_L = qBound(0., l, 100.);
    m_colorData.Lab_a = qBound(-128., a, 127.);
    m_colorData.Lab_b = qBound(-128., b, 127.);
    setAlpha(alpha);
    setShade(shade);
//    m_colorData.alpha = qBound(0., alpha / 255., 1.);
//    m_colorData.shade = qBound(0., shade / 255., 1.);
}

void ScColor::setAlpha(int alpha)
{
    setAlphaF(qBound(0., alpha / 255., 1.));
}

void ScColor::setAlphaF(double alpha)
{
    m_colorData.alpha = qBound(0., alpha, 1.);
}

void ScColor::setShade(int shade)
{
    setShadeF(qBound(0., shade / 255., 1.));
}

void ScColor::setShadeF(double shade)
{
    m_colorData.shade = qBound(0., shade, 1.);
}

/* ********************************************************************************* *
 *
 * From
 *
 * ********************************************************************************* */

void ScColor::fromQColor(QColor color)
{
    if (color.spec() == QColor::Cmyk)
    {
        int c, m, y, k, a;
        color.getCmyk(&c, &m, &y, &k, &a);
        setColor(c, m, y, k, a);
    }
    else
    {
        int r, g, b, a;
        color.getRgb(&r, &g, &b, &a);
        setRgb(r, g, b, a);
    }

}

/* ********************************************************************************* *
 *
 * Get
 *
 * ********************************************************************************* */

void ScColor::getCmyk(int *c, int *m, int *y, int *k) const
{
    if (m_model != ColorModel::CMYK)
        qDebug("calling getCmyk with a non cmyk color");
    *c = qRound(m_colorData.CMYK_cyan * 255);
    *m = qRound(m_colorData.CMYK_magenta * 255);
    *y = qRound(m_colorData.CMYK_yellow * 255);
    *k = qRound(m_colorData.CMYK_key * 255);
}

void ScColor::getCmykF(double *c, double *m, double *y, double *k) const
{
    if (m_model != ColorModel::CMYK)
        qDebug("calling getCmykF with a non cymk color");
    *c = m_colorData.CMYK_cyan;
    *m = m_colorData.CMYK_magenta;
    *y = m_colorData.CMYK_yellow;
    *k = m_colorData.CMYK_key;
}

void ScColor::getRgb(int *r, int *g, int *b) const
{
    if (m_model != ColorModel::RGB)
        qDebug("calling getRgb with a non rgb color");
    *r = qRound(m_colorData.RGB_red * 255);
    *g = qRound(m_colorData.RGB_green * 255);
    *b = qRound(m_colorData.RGB_blue * 255);
}

void ScColor::getRgbF(double *r, double *g, double *b) const
{
    if (m_model != ColorModel::RGB)
        qDebug("calling getRgbF with a non rgb color");
    *r = m_colorData.RGB_red;
    *g = m_colorData.RGB_green;
    *b = m_colorData.RGB_blue;
}

void ScColor::getLab(double *L, double *a, double *b) const
{
    if (m_model != ColorModel::Lab)
        qDebug("calling getLab with a non Lab color");
    *L = m_colorData.Lab_L;
    *a = m_colorData.Lab_a;
    *b = m_colorData.Lab_b;
}

void ScColor::getHsv(int *h, int *s, int *v) const
{
    if (m_model != ColorModel::HSV)
        qDebug("calling getHsv with a non hsv color");
    *h = qRound(m_colorData.HSV_Hue * 359);
    *s = qRound(m_colorData.HSV_Saturation * 255);
    *v = qRound(m_colorData.HSV_Value * 255);
}

void ScColor::getHsvF(double *h, double *s, double *v) const
{
    if (m_model != ColorModel::HSV)
        qDebug("calling getHsvF with a non hsv color");
    *h = m_colorData.HSV_Hue;
    *s = m_colorData.HSV_Saturation;
    *v = m_colorData.HSV_Value;
}


/* ********************************************************************************* *
 *
 * Color Space Converter
 *
 * ********************************************************************************* */

ScColor ScColor::toRgb() const
{
    ScColor color;

    switch(m_model){
    case ColorModel::RGB:
        return *this;
        break;
    case ColorModel::CMYK:{
        ColorSpace::Cmyk cmyk(m_colorData.CMYK_cyan, m_colorData.CMYK_magenta, m_colorData.CMYK_yellow, m_colorData.CMYK_key);
        ColorSpace::Rgb rgb;
        cmyk.To<ColorSpace::Rgb>(&rgb);

        color.setRgb(rgb.r, rgb.g, rgb.b, alpha(), shade());
        break;
    }
    case ColorModel::Lab:{
        ColorSpace::Lab lab(m_colorData.Lab_L, m_colorData.Lab_a, m_colorData.Lab_b);
        ColorSpace::Rgb rgb;
        lab.To<ColorSpace::Rgb>(&rgb);

        color.setRgb(rgb.r, rgb.g, rgb.b, alpha(), shade());
        break;
    }
    case ColorModel::HSV:{
        ColorSpace::Hsv hsv(qRound(m_colorData.HSV_Hue * 359), m_colorData.HSV_Saturation, m_colorData.HSV_Value);
        ColorSpace::Rgb rgb;
        hsv.To<ColorSpace::Rgb>(&rgb);

        color.setRgb(rgb.r, rgb.g, rgb.b, alpha(), shade());
        break;
    }
    }

    return color;

}

ScColor ScColor::toCmyk() const
{
    ScColor color;

    switch(m_model){
    case ColorModel::RGB:{
        ColorSpace::Rgb rgb(qRound(m_colorData.RGB_red*255), qRound(m_colorData.RGB_green*255), qRound(m_colorData.RGB_blue*255));
        ColorSpace::Cmyk cmyk;
        rgb.To<ColorSpace::Cmyk>(&cmyk);

        color.setCmykF(cmyk.c, cmyk.m, cmyk.y, cmyk.k, alphaF(), shadeF());
        break;
    }
    case ColorModel::CMYK:{
        return *this;
        break;
    }
    case ColorModel::Lab:{
        ColorSpace::Lab lab(m_colorData.Lab_L, m_colorData.Lab_a, m_colorData.Lab_b);
        ColorSpace::Cmyk cmyk;
        lab.To<ColorSpace::Cmyk>(&cmyk);

        color.setCmykF(cmyk.c, cmyk.m, cmyk.y, cmyk.k, alphaF(), shadeF());
        break;
    }
    case ColorModel::HSV:{
        ColorSpace::Hsv hsv(qRound(m_colorData.HSV_Hue * 359), m_colorData.HSV_Saturation, m_colorData.HSV_Value);
        ColorSpace::Cmyk cmyk;
        hsv.To<ColorSpace::Cmyk>(&cmyk);

        color.setCmykF(cmyk.c, cmyk.m, cmyk.y, cmyk.k, alphaF(), shadeF());
        break;
    }
    }

    return color;
}

ScColor ScColor::toLab() const
{
    ScColor color;

    switch(m_model){
    case ColorModel::RGB:{
        ColorSpace::Rgb rgb(qRound(m_colorData.RGB_red*255), qRound(m_colorData.RGB_green*255), qRound(m_colorData.RGB_blue*255));
        ColorSpace::Lab lab;
        rgb.To<ColorSpace::Lab>(&lab);

        color.setLab(lab.l, lab.a, lab.b, alpha(), shade());
        break;
    }
    case ColorModel::CMYK:{
        ColorSpace::Cmyk cmyk(m_colorData.CMYK_cyan, m_colorData.CMYK_magenta, m_colorData.CMYK_yellow, m_colorData.CMYK_key);
        ColorSpace::Lab lab;
        cmyk.To<ColorSpace::Lab>(&lab);

        color.setLab(lab.l, lab.a, lab.b, alpha(), shade());
        break;
    }
    case ColorModel::Lab:
        return *this;
        break;
    case ColorModel::HSV:{
        ColorSpace::Hsv hsv(qRound(m_colorData.HSV_Hue * 359), m_colorData.HSV_Saturation, m_colorData.HSV_Value);
        ColorSpace::Lab lab;
        hsv.To<ColorSpace::Lab>(&lab);

        color.setLab(lab.l, lab.a, lab.b, alpha(), shade());
        break;
    }
    }

    return color;
}

ScColor ScColor::toHsv() const
{
    ScColor color;

    switch(m_model){
    case ColorModel::RGB:{
        ColorSpace::Rgb rgb(qRound(m_colorData.RGB_red*255), qRound(m_colorData.RGB_green*255), qRound(m_colorData.RGB_blue*255));
        ColorSpace::Hsv hsv;
        rgb.To<ColorSpace::Hsv>(&hsv);

        color.setHsvF(hsv.h / 359., hsv.s, hsv.v, alphaF(), shadeF());
        break;
    }
    case ColorModel::CMYK:{
        ColorSpace::Cmyk cmyk(m_colorData.CMYK_cyan, m_colorData.CMYK_magenta, m_colorData.CMYK_yellow, m_colorData.CMYK_key);
        ColorSpace::Hsv hsv;
        cmyk.To<ColorSpace::Hsv>(&hsv);

        color.setHsvF(hsv.h / 359., hsv.s, hsv.v, alphaF(), shadeF());
        break;
    }
    case ColorModel::Lab:{
        ColorSpace::Lab lab(m_colorData.Lab_L, m_colorData.Lab_a, m_colorData.Lab_b);
        ColorSpace::Hsv hsv;
        lab.To<ColorSpace::Hsv>(&hsv);

        color.setHsvF(hsv.h / 359., hsv.s, hsv.v, alphaF(), shadeF());
        break;
    }
    case ColorModel::HSV:
        return *this;
        break;

    }

    return color;
}

QColor ScColor::toQColor() const
{
//    ScColor color = this->toRgb();
//    return QColor(color.red(), color.green(), color.blue(), color.alpha());

    ScColor color = this->toRgb();
    QColor qColor(color.red(), color.green(), color.blue(), color.alpha());

    return ColorUtils::colorLuminosity(qColor, m_colorData.shade);
}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

ColorModel ScColor::getColorModel() const
{
    return m_model;
}

bool ScColor::isProcessColor() const
{
    return (!m_register && !m_spot);
}

bool ScColor::isSpotColor() const
{
    return m_spot;
}

void ScColor::setSpotColor(bool s)
{
    m_spot = s;
}

bool ScColor::isRegistrationColor() const
{
    return m_register;
}

void ScColor::setRegistrationColor(bool r)
{
    m_register = r;
}

bool ScColor::isOutOfGamut() const
{
    return m_outOfGamut;
}

void ScColor::setIsOutOfGamut(bool g)
{
    m_outOfGamut = g;
}

int ScColor::red() const
{
    return qRound(redF() * 255);
}

double ScColor::redF() const
{
    if(m_model == ColorModel::RGB) return m_colorData.RGB_red;

    ScColor color = this->toRgb();
    return color.redF();
}

int ScColor::green() const
{
    return qRound(greenF() * 255);
}

double ScColor::greenF() const
{
    if(m_model == ColorModel::RGB) return m_colorData.RGB_green;

    ScColor color = this->toRgb();
    return color.greenF();
}

int ScColor::blue() const
{
    return qRound(blueF() * 255);
}

double ScColor::blueF() const
{
    if(m_model == ColorModel::RGB) return m_colorData.RGB_blue;

    ScColor color = this->toRgb();
    return color.blueF();
}

int ScColor::cyan() const
{
    return qRound(cyanF() * 255);
}

double ScColor::cyanF() const
{
    if(m_model == ColorModel::CMYK) return m_colorData.CMYK_cyan;

    ScColor color = this->toCmyk();
    return color.cyanF();
}

int ScColor::magenta() const
{
    return qRound(magentaF() * 255);
}

double ScColor::magentaF() const
{
    if(m_model == ColorModel::CMYK) return m_colorData.CMYK_magenta;

    ScColor color = this->toCmyk();
    return color.magentaF();
}

int ScColor::yellow() const
{
    return qRound(yellowF() * 255);
}

double ScColor::yellowF() const
{
    if(m_model == ColorModel::CMYK) return m_colorData.CMYK_yellow;

    ScColor color = this->toCmyk();
    return color.yellowF();
}

int ScColor::black() const
{
    return qRound(blackF() * 255);
}

double ScColor::blackF() const
{
    if(m_model == ColorModel::CMYK) return m_colorData.CMYK_key;

    ScColor color = this->toCmyk();
    return color.blackF();
}

int ScColor::hue() const
{
    return qRound(hueF() * 359);
}

double ScColor::hueF() const
{

    if(m_model == ColorModel::HSV) return m_colorData.HSV_Hue;

    ScColor color = this->toHsv();
    return color.hueF();
}

int ScColor::saturation() const
{
    return qRound(saturationF() * 255);
}

double ScColor::saturationF() const
{
    if(m_model == ColorModel::HSV) return m_colorData.HSV_Saturation;

    ScColor color = this->toHsv();
    return color.saturationF();

}

int ScColor::value() const
{
    return qRound(valueF() * 255);
}

double ScColor::valueF() const
{
    if(m_model == ColorModel::HSV) return m_colorData.HSV_Value;

    ScColor color = this->toHsv();
    return color.valueF();

}

double ScColor::L() const
{
    if(m_model == ColorModel::Lab) return m_colorData.Lab_L;

    ScColor color = this->toLab();
    return color.L();
}

double ScColor::a() const
{
    if(m_model == ColorModel::Lab) return m_colorData.Lab_a;

    ScColor color = this->toLab();
    return color.a();
}

double ScColor::b() const
{
    if(m_model == ColorModel::Lab) return m_colorData.Lab_b;

    ScColor color = this->toLab();
    return color.b();
}

int ScColor::alpha() const
{
    return qRound(alphaF() * 255);
}

double ScColor::alphaF() const
{
    return m_colorData.alpha;
}

QString ScColor::name() const
{
    return QString("#%1%2%3").arg(red(), 2, 16, QLatin1Char( '0' )).arg(green(), 2, 16, QLatin1Char( '0' )).arg(blue(), 2, 16, QLatin1Char( '0' ));
}

int ScColor::shade() const
{
    return qRound(shadeF() * 255);
}

double ScColor::shadeF() const
{
    return m_colorData.shade;
}

/* ********************************************************************************* *
 *
 * Operator
 *
 * ********************************************************************************* */

QDebug operator<<(QDebug dbg, const ScColor &obj)
{
    // Qt debug output of QColor:
    // QColor(ARGB 1, 1, 0, 0.501961)

    dbg.nospace() << "ScColor(";

    switch(obj.getColorModel()){
    case ColorModel::RGB:
        dbg << "RGB " <<
               obj.red() << ", " <<
               obj.green() << ", " <<
               obj.blue() << ", " <<
               "A: " << obj.alpha() << ", " <<
               "S: " << obj.shade();
        break;
    case ColorModel::CMYK:
        dbg << "CMYK "<<
               obj.cyanF() << ", " <<
               obj.magentaF() << ", " <<
               obj.yellowF() << ", " <<
               obj.blackF() << ", " <<
               "A: " << obj.alphaF() << ", " <<
               "S: " << obj.shadeF();
        break;
    case ColorModel::HSV:
        dbg << "HSV "<<
               obj.hueF() << ", " <<
               obj.saturationF() << ", " <<
               obj.valueF() << ", " <<
               "A: " << obj.alphaF() << ", " <<
               "S: " << obj.shadeF();
        break;
    case ColorModel::Lab:
        dbg << "Lab "<<
               obj.L() << ", " <<
               obj.a() << ", " <<
               obj.b() << ", " <<
               "A: " << obj.alpha() << ", " <<
               "S: " << obj.shade();
        break;
    }

    dbg << ")";

    return dbg;//.maybeSpace();
}
