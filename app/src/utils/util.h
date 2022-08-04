/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef _UTIL_H
#define _UTIL_H

#include <QVector>

#include "scribusapi.h"

void    SCRIBUS_API getDashArray(int dashtype, double linewidth, QVector<double> &dashArray);
void    SCRIBUS_API getDashArray(int dashtype, double linewidth, QVector<float> &dashArray);

#endif // UTIL_H
