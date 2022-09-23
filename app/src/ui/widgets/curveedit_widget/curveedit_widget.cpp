/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

// Based on code of https://github.com/scribusproject/scribus/blob/master/scribus/ui/curvewidget.cpp


#include "curveedit_widget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include "spline_utils.h"
#include "color_utils.h"

const qreal POINT_RADIUS = 4.0;
const qreal TOLLERANCE = 2.0; // pixel tollerance to hit a point

CurveEditWidget::CurveEditWidget(QWidget *parent) : QWidget(parent),
    m_leftmost(0.0),
    m_rightmost(0.0),
    m_dragging(false),
    m_linear(false),
    m_selectedPoint(0)
{
    setMouseTracking(true);
    setMinimumSize(150, 150);
    m_points.resize(0);
    m_points.addPoint(0.0, 0.0);
    m_points.addPoint(1.0, 1.0);

//    // TMP
//    m_points.addPoint(0.2, .9);
//    m_points.addPoint(0.4, 0.5);
//    m_points.addPoint(0.6, .9);
//    m_points.addPoint(0.8, 0.2);

    setFocusPolicy(Qt::StrongFocus);
}

CurveEditWidget::~CurveEditWidget()
{
}

void CurveEditWidget::paintEvent(QPaintEvent *)
{
    //    int x = 0;
    int wWidth = width();
    int wHeight = height();
    QPointF offset(-.5, -.5);
    QColor colorHandle = palette().color(QPalette::Highlight);
    QColor colorBackground = palette().color(QPalette::Base);
    QColor colorGraph = palette().color(QPalette::WindowText);
    QColor colorGrid = palette().color(QPalette::Mid); //Qt::gray;
    QPainterPath path = curvePath();

    // Drawing selection or all histogram values.
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //  draw background
    painter.fillRect(this->rect(), colorBackground);

    // Draw grid separators.
    painter.setPen(QPen(colorGrid, 1, Qt::SolidLine));
    painter.drawLine( QPointF(wWidth/4, 0)-offset, QPointF(wWidth/4, wHeight)-offset );
    painter.drawLine( QPointF(wWidth/2, 0)-offset, QPointF(wWidth/2, wHeight)-offset );
    painter.drawLine( QPointF(3*wWidth/4, 0)-offset, QPointF(3*wWidth/4, wHeight)-offset );
    painter.drawLine( QPointF(0, wHeight/4)-offset, QPointF(wWidth, wHeight/4)-offset );
    painter.drawLine( QPointF(0, wHeight/2)-offset, QPointF(wWidth, wHeight/2)-offset );
    painter.drawLine( QPointF(0, 3*wHeight/4)-offset, QPointF(wWidth, 3*wHeight/4)-offset );

    // Draw curve.
//    painter.setPen(QPen(Qt::white, 4, Qt::SolidLine));
//    painter.drawPath(path);
    painter.setPen(QPen(colorGraph, 2, Qt::SolidLine));
    painter.drawPath(path);

    painter.setBrush(Qt::NoBrush);

    // Draw handles
    for (int i = 0; i < m_points.size(); i++)
    {
        FPoint p = m_points.point(i);
        QPointF dot = QPointF(p.x() * width(), (1-p.y()) * height());

        if (p == m_points.at(m_selectedPoint))
        {
            painter.setPen(QPen(colorHandle, 2, Qt::SolidLine));
            painter.setBrush(colorHandle);
            painter.drawEllipse( dot, POINT_RADIUS, POINT_RADIUS );
        }
        else
        {
            painter.setPen(QPen(colorGraph, 2, Qt::SolidLine));
            painter.setBrush(colorBackground);
            painter.drawEllipse( dot, POINT_RADIUS, POINT_RADIUS );
        }
    }

    painter.end();
}

void CurveEditWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace)
    {
        if (m_points.size() > 2)
        {
            m_points.removeAt(m_selectedPoint);

            m_selectedPoint = qBound(0, m_selectedPoint-1, m_points.size() -1);

            repaint();
            emit modified();
            QWidget::keyPressEvent(e);
        }
    }
}

