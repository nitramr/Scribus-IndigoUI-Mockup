/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          sccolor.h  -  description
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

#ifndef SCCOLOR_H
#define SCCOLOR_H

#include <QColor>
#include "enums.h"
#include "structs.h"


class ScColor
{
public:
    /** \brief Constructs a ScColor with 4 Components set to 0 */
    ScColor();
    /** \brief Constructs a ScColor with 4 Components in the range from 0 - 255 */
    ScColor(int c, int m, int y, int k);
    /** \brief Constructs a RGB color with 3 Components in the range from 0 - 255 */
    ScColor(int r, int g, int b);
    /** \brief Constructs a Lab color with 3 Components */
    ScColor(double l, double a, double b);

    bool operator==(const ScColor& other) const;
    ScColor(const ScColor &) = default;
    ScColor &operator=(const ScColor &) = default;
    inline bool operator!=(const ScColor &color) const { return !(operator==(color)); }
    ~ScColor() = default;

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const ScColor &obj);
#endif

    // Set

    /** \brief Same as the Constructor but for an existing Color */
    void setColor(int c, int m, int y, int k, int alpha = 255, int shade = 255);

    /** \brief Same as the Constructor but for an existing Color */
    void setColorF(double c, double m, double y, double k, double alpha = 1.0, double shade = 1.0);

    /** \brief Define color as a CMYK color with specified values */
    void setCmyk(int c, int m, int y, int k, int alpha = 255, int shade = 255);

    /** \brief Define color as a CMYK color with specified values */
    void setCmykF(double c, double m, double y, double k, double alpha = 1.0, double shade = 1.0);

    /** \brief Define color as a RGB color with specified values */
    void setRgb(int r, int g, int b, int alpha = 255, int shade = 255);

    /** \brief Define color as a RGB color with specified values */
    void setRgbF(double r, double g, double b, double alpha = 1.0, double shade = 1.0);

    /** \brief Define color as a HSV color with specified values */
    void setHsv(int h, int s, int v, int alpha = 255, int shade = 255);

    /** \brief Define color as a HSV color with specified values */
    void setHsvF(double h, double s, double v, double alpha = 1.0, double shade = 1.0);

    /** \brief Define color as a Lab color with specified values */
    void setLab(double l, double a, double b, int alpha = 255, int shade = 255);

    void setAlpha(int alpha);
    void setAlphaF(double alpha);

    void setShade(int shade);
    void setShadeF(double shade);

    // From

    /** \brief Computes a ScColor for a QColor */
    void fromQColor(QColor color);

    // Get

    /** \brief Returns the 4 Values that form an ScColor.
        * Returns meaningful results only if color is a cmyk color.
        * Must not be called if color is the None Color. */
    void getCmyk(int *c, int *m, int *y, int *k) const;

    /** \brief Returns the 4 Values that form an ScColor.
        * Returns meaningful results only if color is a cmyk color.
        * Must not be called if color is the None Color. */
    void getCmykF(double *c, double *m, double *y, double *k) const;

    /** \brief Returns the 3 Values that form an RGBColor
        * Returns meaningful results only if color is a rgb color.
        * Must not be called if color is the None Color. */
    void getRgb(int *r, int *g, int *b) const;

    /** \brief Returns the 3 Values that form an RGBColor
        * Returns meaningful results only if color is a rgb color.
        * Must not be called if color is the None Color. */
    void getRgbF(double *r, double *g, double *b) const;

    /** \brief Returns the 3 Values that form an LabColor
        * Returns meaningful results only if color is a Lab color.
        * Must not be called if color is the None Color. */
    void getLab(double *L, double *a, double *b) const;

    /** \brief Returns the 3 Values that form an RGBColor
        * Returns meaningful results only if color is a rgb color.
        * Must not be called if color is the None Color. */
    void getHsv(int *h, int *s, int *v) const;

    /** \brief Returns the 3 Values that form an RGBColor
        * Returns meaningful results only if color is a rgb color.
        * Must not be called if color is the None Color. */
    void getHsvF(double *h, double *s, double *v) const;

    // To
    ScColor toRgb() const;
    ScColor toCmyk() const;
    ScColor toLab() const;
    ScColor toHsv() const;
    QColor toQColor() const;

    // Members

    /** \brief get the color model */
    ColorModel getColorModel () const;
    /** \brief If the color is a process color (ie neither spot, nor registration) */
    bool isProcessColor() const;
    /** \brief If the color is a spot color */
    bool isSpotColor() const;
    /** \brief Set a color to be a spot color or not. No effect if color is the None color. */
    void setSpotColor(bool s);
    /** \brief If the color is a registration color */
    bool isRegistrationColor() const;
    /** \brief Set a color to be a registration color or not. No effect if color is the None color. */
    void setRegistrationColor(bool r);

    bool isOutOfGamut() const;
    void setIsOutOfGamut(bool g);

    int red() const;
    double redF() const;
    int green() const;
    double greenF() const;
    int blue() const;
    double blueF() const;
    int cyan() const;
    double cyanF() const;
    int magenta() const;
    double magentaF() const;
    int yellow() const;
    double yellowF() const;
    int black() const;
    double blackF() const;
    int hue() const;
    double hueF() const;
    int saturation() const;
    double saturationF() const;
    int value() const;
    double valueF() const;
    double L() const;
    double a() const;
    double b() const;
    int alpha() const;
    double alphaF() const;
    QString name() const;
    int shade() const;
    double shadeF() const;


private:

    /** \brief Flag, true if the Color is a Spotcolor */
    bool m_spot {false};
    /** \brief Flag, true if the Color is a Registration color */
    bool m_register {false};
    bool m_outOfGamut {false};

    /** \brief Color model of the current color */
    ColorModel m_model {ColorModel::RGB};

    ColorData m_colorData;
};

#endif // SCCOLOR_H
