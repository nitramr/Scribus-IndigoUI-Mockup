/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#ifndef STRUCTS_H
#define STRUCTS_H

#include <QMap>
#include <QString>

#include "fpointarray.h"

struct IconSetData
{
    QString path;
    QString baseName;
    QString license;
    QString author;
    QString activeversion;
    bool isDefault;
    QMap<QString, QString> nameTranslations;
};


struct ColorData
{
    double RGB_red;
    double RGB_green;
    double RGB_blue;
    double CMYK_cyan;
    double CMYK_magenta;
    double CMYK_yellow;
    double CMYK_key;
    double Lab_L;
    double Lab_a;
    double Lab_b;
    double HSV_Hue;
    double HSV_Saturation;
    double HSV_Value;
    double alpha;
    double shade;
};


struct ArrowDesc
{
    QString name;
    bool userArrow { false };
    FPointArray points;
};


#endif // STRUCTS_H