void CurveEditWidget::mousePressEvent ( QMouseEvent * e )
{

    if (e->button() != Qt::LeftButton)
        return;

    // invert mouseY
    m_mousePos = QPointF( e->pos().x(), (height() - e->pos().y()));

    m_leftmost = -1;
    m_selectedPoint = 0;
    m_rightmost = m_points.size();

    m_dragging = false;

    for(int i = 0; i < m_points.size(); i++) {

        QPointF pt(m_points[i].x() * width(), m_points[i].y() * height());

        // calculate left point of mouse position
        if(pt.x() >= 0 && pt.x() <= m_mousePos.x()){
            m_leftmost = i;
        }

        if( SplineUtils::distance(pt, m_mousePos) <= POINT_RADIUS + TOLLERANCE ){

            m_selectedPoint = i;
            m_leftmost = i-1;
            m_rightmost = i+1;

            m_dragging = true;
            repaint();
            return;
        }

    }

    // add new point
    if(!m_dragging){

        FPoint onCurve(m_mousePos.x() / width(), m_mousePos.y() / height() );
        m_selectedPoint = m_leftmost +1;
        m_rightmost = m_leftmost + 2;
        m_points.insert(m_selectedPoint, onCurve );

        m_dragging = true;

        repaint();
        emit modified();
    }


}

void CurveEditWidget::mouseReleaseEvent ( QMouseEvent * e )
{
    if (e->button() != Qt::LeftButton)
        return;
    setCursor(QCursor(Qt::ArrowCursor));
    m_dragging = false;
    repaint();
    emit modified();
}

void CurveEditWidget::mouseMoveEvent ( QMouseEvent * e )
{
    //  boolHoverCurve = false;

    if(m_dragging){

        setCursor(QCursor(Qt::CrossCursor));

        // https://github.com/scribusproject/scribus/blob/master/scribus/ui/curvewidget.cpp

        // invert mouseY
        QPointF mouse(e->pos().x(), height() - e->pos().y());

        // left bound
        qreal leftBound = (m_leftmost < 0) ? 0. : m_points.at(m_leftmost).x();
        qreal rightBound = (m_rightmost >= m_points.size()) ? 1. : m_points.at(m_rightmost).x();

        // limit to bounds
        qreal yPos = qBound(0., mouse.y() / height(), 1.);
        qreal xPos = qBound(leftBound + 1E-4, mouse.x() / width(), rightBound - 1E-4);

        QPointF pointSelectedDot(xPos, yPos );

        // set new position
        m_points.setPoint( m_selectedPoint, pointSelectedDot);



        repaint();
        emit modified();
    }
}

//double CurveEditWidget::getCurveValue(double x)
//{
//    return ColorUtils::getCurveYValue(m_points, x, m_linear);
//}

FPointArray CurveEditWidget::getCurve()
{
    return m_points.copy();
}


