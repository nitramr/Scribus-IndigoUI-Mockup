/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          util.cpp  -  description
                             -------------------
    begin                : Fri Sep 14 2001
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

#include "util.h"


void getDashArray(int dashtype, double linewidth, QVector<double> &dashArray)
{
    dashArray.clear();
    if ((dashtype == 1) || (dashtype == 0))
        return;
    double Dt = qMax(1.0*linewidth, 0.1);
    double Sp = qMax(2.0*linewidth, 0.1);
    double Da = qMax(4.0*linewidth, 0.1);
    switch (dashtype)
    {
        case 1:
            break;
        case 2:
            dashArray << Da << Sp;
            break;
        case 3:
            dashArray << Dt << Sp;
            break;
        case 4:
            dashArray << Da << Sp << Dt << Sp;
            break;
        case 5:
            dashArray << Da << Sp << Dt << Sp << Dt << Sp;
            break;
// Additional line styles taken from Inkscape
        case 6:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 7:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(3.0 * linewidth, 0.01);
            break;
        case 8:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(4.0 * linewidth, 0.01);
            break;
        case 9:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(6.0 * linewidth, 0.01);
            break;
        case 10:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(8.0 * linewidth, 0.01);
            break;
        case 11:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(12.0 * linewidth, 0.01);
            break;
        case 12:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(24.0 * linewidth, 0.01);
            break;
        case 13:
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(48.0 * linewidth, 0.01);
            break;
        case 14:
            dashArray << qMax(2.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 15:
            dashArray << qMax(3.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 16:
            dashArray << qMax(4.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 17:
            dashArray << qMax(6.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 18:
            dashArray << qMax(8.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 19:
            dashArray << qMax(10.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 20:
            dashArray << qMax(12.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 21:
            dashArray << qMax(2.0 * linewidth, 0.01) << qMax(2.0 * linewidth, 0.01);
            break;
        case 22:
            dashArray << qMax(3.0 * linewidth, 0.01) << qMax(3.0 * linewidth, 0.01);
            break;
        case 23:
            dashArray << qMax(4.0 * linewidth, 0.01) << qMax(4.0 * linewidth, 0.01);
            break;
        case 24:
            dashArray << qMax(6.0 * linewidth, 0.01) << qMax(6.0 * linewidth, 0.01);
            break;
        case 25:
            dashArray << qMax(8.0 * linewidth, 0.01) << qMax(8.0 * linewidth, 0.01);
            break;
        case 26:
            dashArray << qMax(10.0 * linewidth, 0.01) << qMax(10.0 * linewidth, 0.01);
            break;
        case 27:
            dashArray << qMax(12.0 * linewidth, 0.01) << qMax(12.0 * linewidth, 0.01);
            break;
        case 28:
            dashArray << qMax(2.0 * linewidth, 0.01) << qMax(4.0 * linewidth, 0.01);
            break;
        case 29:
            dashArray << qMax(2.0 * linewidth, 0.01) << qMax(6.0 * linewidth, 0.01);
            break;
        case 30:
            dashArray << qMax(6.0 * linewidth, 0.01) << qMax(2.0 * linewidth, 0.01);
            break;
        case 31:
            dashArray << qMax(4.0 * linewidth, 0.01) << qMax(8.0 * linewidth, 0.01);
            break;
        case 32:
            dashArray << qMax(8.0 * linewidth, 0.01) << qMax(4.0 * linewidth, 0.01);
            break;
        case 33:
            dashArray << qMax(2.0 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            dashArray << qMax(0.5 * linewidth, 0.01) << qMax(1.0 * linewidth, 0.01);
            break;
        case 34:
            dashArray << qMax(8.0 * linewidth, 0.01) << qMax(2.0 * linewidth, 0.01);
            dashArray << qMax(1.0 * linewidth, 0.01) << qMax(2.0 * linewidth, 0.01);
            break;
        case 35:
            dashArray << qMax(0.5 * linewidth, 0.01) << qMax(0.5 * linewidth, 0.01);
            break;
        case 36:
            dashArray << qMax(0.25 * linewidth, 0.01) << qMax(0.25 * linewidth, 0.01);
            break;
        case 37:
            dashArray << qMax(0.1 * linewidth, 0.01) << qMax(0.1 * linewidth, 0.01);
            break;
        default:
            break;
    }
}
