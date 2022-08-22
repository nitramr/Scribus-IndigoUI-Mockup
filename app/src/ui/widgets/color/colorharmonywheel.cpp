#include "colorharmonywheel.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include "util_render.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

const int RADIUS = 6;

ColorHarmonyWheel::ColorHarmonyWheel(QWidget *parent)
    : QWidget{parent}
{
    setup();
    renderMap();
}


void ColorHarmonyWheel::setup()
{

    m_colors.insert(Color::Main,     QPair<QPointF,ScColor>(rect().center(), ScColor(255,0,0)) ); // red
    m_colors.insert(Color::Variant1, QPair<QPointF,ScColor>(rect().center(), ScColor(255,255,0)) ); // yellow
    m_colors.insert(Color::Variant2, QPair<QPointF,ScColor>(rect().center(), ScColor(0,255,0)) ); // green
    m_colors.insert(Color::Variant3, QPair<QPointF,ScColor>(rect().center(), ScColor(0,255,255)) ); // cyan
    m_colors.insert(Color::Variant4, QPair<QPointF,ScColor>(rect().center(), ScColor(0,0,255)) ); // blue

    m_harmony = ColorHarmonyWheel::Complementary;
    m_value = 1.;
    m_alpha = 1.;


}

/* ********************************************************************************* *
 *
 * Slots
 *
 * ********************************************************************************* */

void ColorHarmonyWheel::setHarmony(Harmony harmony)
{
    m_harmony = harmony;
    ScColor col = color(ColorHarmonyWheel::Main);
    positionFromColor(col);
    update();
    emit colorChanged(col);
    emit harmonyChanged(m_harmony);
}

void ColorHarmonyWheel::setColor(ScColor color)
{
    positionFromColor(color);
    renderMap();
    update();
}



/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */

void ColorHarmonyWheel::positionFromColor(ScColor color)
{

    double radius = canvas().width()/2.;
    QPointF center = canvas().center();
    QLineF *line = new QLineF();

    double hue = color.hue();
    double sat = qBound(0., radius * color.saturationF(), radius);
    m_value = color.valueF();
    m_alpha = color.alphaF();
    m_shade = color.shadeF();

    QPointF posClamp = line->fromPolar( sat, hue ).p2() + center;

    updateRingMarker(posClamp);

}

void ColorHarmonyWheel::updateRingMarker(QPointF pos)
{
    updateColorPoint(ColorHarmonyWheel::Main, pos, 0.);

    // Reference: https://www.canva.com/colors/color-wheel/
    // Angles based on 12 color wheel
    // if custom angles are supported add them here!

    switch(m_harmony){
    case ColorHarmonyWheel::Complementary:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, 180 );
        break;
    case ColorHarmonyWheel::SplitComplementary:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, 220 );
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, 150 );
        break;
    case ColorHarmonyWheel::Monochromatic:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, 0., .7);
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, 0., .4);
        updateColorPoint(ColorHarmonyWheel::Variant3, pos, 0., .1);
        break;
    case ColorHarmonyWheel::Tetradic:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, -30 );
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, 180 );
        updateColorPoint(ColorHarmonyWheel::Variant3, pos, 150 );
        break;
    case ColorHarmonyWheel::Triadic:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, -120 );
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, 120 );
        break;
    case ColorHarmonyWheel::Analogous:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, -15 );
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, -30 );
        updateColorPoint(ColorHarmonyWheel::Variant3, pos, 15 );
        updateColorPoint(ColorHarmonyWheel::Variant4, pos, 30 );
        break;
    case ColorHarmonyWheel::Square:
        updateColorPoint(ColorHarmonyWheel::Variant1, pos, 90 );
        updateColorPoint(ColorHarmonyWheel::Variant2, pos, 180 );
        updateColorPoint(ColorHarmonyWheel::Variant3, pos, 270 );
        break;
    default:
        break;

    }

}

void ColorHarmonyWheel::updateColorPoint(Color color, QPointF pos, double angle, double s)
{
    s = qBound(0., s, 1.);
    QPointF center = canvas().center();
    QLineF *line = new QLineF(center, pos);
    double radius = canvas().width()/2.;
    double length = qBound(0., line->length(), radius) * s;
    angle = line->angle() + angle;
    double sat = length / radius;


    QPointF posClamp = line->fromPolar( length, angle ).p2() + center;

    ScColor colMain = ScColor();
    colMain.fromQColor( QColor::fromHsvF(normalizeAngle(angle) / 360., sat, m_value , m_alpha) );
    colMain.setShadeF(m_shade);

    m_colors.find(color)->first = posClamp;
    m_colors.find(color)->second = colMain;
}

double ColorHarmonyWheel::normalizeAngle(double angle)
{
    return ( angle - ( floor( angle / 360. ) * 360. ) ) ;
}

void ColorHarmonyWheel::renderMap()
{
    m_map = QImage(canvas().width(), canvas().height(), QImage::Format_ARGB32);
    m_map.fill(Qt::transparent);

    QPainter painter(&m_map);
    painter.setRenderHint(QPainter::Antialiasing, true);

    double radius = m_map.width()/2.;
    QRect rect = m_map.rect().adjusted(1,1,-1,-1);

    for (int angle = 0; angle < 360; ++angle) {

        QRadialGradient gradient(rect.center(), radius);
        gradient.setColorAt(0, QColor::fromHsvF(0, 0, m_value));
        gradient.setColorAt(1, QColor::fromHsvF(angle / 360., 1., m_value));

        QBrush brush(gradient);
        QPen pen(brush, 1.0);
        painter.setPen(pen);
        painter.setBrush(brush);
        // The startAngle and spanAngle must be specified in 1/16th of a degree
        painter.drawPie(rect, angle * 16, 16);
    }

    painter.end();
}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

