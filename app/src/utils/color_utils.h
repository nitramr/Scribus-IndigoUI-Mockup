#ifndef UTIL_COLOR_H
#define UTIL_COLOR_H

#include "sccolor.h"
#include <QPixmap>
#include <QColor>


class ColorUtils
{
public:
    ColorUtils();


    // Color
    static QColor colorBlend(QColor color1, QColor color2, double ratio);
    static ScColor colorBlend(ScColor color1, ScColor color2, double ratio);
    static QColor colorAlpha(QColor color, double alpha);
//    static QColor colorDarken(QColor color, double dark);
//    static QColor colorLighten(QColor color, double light);
    static QColor colorTint(QColor color, double tint);
    static QColor colorShade(QColor color, double shade);
    static QColor colorLuminosity(QColor color, double value);


};

#endif // UTIL_COLOR_H