QPainterPath CurveEditWidget::curvePath()
{
    QPointF pointStart( 0, (1-m_points.at(0).y()) * height() );
    QPointF pointEnd( width(), (1-m_points.at(m_points.size()-1).y()) * height() );


    QList<QPointF> points;
    points.append( pointStart );

    // Calculate absolute position of each point
    for (int i = 0; i < m_points.size(); i++)
    {
        FPoint p = m_points.at(i);
        points.append(QPointF(p.x() * width(), (1-p.y()) * height()));
    }

    points.append( pointEnd );


    // Construct Path
    QPainterPath path;

    // Add start line
    path.moveTo( pointStart );
    path.lineTo( points.at(1) );

    for (int id = 0; id < points.size(); id++)
    {

        if(m_linear){

            path.lineTo(points.at(id).toPoint());

        }else{

            int i0 = id-1;
            int i1 = id;
            int i2 = id+1;
            int i3 = id+2;

            if(i0 < 0 || i2 > points.size()-1 || i3 > points.size()-1){

                continue;
            }

            FPoint p0 = (i0 >= 0) ? points.at(i0) : points.at(i1);
            FPoint p1 = points.at(i1);
            FPoint p2 = (i2 < points.size()) ? points.at(i2) : points.at(points.size()-1);
            FPoint p3 = (i3 < points.size()) ? points.at(i3) : points.at(points.size()-1);

            QList<QPointF> inputPoints;
            inputPoints.append( p0.toQPointF() ); // Previous point
            inputPoints.append( p1.toQPointF() ); // Point
            inputPoints.append( p2.toQPointF() ); // Next point
            inputPoints.append( p3.toQPointF() ); // Next but one point

            double t = qMax(width() / (p2.x() - p1.x()) / 6, 1.);

            QList<QPointF> *bezPoints = SplineUtils::catmullToBezier(inputPoints, t);

            path.cubicTo(
                        QPointF( bezPoints->at(1) ), // Control 1
                        QPointF( bezPoints->at(2) ), // Control 2
                        QPointF( bezPoints->at(3) ) // Next Point

                        );
        }

    }

    // Add end line
    path.lineTo( pointEnd );

    return path;

}

void CurveEditWidget::setCurve(const FPointArray& inlist)
{
    m_points_back = m_points.copy();
    m_points.resize(0);
    m_points = inlist.copy();
    repaint();
    emit modified();
}

void CurveEditWidget::resetCurve()
{
    m_points.resize(0);
    m_points = m_points_back.copy();
    repaint();
    emit modified();
}

void CurveEditWidget::setLinear(bool setter)
{
    m_linear = setter;
    repaint();
    emit modified();
}

bool CurveEditWidget::isLinear()
{
    return m_linear;
}

//QPointF CurveEditWidget::pointOnBezier(QPointF mouse)
//{
//    // Get Bezier segment on mouse

//    QPointF pointStart( 0, (1-m_points.at(0).y()) * height() );
//    QPointF pointEnd( width(), (1-m_points.at(m_points.size()-1).y()) * height() );

//    // Generate temporary point list
//    QList<QPointF> points;
//    points.append( pointStart );

//    for (int i = 0; i < m_points.size(); i++)
//    {
//        FPoint fp = m_points.at(i);
//        points.append(QPointF(fp.x() * width(), (1-fp.y()) * height()));
//    }

//    points.append( pointEnd );



//    QPointF result(0,0);

//    for (int dh = 0; dh < points.size(); dh++)
//    {

//        int i0 = dh-1;
//        int i1 = dh;
//        int i2 = dh+1;
//        int i3 = dh+2;

//        if(i0 < 0 || i2 > points.size()-1 || i3 > points.size()-1){

//            continue;
//        }

//        FPoint p0 = (i0 >= 0) ? points.at(i0) : points.at(i1);
//        FPoint p1 = points.at(i1);
//        FPoint p2 = (i2 < points.size()) ? points.at(i2) : points.at(points.size()-1);
//        FPoint p3 = (i3 < points.size()) ? points.at(i3) : points.at(points.size()-1);


//        if(p1.x() <= mouse.x() && p2.x() > mouse.x()){

//            QList<QPointF> inputPoints;
//            inputPoints.append( p0.toQPointF() ); // Previous point
//            inputPoints.append( p1.toQPointF() ); // Point
//            inputPoints.append( p2.toQPointF() ); // Next point
//            inputPoints.append( p3.toQPointF() ); // Next but one point

//            double t = width() / (p2.x() - p1.x()) / 6;

//            QList<QPointF> *bezPoints = SplineUtils::CatmullToBezier(inputPoints, t);

//            result = SplineUtils::findPointOnBezier(bezPoints->at(0), bezPoints->at(1), bezPoints->at(2), bezPoints->at(3), mouse);

//        }

//    }

//    return QPointF(result.x(), height() - result.y());

//}

