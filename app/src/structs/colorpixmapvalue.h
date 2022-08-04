#ifndef COLORPIXMAPVALUE_H
#define COLORPIXMAPVALUE_H

#include <QMetaType>

#include "sccolor.h"

struct ColorPixmapValue
{
    ScColor m_color;
    QString m_name { "invalid" };

    ColorPixmapValue() = default;
    ColorPixmapValue(const ColorPixmapValue& other) : m_color(other.m_color), m_name(other.m_name) {}
    ColorPixmapValue(const ScColor& col, const QString& colName) : m_color(col),m_name(colName) {}
    ColorPixmapValue& operator= (const ColorPixmapValue& other)
    {
        m_color = other.m_color;
        m_name = other.m_name;
        return *this;
    }

    ~ColorPixmapValue() = default;

};

Q_DECLARE_METATYPE(ColorPixmapValue);

#endif // COLORPIXMAPVALUE_H
