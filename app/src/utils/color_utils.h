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

    static double SCRIBUS_API getCurveYValue(FPointArray &curve, double x, bool linear = false);


    static QList<double> *Catmullrom2BezierAndViceVersa(QList<double> inputPoints, double taw, QString mode)
    {
        // Inspired by the explanation on: https://pomax.github.io/bezierinfo/#catmullconv

        QList<double> *result = new QList<double>();

        if (mode == "C2B") // if you want to convert from Catmull-Rom control points to Bezier Control points.
        {
            result->append(inputPoints[2]);
            result->append(inputPoints[3]);
            result->append(inputPoints[2] + (inputPoints[4] - inputPoints[0]) / (6 * taw));
            result->append(inputPoints[3] + (inputPoints[5] - inputPoints[1]) / (6 * taw));
            result->append(inputPoints[4] - (inputPoints[6] - inputPoints[2]) / (6 * taw));
            result->append(inputPoints[5] - (inputPoints[7] - inputPoints[3]) / (6 * taw));
            result->append(inputPoints[4]);
            result->append(inputPoints[5]);
        }
        else if (mode == "B2C") // if you want to convert from Bezier control points to Catmull-Rom Control points.
        {
            result->append(inputPoints[6] + 6 * (inputPoints[0] - inputPoints[2]));
            result->append(inputPoints[7] + 6 * (inputPoints[1] - inputPoints[3]));
            result->append(inputPoints[0]);
            result->append(inputPoints[1]);
            result->append(inputPoints[6]);
            result->append(inputPoints[7]);
            result->append(inputPoints[0] + 6 * (inputPoints[6] - inputPoints[4]));
            result->append(inputPoints[1] + 6 * (inputPoints[7] - inputPoints[5]));
        }
        return result;
    }


};

#endif // UTIL_COLOR_H
