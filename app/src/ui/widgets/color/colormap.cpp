#include "colormap.h"

#include <QPainter>
#include <QResizeEvent>
#include <colorspace.h>
#include <helper.h>

const int RADIUS = 6;

ColorMap::ColorMap(QWidget *parent)
    : QWidget{parent}
{
    renderMap();
}



/* ********************************************************************************* *
 *
 * Slots
 *
 * ********************************************************************************* */

void ColorMap::setColor(ScColor color)
{
    m_color = color;
    renderMap();
    positionFromColor(m_color);
    update();
}

void ColorMap::setMode(Mode mode)
{
    m_drawMode = mode;
    renderMap();
    positionFromColor(m_color);
    update();
}


/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

QRect ColorMap::canvas()
{
    return rect().adjusted(RADIUS, RADIUS, -RADIUS, -RADIUS);
}

ColorMap::Mode ColorMap::mode()
{
    return m_drawMode;
}

ScColor ColorMap::color()
{
    return m_color;
}

/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */

QPointF ColorMap::posFromCanvas(QPointF pos)
{
    int w = canvas().width();
    int h = canvas().height();

    double wRatio = width() / w;
    double hRatio = height() / h;

    return QPointF(
                (pos.x() + RADIUS) * wRatio,
                (pos.y() + RADIUS) * hRatio
                );
}

QPointF ColorMap::posToCanvas(QPointF pos)
{
    int w = canvas().width();
    int h = canvas().height();

    double wRatio = width() / w;
    double hRatio = height() / h;


    return QPointF(
                qBound(0., (pos.x() - RADIUS) * wRatio, (double)w),
                qBound(0., (pos.y() - RADIUS) * hRatio, (double)h)
                );
}

void ColorMap::renderMap()
{

    int w = canvas().width();
    int h = canvas().height();

    m_colorMap = QImage(w,h, QImage::Format_ARGB32_Premultiplied);

    switch(m_drawMode){
    case Mode::HSVHue:
        drawHSVHue(w, h);
//        drawHSV(w, h, m_color.hueF());

        break;
    case Mode::HSVSaturation:
        drawHSVSaturation(w, h);
        break;
    case Mode::HSVValue:
        drawHSVValue(w, h);
        break;
    case Mode::LabA:
        drawLabA(w, h);
        break;
    case Mode::LabB:
        drawLabB(w, h);
        break;
    case Mode::LabLightness:
        drawLabLightness(w, h);
        break;
    case Mode::RGBBlue:
        drawRGBBlue(w, h);
        break;
    case Mode::RGBGreen:
        drawRGBGreen(w, h);
        break;
    case Mode::RGBRed:
        drawRGBRed(w, h);
        break;
    }

}

//void ColorMap::drawHSV(int w, int h, qreal base)
//{

//    for ( int y = 0; y < h; y++ )
//    {
//        qreal val = 1 - qreal(y) / h;
//        for ( int x = 0; x < w; x++ )
//        {
//            qreal sat = qreal(x) / w;
//            m_colorMap.setPixel( x, y, QColor::fromHsvF(base, sat, val).rgb());

//        }

//    }
//}

void ColorMap::drawHSVHue(int w, int h)
{

    qreal base = m_color.hueF();

    for ( int y = 0; y < h; y++ )
    {
        qreal val = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal sat = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromHsvF(base, sat, val).rgb());

        }

    }
}

void ColorMap::drawHSVSaturation(int w, int h)
{
    qreal base = m_color.saturationF();

    for ( int y = 0; y < h; y++ )
    {
        qreal val = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal hue = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromHsvF(hue, base, val).rgb());

        }

    }
}

void ColorMap::drawHSVValue(int w, int h)
{
    qreal base = m_color.valueF();

    for ( int y = 0; y < h; y++ )
    {
        qreal sat = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal hue = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromHsvF(hue, sat, base).rgb());

        }

    }
}

void ColorMap::drawRGBRed(int w, int h)
{
    qreal base = m_color.redF();

    for ( int y = 0; y < h; y++ )
    {
        qreal green = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal blue = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromRgbF(base, green, blue).rgb());

        }

    }
}

void ColorMap::drawRGBGreen(int w, int h)
{
    qreal base = m_color.greenF();

    for ( int y = 0; y < h; y++ )
    {
        qreal red = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal blue = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromRgbF(red, base, blue).rgb());

        }

    }
}

void ColorMap::drawRGBBlue(int w, int h)
{
    qreal base = m_color.blueF();

    for ( int y = 0; y < h; y++ )
    {
        qreal green = 1 - qreal(y) / h;
        for ( int x = 0; x < w; x++ )
        {
            qreal red = qreal(x) / w;
            m_colorMap.setPixel( x, y, QColor::fromRgbF(red, green, base).rgb());

        }

    }
}

void ColorMap::drawLabLightness(int w, int h)
{
    qreal base = m_color.L();

    for ( int y = 0; y < h; y++ )
    {
        qreal b = (0.5 - qreal(y) / h) * 255.;
        for ( int x = 0; x < w; x++ )
        {
            qreal a = -(0.5 - qreal(x) / w) * 255.;
            m_colorMap.setPixel( x, y, ScColor(base, a,b).toQColor().rgb());
        }

    }
}

