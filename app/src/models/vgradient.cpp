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

#include <algorithm>
#include <QMutableListIterator>

#include "vgradient.h"

// colorStop comparison function for stable_sort function
bool compareStops(const VColorStop* item1, const VColorStop* item2 )
{
    double r1 = item1->rampPoint;
    double r2 = item2->rampPoint;
    return (r1 < r2);
}

int VGradient::compareItems(const VColorStop* item1, const VColorStop* item2 ) const
{
    double r1 = item1->rampPoint;
    double r2 = item2->rampPoint;

    return (r1 == r2 ? 0 : r1 < r2 ? -1 : 1);
}

void VGradient::inSort(VColorStop* d)
{
    int index = 0;
    VColorStop *n = m_colorStops.value(index);
    while (n && compareItems(n,d) <= 0)
    {
        ++index;
        n = m_colorStops.value(index);
    }
    m_colorStops.insert( qMin(index, m_colorStops.size()), d );
}

VGradient::VGradient(GradientType type) : m_type( type )
{
    // set up dummy gradient
    ScColor color;

    color = ScColor(255, 255, 255);
    addStop( color, 0.0, 0.5, 1.0 );

    color = ScColor(0, 0, 0);
    addStop( color, 1.0, 0.5, 1.0 );

    setOrigin( QPointF( 0, 0 ) );
    setVector( QPointF( 0, 50 ) );
    setRepeatMethod( VGradient::pad );
}

VGradient::VGradient(const VGradient& gradient)
{
    m_origin		= gradient.m_origin;
    m_focalPoint	= gradient.m_focalPoint;
    m_vector		= gradient.m_vector;
    m_type			= gradient.m_type;
    m_repeatMethod	= gradient.m_repeatMethod;

    clearStops();

    QList<VColorStop*> cs = gradient.colorStops();
    std::stable_sort(cs.begin(), cs.end(), compareStops);
    for (int i = 0; i < cs.count(); ++i)
        m_colorStops.append( new VColorStop(*cs[i]) );
}

VGradient::~VGradient()
{
    clearStops();
}

VGradient& VGradient::operator=(const VGradient& gradient)
{
    if (this == &gradient)
        return *this;

    m_origin		= gradient.m_origin;
    m_focalPoint	= gradient.m_focalPoint;
    m_vector		= gradient.m_vector;
    m_type			= gradient.m_type;
    m_repeatMethod	= gradient.m_repeatMethod;

    clearStops();

    QList<VColorStop*> cs = gradient.colorStops();
    std::stable_sort(cs.begin(), cs.end(), compareStops);
    for (int i = 0; i < cs.count(); ++i)
        m_colorStops.append( new VColorStop( *cs[i] ) );
    return *this;
}

bool VGradient::operator==(const VGradient &gradient) const
{
    if (m_colorStops.count() != gradient.stops())
        return false;
    const QList<VColorStop*>& cs = gradient.colorStops();

    bool retVal = true;
    for (int i = 0; i < m_colorStops.count(); ++i)
    {
        if (m_colorStops.at(i)->rampPoint != cs.at(i)->rampPoint)
        {
            retVal = false;
            break;
        }
        if (m_colorStops.at(i)->opacity != cs.at(i)->opacity)
        {
            retVal = false;
            break;
        }
        if (m_colorStops.at(i)->name != cs.at(i)->name)
        {
            retVal = false;
            break;
        }
        if (m_colorStops.at(i)->shade != cs.at(i)->shade)
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}

const QList<VColorStop*>& VGradient::colorStops() const
{
    return m_colorStops;
}

void VGradient::clearStops()
{
    while (!m_colorStops.isEmpty())
        delete m_colorStops.takeFirst();
}

void VGradient::addStop(const VColorStop& colorStop)
{
    inSort( new VColorStop( colorStop ) );
}

void VGradient::addStop(const ScColor &color, double rampPoint, double midPoint, double opa, const QString& name, double shade)
{
    // Clamping between 0.0 and 1.0
    rampPoint   = qBound(0., rampPoint, 1.);
    midPoint    = qBound(0., midPoint, 1.);
    shade       = qBound(0., shade, 1.);
    opa         = qBound(0., opa, 1.);

    inSort( new VColorStop( rampPoint, midPoint, color, opa, name, shade ) );
}

void  VGradient::setStop(const ScColor &color, double rampPoint, double midPoint, double opa, const QString& name, double shade)
{
    for (int i = 0; i < m_colorStops.count(); ++i)
    {
        if (m_colorStops.at(i)->rampPoint == rampPoint)
        {
            delete m_colorStops.takeAt(i);
            break;
        }
    }
    addStop(color, rampPoint, midPoint, opa, name, shade);
}

void VGradient::removeStop(VColorStop& colorstop)
{
    int n = m_colorStops.indexOf(&colorstop);
    if (n >= 0)
        delete m_colorStops.takeAt(n);
}

void VGradient::removeStop(int n)
{
    delete m_colorStops.takeAt(n);
}

void VGradient::filterStops()
{
    VColorStop* colorStop = nullptr;
    bool zeroFound = false;
    QMutableListIterator<VColorStop*> i(m_colorStops);
    i.toBack();
    while (i.hasPrevious())
    {
        colorStop = i.previous();
        if (colorStop->rampPoint == 0.0 && zeroFound)
        {
            delete i.value();
            i.remove();
        }
        else if (colorStop->rampPoint == 0.0)
            zeroFound = true;
    }
    bool oneFound = false;
    i.toFront();
    while (i.hasNext())
    {
        colorStop = i.next();
        if (colorStop->rampPoint == 1.0 && oneFound)
        {
            delete i.value();
            i.remove();
        }
        else if (colorStop->rampPoint == 1.0)
            oneFound = true;
    }
}

void VGradient::transform( const QTransform &m )
{
    double mx, my;
    mx = m.m11() * m_origin.x() + m.m21() * m_origin.y() + m.dx();
    my = m.m22() * m_origin.y() + m.m12() * m_origin.x() + m.dy();
    m_origin = QPointF(mx, my);
    mx = m.m11() * m_focalPoint.x() + m.m21() * m_focalPoint.y() + m.dx();
    my = m.m22() * m_focalPoint.y() + m.m12() * m_focalPoint.x() + m.dy();
    m_focalPoint = QPointF(mx, my);
    mx = m.m11() * m_vector.x() + m.m21() * m_vector.y() + m.dx();
    my = m.m22() * m_vector.y() + m.m12() * m_vector.x() + m.dy();
    m_vector = QPointF(mx, my);
}

QLinearGradient VGradient::toQLinearGradient()
{
    QLinearGradient gradient;

    foreach(VColorStop *stop, colorStops()){
        gradient.setColorAt(stop->rampPoint, stop->color.toQColor());
    }

    return gradient;
}

QRadialGradient VGradient::toQRadialGradient()
{
    QRadialGradient gradient;
    gradient.setCenter(m_origin);
    gradient.setFocalPoint(m_focalPoint);

    foreach(VColorStop *stop, colorStops()){
        gradient.setColorAt(stop->rampPoint, stop->color.toQColor());
    }

    return gradient;
}

QConicalGradient VGradient::toQConicalGradient()
{
    QConicalGradient gradient;
    gradient.setCenter(m_origin);

    foreach(VColorStop *stop, colorStops()){
        gradient.setColorAt(stop->rampPoint, stop->color.toQColor());
    }

    return gradient;
}
