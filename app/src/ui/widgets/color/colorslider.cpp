#include "colorslider.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QStyle>
#include <QStyleOption>
#include <QWidget>
#include <colorspace.h>
#include <util_render.h>
#include <QPainterPath>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

const int RADIUS = 6;

ColorSlider::ColorSlider(QWidget* parent) : ColorSlider(Mode::HSVHue, parent){}

ColorSlider::ColorSlider(Mode mode, QWidget *parent) : QSlider(parent)
{
    m_mode = mode;
    m_color = ScColor(255,0,0);

    setOrientation(Qt::Horizontal);
    setTickPosition(QSlider::TicksAbove);
    setup();
    updateValues();

}


/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

ColorSlider::Mode ColorSlider::mode()
{
    return m_mode;
}

/* ********************************************************************************* *
 *
 * Slots
 *
 * ********************************************************************************* */

void ColorSlider::setColor(ScColor color)
{
    m_color = color;
    updateValues();
    renderMap();
    update();
}

void ColorSlider::setMode(Mode mode)
{
    m_mode = mode;
    setup();
    updateValues();
    renderMap();
    update();
}

void ColorSlider::setValue(double value)
{
    //QSlider::setValue(qRound(value * 100));
    QSlider::setValue(value);
}

/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */

void ColorSlider::updateColor()
{
    switch(m_mode){
    case Mode::Alpha:
        m_color.setAlphaF(value() / (double)maximum());

        break;
    case Mode::Shade:
        m_color.setShadeF(value() / (double)maximum());

        break;
    case Mode::CMYKCyan:
        m_color.setCmykF(value() / (double)maximum(), m_color.magentaF(), m_color.yellowF(), m_color.blackF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::CMYKMagenta:
        m_color.setCmykF(m_color.cyanF(), value() / (double)maximum(), m_color.yellowF(), m_color.blackF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::CMYKYellow:
        m_color.setCmykF(m_color.cyanF(), m_color.magentaF(), value() / (double)maximum(), m_color.blackF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::CMYKKey:
        m_color.setCmykF(m_color.cyanF(), m_color.magentaF(), m_color.yellowF(), value() / (double)maximum(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::HSVHue:
        m_color.setHsvF(value() / (double)maximum(), m_color.saturationF(), m_color.valueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::HSVSaturation:
        m_color.setHsvF(m_color.hueF(), value() / (double)maximum(), m_color.valueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::HSVValue:
        m_color.setHsvF(m_color.hueF(), m_color.saturationF(), value() / (double)maximum(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::LabLightness:
        m_color.setLab(value() , m_color.a(), m_color.b(), m_color.alpha(), m_color.shade());

        break;
    case Mode::LabA:
        m_color.setLab(m_color.L(), value(), m_color.b(), m_color.alpha(), m_color.shade());

        break;
    case Mode::LabB:
        m_color.setLab(m_color.L(), m_color.a(), value(), m_color.alpha(), m_color.shade());

        break;
    case Mode::RGBRed:
        m_color.setRgbF(value() / (double)maximum(), m_color.greenF(), m_color.blueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::RGBGreen:
        m_color.setRgbF(m_color.redF(), value() / (double)maximum(), m_color.blueF(), m_color.alphaF(), m_color.shadeF());

        break;
    case Mode::RGBBlue:
        m_color.setRgbF(m_color.redF(), m_color.greenF(), value() / (double)maximum(), m_color.alphaF(), m_color.shadeF());
        break;

    }

    emit colorChanged(m_color);
}



void ColorSlider::setup()
{
    disconnectSlots();

    switch(m_mode){
    case Mode::Alpha:
    case Mode::CMYKCyan:
    case Mode::CMYKMagenta:
    case Mode::CMYKYellow:
    case Mode::CMYKKey:
    case Mode::HSVSaturation:
    case Mode::HSVValue:
    case Mode::LabLightness:
    case Mode::Shade:
        setMinimum(0);
        setMaximum(100);
        break;
    case Mode::HSVHue:
        setMinimum(0);
        setMaximum(359);
        break;
    case Mode::LabA:
    case Mode::LabB:
        setMinimum(-128);
        setMaximum(127);
        break;
    case Mode::RGBRed:
    case Mode::RGBGreen:
    case Mode::RGBBlue:
        setMinimum(0);
        setMaximum(255);
        break;

    }

    //    setPageStep(maximum() / 10);
    //    setSingleStep(maximum() / 100);

    connectSlots();
}

void ColorSlider::connectSlots()
{
    QAbstractSlider::connect(this, &QSlider::valueChanged, this, &ColorSlider::updateColor);
//    QAbstractSlider::connect(this, qOverload<int>(&QSlider::valueChanged),
//                             this, [=]() { emit this->valueChanged(value()); });

}

void ColorSlider::disconnectSlots()
{
    QAbstractSlider::disconnect(this, &QSlider::valueChanged, this, &ColorSlider::updateColor);
   // QAbstractSlider::disconnect(this, &QSlider::valueChanged, this, nullptr);
}

void ColorSlider::renderMap()
{
    int w = (orientation() == Qt::Horizontal) ? width() : 1;
    int h = (orientation() == Qt::Horizontal) ? 1 : height();

    int length = qMax(w,h);
    ScColor pixel;

    m_background = QImage(w,h, QImage::Format_ARGB32);
    m_background.fill(Qt::transparent);

    switch(m_mode){
    case Mode::Alpha:{

        for ( int x = 0; x < length; x++ )
        {
            qreal a = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setRgbF(m_color.redF(), m_color.greenF(), m_color.blueF(), a );
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgba());

        }

        break;
    }
    case Mode::Shade:{

        for ( int x = 0; x < length; x++ )
        {
            qreal s = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setRgbF(m_color.redF(), m_color.greenF(), m_color.blueF());
            pixel.setShadeF(s);
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    }
    case Mode::CMYKCyan:

        for ( int x = 0; x < length; x++ )
        {
            qreal c = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setCmykF(c, m_color.magentaF(), m_color.yellowF(), m_color.blackF() );
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::CMYKMagenta:

        for ( int x = 0; x < length; x++ )
        {
            qreal m = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setCmykF(m_color.cyanF(), m, m_color.yellowF(), m_color.blackF() );
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());
        }

        break;
    case Mode::CMYKYellow:
        for ( int x = 0; x < length; x++ )
        {
            qreal yl = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setCmykF(m_color.cyanF(), m_color.magentaF(), yl, m_color.blackF() );
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::CMYKKey:
        for ( int x = 0; x < length; x++ )
        {
            qreal k = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setCmykF(m_color.cyanF(), m_color.magentaF(), m_color.yellowF(), k );
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::HSVHue:{

        for ( int x = 0; x < length; x++ )
        {
            qreal hue = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setHsvF(hue, m_color.saturationF(), m_color.valueF());
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    }
    case Mode::HSVSaturation:

        for ( int x = 0; x < length; x++ )
        {
            qreal sat = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setHsvF(m_color.hueF(), sat, m_color.valueF());
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::HSVValue:

        for ( int x = 0; x < length; x++ )
        {
            qreal val = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setHsvF(m_color.hueF(), m_color.saturationF(), val);
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }
        break;
    case Mode::LabLightness:{

        ScColor lab = m_color.toLab();

        for ( int x = 0; x < length; x++ )
        {
            qreal l = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setLab(l * 100., lab.a(), lab.b());

            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

    }
        break;
    case Mode::LabA:{

        ScColor lab = m_color.toLab();

        for ( int x = 0; x < length; x++ )
        {
            qreal a = (orientation() == Qt::Horizontal) ? -(0.5 - qreal(x) / length) * 255. : (0.5 - qreal(x) / length) * 255.;
            pixel.setLab(lab.L(), a, lab.b());
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }
    }
        break;
    case Mode::LabB:{

        ScColor lab = m_color.toLab();

        for ( int x = 0; x < length; x++ )
        {
            qreal b = (orientation() == Qt::Horizontal) ? -(0.5 - qreal(x) / length) * 255. : (0.5 - qreal(x) / length) * 255.;
            pixel.setLab(lab.L(), lab.a(), b);
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }
    }
        break;
    case Mode::RGBRed:

        for ( int x = 0; x < length; x++ )
        {
            qreal r = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. -qreal(x) / length;

            pixel.setRgbF(r, m_color.greenF(), m_color.blueF());
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::RGBGreen:

        for ( int x = 0; x < length; x++ )
        {
            qreal g = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setRgbF(m_color.redF(), g, m_color.blueF());
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;
    case Mode::RGBBlue:

        for ( int x = 0; x < length; x++ )
        {
            qreal b = (orientation() == Qt::Horizontal) ? qreal(x) / length : 1. - qreal(x) / length;
            pixel.setRgbF(m_color.redF(), m_color.greenF(), b);
            m_background.setPixel(
                        (orientation() == Qt::Horizontal) ? x : 0,
                        (orientation() == Qt::Horizontal) ? 0 : x,
                        pixel.toQColor().rgb());

        }

        break;

    }
}

void ColorSlider::updateValues()
{
    disconnectSlots();

    switch(m_mode){
    case Mode::Alpha:
        QSlider::setValue(m_color.alphaF() * maximum());
        break;
    case Mode::Shade:
        QSlider::setValue(m_color.shadeF() * maximum());
        break;
    case Mode::CMYKCyan:
        QSlider::setValue(m_color.cyanF() * maximum());
        break;
    case Mode::CMYKMagenta:
        QSlider::setValue(m_color.magentaF() * maximum());
        break;
    case Mode::CMYKYellow:
        QSlider::setValue(m_color.yellowF() * maximum());
        break;
    case Mode::CMYKKey:
        QSlider::setValue(m_color.blackF() * maximum());
        break;
    case Mode::HSVHue:
        QSlider::setValue(m_color.hueF() * maximum());
        break;
    case Mode::HSVSaturation:
        QSlider::setValue(m_color.saturationF() * maximum());
        break;
    case Mode::HSVValue:
        QSlider::setValue(m_color.valueF() * maximum());
        break;
    case Mode::LabLightness:
        QSlider::setValue(m_color.L());
        break;
    case Mode::LabA:
        QSlider::setValue(m_color.a());
        break;
    case Mode::LabB:
        QSlider::setValue(m_color.b());
        break;
    case Mode::RGBRed:
        QSlider::setValue(m_color.redF() * maximum());
        break;
    case Mode::RGBGreen:
        QSlider::setValue(m_color.greenF() * maximum());
        break;
    case Mode::RGBBlue:
        QSlider::setValue(m_color.blueF() * maximum());
        break;

    }

    connectSlots();
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void ColorSlider::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e)

    QStyleOptionSlider opt;
    initStyleOption(&opt);

    opt.subControls = QStyle::SC_SliderGroove;
    if (tickPosition() != NoTicks)
        opt.subControls |= QStyle::SC_SliderTickmarks;
    if (isSliderDown()) {
        opt.state |= QStyle::State_Sunken;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    // Slider Area
    QRectF sliderArea = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRectF borderArea;
    qreal radius;


    if(orientation() == Qt::Horizontal){
        radius = sliderArea.height() / 2;
        sliderArea.adjust(0.5, 0., -0.5, 0.);
        borderArea = sliderArea.adjusted(0,-0.5, 0, 0.5);

    }else{
        radius = sliderArea.width() / 2;
        sliderArea.adjust(0, 0.5, 0., -0.5);
        borderArea = sliderArea.adjusted(-0.5,0, 0.5, 0);
    }

    QPainterPath border;
    border.addRoundedRect(borderArea, radius + .5, radius + .5);
    QPainterPath clip;
    clip.addRoundedRect(sliderArea, radius, radius);


    // Draw Slider Gradients
    painter.setClipPath(clip);

    switch(m_mode){
    case Mode::Alpha:
        UtilRender::renderPattern(&painter, sliderArea.toRect());
    default:
        painter.drawImage(sliderArea, m_background);
        break;
    }
    painter.setClipping(false);

    // Draw Slider Border
    painter.setPen(palette().color(QPalette::Mid));
    painter.setBrush( Qt::NoBrush );
    painter.drawPath(border);
    painter.setPen(Qt::NoPen);


    // Draw Handle
    QRect handle = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    UtilRender::renderCircularHandle(&painter, handle.center() + QPointF(0.5,0.5), RADIUS*2, Qt::NoBrush);


    //    opt.subControls = QStyle::SC_SliderHandle;
    //    opt.rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    //    style()->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);

    //    QPointF mousePos(opt.rect.center() + QPointF(0.5,0.5));
    //    painter.setBrush(m_color.toQColor());
    //    painter.setPen(QPen(palette().color(QPalette::WindowText), 1));
    //    painter.drawEllipse(mousePos, 3.5, 3.5);


    // Draw Ticker
    if(orientation() == Qt::Horizontal && this->tickPosition() != QSlider::NoTicks){
        QFont font = this->font();
        font.setPixelSize(8);
        painter.setFont(font);

        int interval = 4;
        int max = 100;
        int min = 0;

        switch(m_mode){
        case Mode::HSVHue:
            interval = 6;
            max = 360;
            break;
        case Mode::LabA:
        case Mode::LabB:
            interval = 4;
            min = 128;
            max = 256;
            break;
        case Mode::RGBRed:
        case Mode::RGBGreen:
        case Mode::RGBBlue:
            interval = 2;
            max = 256;
            break;
        default:
            break;

        }

        for(int x = 0; x <= interval; x++){
            QRect tick(x * (width()-1) /interval, sliderArea.top()-3, 1, 2);
            QString label = QString::number((x * max / interval) - min);
            int text = QFontMetrics(painter.font()).size(Qt::TextSingleLine, label).width();
            int offset = text / 2;

            if(x == 0) offset = 0;
            if(x == interval) offset = text;

            painter.setPen(palette().color(QPalette::WindowText));
            painter.drawText(tick.left() -offset, sliderArea.top()-4, label);
            painter.fillRect(tick, palette().color(QPalette::WindowText));
        }
    }

    painter.end();
}

void ColorSlider::resizeEvent(QResizeEvent *e)
{
    if (e->oldSize() != e->size()){
        //setup();
        renderMap();
    }
    QWidget::resizeEvent(e);
}