void ColorMap::drawLabA(int w, int h)
{
    qreal base = m_color.a() ;

    for ( int y = 0; y < h; y++ )
    {
        qreal L = (1.0 - qreal(y) / h) * 100.;
        for ( int x = 0; x < w; x++ )
        {
            qreal b = -(0.5 - qreal(x) / w) * 255.;
            m_colorMap.setPixel( x, y, ScColor(L, base, b).toQColor().rgb());
        }

    }
}

void ColorMap::drawLabB(int w, int h)
{
    qreal base = m_color.b();

    for ( int y = 0; y < h; y++ )
    {
        qreal L = (1.0 - qreal(y) / h) * 100.;
        for ( int x = 0; x < w; x++ )
        {
            qreal a = -(0.5 - qreal(x) / w) * 255.;
            m_colorMap.setPixel( x, y, ScColor(L, a, base).toQColor().rgb());
        }

    }
}

void ColorMap::colorFromPosition(QPointF pos)
{
    int w = canvas().width();
    int h = canvas().height();

    m_mark = posToCanvas(pos);

    double mX = qBound(0.0, qreal(m_mark.x()) / w, 1.0);
    double mY = qBound(0.0, 1 - qreal(m_mark.y()) / h, 1.0);


    switch(m_drawMode){
    case Mode::HSVHue:
        m_color.setHsvF(m_color.hueF(), mX, mY, m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::HSVSaturation:
        m_color.setHsvF(mX, m_color.saturationF(), mY, m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::HSVValue:
        m_color.setHsvF(mX, mY, m_color.valueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::LabA:
        mX = qBound(-128., -(128 - qreal(m_mark.x()) / w * 255), 127.);
        m_color.setLab(mY * 100, m_color.a(), mX, m_color.alpha(), m_color.shade());

        break;
    case Mode::LabB:
        mX = qBound(-128., -(128 - qreal(m_mark.x()) / w * 255), 127.);
        m_color.setLab(mY * 100, mX, m_color.b(), m_color.alpha(), m_color.shade());

        break;
    case Mode::LabLightness:
        mX = qBound(-128., -(128 - qreal(m_mark.x()) / w * 255), 127.);
        mY = qBound(-128., 128 - qreal(m_mark.y()) / h * 255, 127.);
        m_color.setLab(m_color.L(), mX, mY, m_color.alpha(), m_color.shade());

        break;
    case Mode::RGBBlue:
        m_color.setRgbF(mX, mY, m_color.blueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::RGBGreen:
        m_color.setRgbF(mY, m_color.greenF(), mX, m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::RGBRed:
        m_color.setRgbF(m_color.redF(), mY, mX, m_color.alphaF(), m_color.shadeF());

        break;
    }


    emit colorChanged(m_color);
}

void ColorMap::positionFromColor(ScColor color)
{
    double mX = 0;
    double mY = 0;
    int w = canvas().width();
    int h = canvas().height();

    switch(m_drawMode){
    default:
    case Mode::HSVHue:
        mX = color.saturationF() * w;
        mY = h - color.valueF() * h;
        break;
    case Mode::HSVSaturation:
        mX = color.hueF() * w;
        mY = h - color.valueF() * h;
        break;
    case Mode::HSVValue:
        mX = color.hueF() * w;
        mY = h - color.saturationF() * h;
        break;
    case Mode::LabA:
        mX = w - (128. - color.b()) / 255. * w;
        mY = h - color.L() / 100. * h;
        break;
    case Mode::LabB:
        mX = w - (128. - color.a()) / 255. * w;
        mY = h - color.L() / 100. * h;
        break;
    case Mode::LabLightness:
        mX = w - (128. - color.a()) / 255. * w;
        mY = (128. - color.b()) / 255. * h;
        break;
    case Mode::RGBBlue:
        mX = color.redF() * w;
        mY = h - color.greenF() * h;
        break;
    case Mode::RGBGreen:
        mX = color.blueF() * w;
        mY = h - color.redF() * h;
        break;
    case Mode::RGBRed:
        mX = color.blueF() * w;
        mY = h - color.greenF() * h;
        break;
    }

    m_mark = QPointF(mX, mY);
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void ColorMap::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);

    // Draw Map
    painter.drawImage(canvas(), m_colorMap);

    // Draw Pointer
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor col(m_color.red(), m_color.green(), m_color.blue());
    Helper::renderColorHandle(&painter, posFromCanvas(m_mark) + QPointF(.5,.5), RADIUS, QBrush(col));

    painter.end();
}

void ColorMap::resizeEvent(QResizeEvent *e)
{
    if (e->oldSize() != e->size()){

        renderMap();
        positionFromColor(m_color);
    }
    QWidget::resizeEvent(e);
}

void ColorMap::mouseMoveEvent(QMouseEvent *e)
{
    colorFromPosition(e->position());
    update();
}

void ColorMap::mousePressEvent(QMouseEvent *e)
{
    colorFromPosition(e->position());
    update();
}

void ColorMap::mouseReleaseEvent(QMouseEvent *e)
{
    colorFromPosition(e->position());
}