ColorHarmonyWheel::Harmony ColorHarmonyWheel::harmony()
{
    return m_harmony;
}

ScColor ColorHarmonyWheel::color(Color color)
{
    return m_colors.find(color).value().second;
}

QPointF ColorHarmonyWheel::position(Color color)
{
    return m_colors.find(color).value().first;
}

QMap<ColorHarmonyWheel::Color, ScColor> ColorHarmonyWheel::colors()
{
    QMap<ColorHarmonyWheel::Color, ScColor> colList;

    colList.insert( ColorHarmonyWheel::Main, color(ColorHarmonyWheel::Main) );
    colList.insert( ColorHarmonyWheel::Variant1, color(ColorHarmonyWheel::Variant1) );
    colList.insert( ColorHarmonyWheel::Variant2, color(ColorHarmonyWheel::Variant2) );
    colList.insert( ColorHarmonyWheel::Variant3, color(ColorHarmonyWheel::Variant3) );
    colList.insert( ColorHarmonyWheel::Variant4, color(ColorHarmonyWheel::Variant4) );

    return colList;
}


QPainterPath ColorHarmonyWheel::wheel()
{
    QPainterPath path;
    path.addEllipse(canvas());

    return path;
}

QRect ColorHarmonyWheel::canvas()
{
    int side = qMin(height(), width());

    int x = 0;
    int y = 0;

    if(height() != side){
        y = (height() - side) / 2;
    }

    if(width() != side){
        x = (width() - side) / 2;
    }

    return QRect(x,y,side,side).adjusted(RADIUS,RADIUS,-RADIUS,-RADIUS);
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void ColorHarmonyWheel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);


    // Draw Rainbow Wheel
    painter.drawImage(canvas(), m_map);


    // Draw Marker
    QPair<QPointF, ScColor> marker;

    // Transparency fix
//    QColor colMain = color(ColorHarmonyWheel::Main).toQColor();
//    colMain.setAlphaF(1);
//    QColor col1 = color(ColorHarmonyWheel::Variant1).toQColor();
//    col1.setAlphaF(1);
//    QColor col2 = color(ColorHarmonyWheel::Variant2).toQColor();
//    col2.setAlphaF(1);
//    QColor col3 = color(ColorHarmonyWheel::Variant3).toQColor();
//    col3.setAlphaF(1);
//    QColor col4 = color(ColorHarmonyWheel::Variant4).toQColor();
//    col4.setAlphaF(1);

    QColor colMain( color(ColorHarmonyWheel::Main).red(), color(ColorHarmonyWheel::Main).green(), color(ColorHarmonyWheel::Main).blue() );
    QColor col1( color(ColorHarmonyWheel::Variant1).red(), color(ColorHarmonyWheel::Variant1).green(), color(ColorHarmonyWheel::Variant1).blue() );
    QColor col2( color(ColorHarmonyWheel::Variant2).red(), color(ColorHarmonyWheel::Variant2).green(), color(ColorHarmonyWheel::Variant2).blue() );
    QColor col3( color(ColorHarmonyWheel::Variant3).red(), color(ColorHarmonyWheel::Variant3).green(), color(ColorHarmonyWheel::Variant3).blue() );
    QColor col4( color(ColorHarmonyWheel::Variant4).red(), color(ColorHarmonyWheel::Variant4).green(), color(ColorHarmonyWheel::Variant4).blue() );


    UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Main) + QPointF(.5,.5), RADIUS*2, QBrush(colMain) );

    switch(m_harmony){
    case ColorHarmonyWheel::Complementary:
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant1) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col1) );

        break;
    case ColorHarmonyWheel::SplitComplementary:
    case ColorHarmonyWheel::Triadic:
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant1) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col1) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant2) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col2) );

        break;
    case ColorHarmonyWheel::Tetradic:
    case ColorHarmonyWheel::Square:
    case ColorHarmonyWheel::Monochromatic:
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant1) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col1) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant2) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col2) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant3) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col3) );

        break;
    case ColorHarmonyWheel::Analogous:
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant1) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col1) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant2) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col2) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant3) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col3) );
        UtilRender::renderCircularHandle(&painter, position(ColorHarmonyWheel::Variant4) + QPointF(.5,.5), RADIUS*2 - 2, QBrush(col4) );
        break;
    default:
        break;

    }


    painter.end();

}

void ColorHarmonyWheel::resizeEvent(QResizeEvent *e)
{
    if (e->oldSize() != e->size()){

        //m_canvas = rect().adjusted(RADIUS, RADIUS, -RADIUS, -RADIUS);
        renderMap();
        positionFromColor(color(ColorHarmonyWheel::Main));
    }
    QWidget::resizeEvent(e);
}

void ColorHarmonyWheel::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {

        if(m_hitWheel){
            updateRingMarker(e->pos());
            update();
            emit colorChanged(m_colors.find(ColorHarmonyWheel::Main).value().second);
        }

    }
}

void ColorHarmonyWheel::mousePressEvent(QMouseEvent *e)
{
    // hit test ring
    if(wheel().contains(e->pos())){
        m_hitWheel = true;
        updateRingMarker(e->pos());
        update();
        emit colorChanged(m_colors.find(ColorHarmonyWheel::Main).value().second);
    }
}

void ColorHarmonyWheel::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    m_hitWheel = false;
}

