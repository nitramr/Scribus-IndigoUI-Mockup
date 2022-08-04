#include "colorwheel.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QRegion>

const int ringWidth = 20;

ColorWheel::ColorWheel(QWidget *parent)
    : QWidget{parent}
{
    m_hue = 0;
    m_hitRing = false;

    markRing = canvas().center() + QPointF(0., canvas().width()/2 - ringWidth / 2);

    setAngle(0);

}

void ColorWheel::paintEvent(QPaintEvent *e)
{

    qreal step = 1. / 6.;    

    // Ring Gradient
    QConicalGradient gradientHue;
    gradientHue.setCenter(canvas().center());
    gradientHue.setColorAt(0.0, Qt::red);
    gradientHue.setColorAt(step, Qt::yellow);
    gradientHue.setColorAt(step * 2, Qt::green);
    gradientHue.setColorAt(step * 3, Qt::cyan);
    gradientHue.setColorAt(step * 4, Qt::blue);
    gradientHue.setColorAt(step * 5, Qt::magenta);
    gradientHue.setColorAt(1.0, Qt::red);


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    // Paint Ring
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradientHue);
    painter.drawPath(ring());

    // Paint Ring Marker
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(markRing, 4, 4);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawEllipse(markRing, 5.5, 5.5);

    // Paint Triangle    
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.setTransform(m_transform, true);
    painter.setClipPath(triangle());
    painter.drawImage(QRectF(QPointF(0, 0), colorMap.size()), colorMap);
    painter.setClipping(false);

    // Draw Widget Frame
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::NoBrush);
    painter.resetTransform();
    painter.drawRect(rect());

    painter.end();
}

void ColorWheel::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {

        if(m_hitRing){
            updateRingMarker(e->pos());
            update();
        }

    }
}

void ColorWheel::mousePressEvent(QMouseEvent *e)
{
    // hit test ring
    if(ring().contains(e->pos())){
        m_hitRing = true;
        updateRingMarker(e->pos());
        update();
    }
}

void ColorWheel::mouseReleaseEvent(QMouseEvent *)
{
    m_hitRing = false;
}

QRect ColorWheel::canvas()
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

    return QRect(x,y,side,side);

}

QPainterPath ColorWheel::ring()
{
    QPainterPath path;
    path.addEllipse(canvas());
    path.addEllipse(canvas().adjusted(ringWidth,ringWidth,-ringWidth,-ringWidth));

    return path;
}

QPainterPath ColorWheel::triangle()
{
    QRect rect = canvas();
    double side = (rect.height() - ringWidth * 2) * qSin(60./180.*M_PI);
    double h = qSqrt(pow(side, 2) - pow(side/2, 2));
    double left = 0;//(width() - side - ringWidth) / 2;
    double top = 0;//(height() - side) / 2;

//    QPainterPath path;
//    path.moveTo(left, top);
//    path.lineTo(left + h, top + side / 2);
//    path.lineTo(left, top + side);
//    path.closeSubpath();

    QPainterPath path;
    path.moveTo(left, top + side/2);
    path.lineTo(left + h, top);
    path.lineTo(left + h, top + side);
    path.closeSubpath();

   // qDebug() << path.boundingRect();

    return path;
}

void ColorWheel::updateRingMarker(QPointF pos)
{
    QLineF *line = new QLineF(canvas().center(), pos);

    double angle = line->angle();
    setAngle(-angle);
    m_hue = angle / 360.;
    markRing = line->fromPolar(canvas().width()/2 - ringWidth / 2, angle).p2() + canvas().center() + QPointF(1,1);
}


void ColorWheel::renderTriangle()
{

    double height = triangle().boundingRect().height();
    double width = triangle().boundingRect().width();

    colorMap = QImage((int)width, (int)height, QImage::Format_ARGB32_Premultiplied);

//    for (int x = 0; x < (int)width; x++ )
//    {
//        for (int y = 0; y < (int)height; y++ )
//        {
//            qreal val = 1;//qBound(0.0, x / width, 1.0);
//            qreal sat = qBound(0.0, (y / 2.) / x, 1.0);

//            colorMap.setPixel( x, y, QColor::fromHsvF(m_hue, sat, val).rgb());

//        }
//    }


    // works
    for (int x = 0; x < (int)width; x++ )
    {
        qreal val = qBound(0.0, x / width, 1.0);

        for (int y = 0; y < (int)height; y++ )
        {
            qreal sat = qBound(0.0, (y - (height - x) / 2) / x, 1.0);

            colorMap.setPixel( x, y, QColor::fromHsvF(m_hue, sat, val).rgb());

        }
    }


}

void ColorWheel::setAngle(double angle)
{
    QPointF center = rect().center();
    QRectF shape = triangle().boundingRect();
    QPointF offset(shape.width()/2, shape.height()/2);

    m_transform = QTransform()
            .translate(center.x(), center.y())
            .rotate(angle -60)
            .translate(-shape.center().x() - ringWidth , -shape.center().y() );

   // qDebug() << shape.center().x()<< shape.center().y() << shape.center().x() - shape.center().y();

    // render color map
    renderTriangle();

//    m_transform = QTransform()
//            .translate(  center.x() + offset.x(),  center.y() + offset.y() )
//            .rotate( angle );
//           // .translate( -center.x() - offset.x(), -center.y() - offset.y() );

    update();

}
