/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef _UTIL_MATH_H
#define _UTIL_MATH_H

#include "scribusapi.h"

class FPoint;
class FPointArray;

FPoint   SCRIBUS_API getMaxClipF(const FPointArray* clip);
FPoint   SCRIBUS_API getMinClipF(const FPointArray* clip);

#endif // UTILSMATH_H
