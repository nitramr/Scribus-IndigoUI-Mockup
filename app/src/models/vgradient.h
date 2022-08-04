/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/* This file is part of the KDE project
   Copyright (C) 2002, The Karbon Developers

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef VGRADIENT_H
#define VGRADIENT_H


#include <QColor>
#include <QList>
#include <QTransform>

#include "enums.h"
#include <QLinearGradient>
#include "sccolor.h"
#include "scribusapi.h"

class SCRIBUS_API VColorStop
{
public:
    VColorStop(double r, double m, const ScColor& c, double o, const QString& n, int s)
    {
        rampPoint = r;
        midPoint = m;
        color = c;
        opacity = o;
        name = n;
        shade = s;
    }

    VColorStop(const VColorStop& colorStop)
    {
        rampPoint = colorStop.rampPoint;
        midPoint = colorStop.midPoint;
        color = colorStop.color;
        opacity = colorStop.opacity;
        name = colorStop.name;
        shade = colorStop.shade;
    }

    ScColor color;

    // relative position of color point (0.0-1.0):
    double rampPoint;

    // relative position of midpoint (0.0-1.0)
    // between two ramp points. ignored for last VColorStop.
    double midPoint;
    double opacity;
    double shade;
    QString name;

    friend inline bool operator== (const VColorStop& s1, const VColorStop& s2)
    {
        return s1.rampPoint == s2.rampPoint;
    }
};

// comparison function for use with stable_sort
bool compareStops(const VColorStop* item1, const VColorStop* item2);

class SCRIBUS_API VGradient
{
    // friend class VGradientWidget;

public:
//    enum VGradientType
//    {
//        linear = 0,
//        radial = 1,
//        fourcolor  = 2,
//        diamond = 3,
//        mesh = 4,
//        freemesh = 5
//    };

    enum VGradientRepeatMethod
    {
        none    = 0,
        reflect = 1,
        repeat  = 2,
        pad     = 3
    };

    VGradient(GradientType type = GradientType::Linear);
    VGradient(const VGradient& gradient);
    ~VGradient();

    VGradient& operator=(const VGradient& gradient);
    bool operator==(const VGradient& gradient) const;

    GradientType type() const { return m_type; }
    void setType(GradientType type) { m_type = type; }

    VGradientRepeatMethod repeatMethod() const { return m_repeatMethod; }
    void setRepeatMethod(VGradientRepeatMethod repeatMethod) { m_repeatMethod = repeatMethod; }

    const QList<VColorStop*>& colorStops() const;
    void addStop(const VColorStop& colorStop);
    void addStop(const ScColor &color, double rampPoint, double midPoint, double opa, const QString& name = QString(), double shade = 1.);
    void setStop(const ScColor &color, double rampPoint, double midPoint, double opa, const QString& name = QString(), double shade = 1.);
    void removeStop(VColorStop& colorStop);
    void removeStop(int n);
    void clearStops();
    int  stops() const { return m_colorStops.count(); }

    // This function let only one stop with offset value equal to 0 and 1.0
    // by removing the firsts with 0.0 value and the lasts with 1.0 value;
    void filterStops();

    QPointF origin() const { return m_origin; }
    void setOrigin(const QPointF &origin) { m_origin = origin; }

    QPointF focalPoint() const { return m_focalPoint; }
    void setFocalPoint(const QPointF &focalPoint) { m_focalPoint = focalPoint; }

    QPointF vector() const { return m_vector; }
    void setVector(const QPointF &vector) { m_vector = vector; }

    void transform(const QTransform& m);

    QLinearGradient toQLinearGradient();
    QRadialGradient toQRadialGradient();
    QConicalGradient toQConicalGradient();

protected:
    QList<VColorStop*> m_colorStops;

    int  compareItems(const VColorStop* item1, const VColorStop* item2 ) const;
    void inSort(VColorStop* d);

private:
    GradientType m_type;
    VGradientRepeatMethod m_repeatMethod	: 3;

    // coordinates:
    QPointF m_origin;
    QPointF m_focalPoint;
    QPointF m_vector;
};

#endif // VGRADIENT_H
