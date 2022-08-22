#include "gradientedit.h"
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include "util_render.h"
#include "iconmanager.h"
#include "util_color.h"


const int RADIUS = 6;

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

GradientEdit::GradientEdit(QWidget *parent)
    : QWidget{parent}
{



    setMinimumSize(QSize(200, 36));
    setMaximumSize(QSize(3000, 36));
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);

    setup();

}


void GradientEdit::setup()
{
    m_activeStop = 0;
    m_tmpStop = 0;
    m_isEditable = true;


    ScColor color;
    fill_gradient.clearStops();

    color = ScColor(255,255,255);
    fill_gradient.addStop( color, 0.0, 0.5, 1.0 );

    color = ScColor(0,0,0);
    fill_gradient.addStop( color, 1.0, 0.5, 1.0 );

}



/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

int GradientEdit::stopAtPosition(QPoint position)
{
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    for (int i = 0; i < cstops.count(); ++i)
    {
        int hLeft = qRound(cstops.at(i)->rampPoint * canvasRect().width() );

        QRect fpo(hLeft, 0, RADIUS * 2, canvasRect().height());
        if (fpo.contains(position) )
        {
            return i;
        }
    }

    return -1;
}

double GradientEdit::percentFromPosition(QPointF position)
{
    //        double wRatio = (double)width() / (double)canvasRect().width();
    //        double t = (position.x() - RADIUS) * wRatio / (double)width();

    double t = static_cast<double>((position.x() - RADIUS)) / static_cast<double>(canvasRect().width());
    return qBound(0., t, 1.);

}

void GradientEdit::addStop(QPoint mousePosition)
{
    //    QList<VColorStop*> cstops = fill_gradient.colorStops();
    //    double  newStop = percentFromPosition(mousePosition);
    //    QColor  stopColor = (cstops.count() > 0) ? cstops.at(0)->color : QColor(255, 255, 255);
    //    QString stopName  = (cstops.count() > 0) ? cstops.at(0)->name  : QString("White");
    //    int     stopShade = (cstops.count() > 0) ? cstops.at(0)->shade : 100;
    //    fill_gradient.addStop(stopColor, newStop, 0.5, 1.0, stopName, stopShade);


    //    cstops = fill_gradient.colorStops();
    //    std::sort(cstops.begin(), cstops.end());

    ScColor blendColor = ColorUtils::colorBlend(fill_gradient.colorStops().first()->color, fill_gradient.colorStops().last()->color, 0.5);

    qDebug() << blendColor;

    fill_gradient.addStop(blendColor, percentFromPosition(mousePosition), 0.5, blendColor.alphaF(), blendColor.name(), blendColor.shadeF());
    sortStops();

    m_activeStop = stopAtPosition(mousePosition);
    m_tmpStop = m_activeStop;

    repaint();

    if(m_activeStop > -1){
        emitStop();
        emitStopID();
    }


}

void GradientEdit::removeStop()
{
    QList<VColorStop*> cstops = fill_gradient.colorStops();

    // Remove stop if it is not first or last one
    if ( m_activeStop != -1 && cstops.count() > 2){
        fill_gradient.removeStop(m_activeStop);
        m_activeStop = qMax(m_activeStop - 1, 0);
        repaint();
        emitStop();
        emitStopID();
    }
}

void GradientEdit::emitStop()
{

    if (!fill_gradient.colorStops().isEmpty())
    {
        QList<VColorStop*> cstops = fill_gradient.colorStops();

        emit selectedColor(cstops.at(m_activeStop)->color);
        emit selectedPosition(cstops.at(m_activeStop)->rampPoint);
    }

}

void GradientEdit::emitStopID()
{
    if (!fill_gradient.colorStops().isEmpty())
    {
        emit selectedStop(fill_gradient.colorStops().at(m_activeStop));
    }

}

void GradientEdit::updateTmpStop(double t)
{
    // update stop position
    if(m_activeStop != -1){

        QList<VColorStop*> cstops = fill_gradient.colorStops();
        cstops.at(m_activeStop)->rampPoint = t;

        std::stable_sort(cstops.begin(), cstops.end(), compareStops);
        for(int i = 0; i < cstops.count(); i++){
            VColorStop *stop = cstops.at(i);
            if(stop->rampPoint == t)
                m_tmpStop = i;

        }

        repaint();

    }
}

void GradientEdit::sortStops()
{
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    std::stable_sort(cstops.begin(), cstops.end(), compareStops);

    VGradient grad(fill_gradient);
    grad.clearStops();

    foreach(VColorStop *stop, cstops){
        grad.addStop(*stop);
    }

    fill_gradient = grad;

}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void GradientEdit::paintEvent(QPaintEvent *e)
{

    QList<VColorStop*> cstops = fill_gradient.colorStops();
    std::stable_sort(cstops.begin(), cstops.end(), compareStops);

    // Gradient
    QLinearGradient gradient = fill_gradient.toQLinearGradient();
    gradient.setStart(gradientRect().left(), 0);
    gradient.setFinalStop(gradientRect().right(), 0);

    // TODO: replace with ScPainter
    QPainter painter;
    painter.begin(this);

    // Draw Background
    UtilRender::renderPattern(&painter, gradientRect());

    // Draw Gradient
    painter.setPen(palette().color(QPalette::Mid));
    painter.setBrush(gradient);
    painter.drawRect(gradientRect());


    if (isEditable())
    {
        painter.setRenderHint(QPainter::Antialiasing, true);

        //qreal yCenter =  canvasRect().center().y() + 0.5;
        qreal yCenter = 12 + 0.5;

        // Draw line
//        if(fill_gradient.stops() >= 2){
//            qreal start = cstops.first()->rampPoint * canvasRect().width()  + RADIUS;
//            qreal end = cstops.last()->rampPoint * canvasRect().width()  + RADIUS;

//            QPen pen;

//            pen.setColor(Qt::white);
//            pen.setWidth(3);
//            painter.setPen(pen);
//            painter.drawLine(QPointF(start, yCenter), QPointF(end, yCenter) );

//            pen.setColor(Qt::black);
//            pen.setWidth(1);
//            painter.setPen(pen);
//            painter.drawLine(QPointF(start, yCenter), QPointF(end, yCenter) );
//        }


        // Draw Stops
        for (int i = 0; i < fill_gradient.stops(); ++i)
        {
            int hCenter = cstops.at(i)->rampPoint * canvasRect().width() + RADIUS;

            // Draw Marker
            if (m_tmpStop == i){

                QPainterPath marker;
                marker.moveTo( QPointF(hCenter - 5, -0.5) );
                marker.lineTo( QPointF(hCenter + 5, -0.5) );
                marker.lineTo( QPointF(hCenter, 5) );
                marker.closeSubpath();

                painter.setPen(QPen(palette().color(QPalette::Window), 1));
                painter.setBrush(palette().color(QPalette::WindowText));
                painter.drawPath(marker);

            }            

            UtilRender::renderPointerHandle(&painter, QPointF(hCenter, yCenter), RADIUS*2-2, cstops.at(i)->color.toQColor() );

            //            // Draw Mid Point
            //            qreal mid = cstops.at(i)->midPoint * canvasRect.width() + RADIUS + 0.5;

            //            QPen pen;

            //            pen.setColor(Qt::white);
            //            pen.setWidth(3);
            //            painter.setPen(pen);
            //            painter.drawLine(QPointF(mid, yCenter - RADIUS), QPointF(mid, yCenter + RADIUS) );

            //            pen.setColor(Qt::black);
            //            pen.setWidth(1);
            //            painter.setPen(pen);
            //            painter.drawLine(QPointF(mid, yCenter - RADIUS), QPointF(mid, yCenter + RADIUS) );


        }
    }

    painter.end();

    QWidget::paintEvent(e);

}

void GradientEdit::keyPressEvent(QKeyEvent *e)
{
    if (isEditable())
    {
        if(e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace)
        {
            removeStop();
        }

    }
}

void GradientEdit::mousePressEvent(QMouseEvent *m)
{
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));

    if (isEditable()){
        m_activeStop = stopAtPosition(m->pos());
        m_tmpStop = m_activeStop;

        if(m_activeStop == -1){
            addStop(m->pos());
        }else{
            repaint();

            emitStop();
            emitStopID();
        }


    }else{
        m_activeStop = m_tmpStop = -1;
    }



}

void GradientEdit::mouseReleaseEvent(QMouseEvent *m)
{

    if (isEditable())
    {
        qApp->restoreOverrideCursor();

        if (m->button() == Qt::LeftButton)
        {
            if (isMouseOutside(m->pos())){
                removeStop();
            }else{
                sortStops();
                m_activeStop = m_tmpStop;
                repaint();
                emitStopID();
            }

        }
    }
}

void GradientEdit::mouseMoveEvent(QMouseEvent *m)
{

    if (isEditable())
    {

        qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));

        // Set Hover Cursor
        if (canvasRect().contains(m->position().toPoint()) )
        {

            if(stopAtPosition(m->position().toPoint()) > -1){
                setCursor(QCursor(Qt::SizeHorCursor));
                //return;
            }else{
                setCursor(IconManager::instance().cursor("cursor-point-add", 1, 1));
            }

        }

        // Press Left Mouse
        if (m->buttons() & Qt::LeftButton)
        {

            double newPos = percentFromPosition(m->position());
            updateTmpStop(newPos);
            emitStop();

            QList<VColorStop*> cstops = fill_gradient.colorStops();
            // Set "remove" cursor if gradient has more than 2 stops
            if (isMouseOutside(m->pos()) && cstops.count() > 2)
                qApp->changeOverrideCursor(IconManager::instance().cursor("cursor-point-delete", 1, 1));


        }
    }


}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void GradientEdit::setActiveStopColor(const ScColor &c)
{
    if (m_activeStop == -1)
        return;

    fill_gradient.colorStops().at(m_activeStop)->color = c;
    fill_gradient.colorStops().at(m_activeStop)->name = c.name();
    fill_gradient.colorStops().at(m_activeStop)->opacity = c.alpha();
    fill_gradient.colorStops().at(m_activeStop)->shade = c.shadeF() * 100;
    repaint();
}

void GradientEdit::setActiveStopPosition(double t)
{
    if (m_activeStop == -1)
        return;

    updateTmpStop(t);

    repaint();
}

void GradientEdit::setIsEditable(bool isEditable)
{
    m_isEditable = isEditable;
    repaint();
}

bool GradientEdit::isEditable()
{
    return m_isEditable;
}

void GradientEdit::setGradient(const VGradient &gradient)
{
    if ((gradient.colorStops().count() == fill_gradient.colorStops().count()) && (m_activeStop >= 0))
    {
        int diffStops = 0;
        for (int i = 0; i < fill_gradient.colorStops().count(); ++i)
        {
            VColorStop* stop1 = gradient.colorStops().at(i);
            VColorStop* stop2 = fill_gradient.colorStops().at(i);
            if ((stop1->color != stop2->color) || (stop1->midPoint != stop2->midPoint) ||
                    (stop1->name  != stop2->name)  || (stop1->opacity != stop2->opacity)   ||
                    (stop1->rampPoint != stop2->rampPoint) || (stop1->shade != stop2->shade))
            {
                ++diffStops;
            }
        }
        if (diffStops > 1)
            m_activeStop = 0;
    }

    if ((m_activeStop < 0) && (gradient.colorStops().count() > 0))
        m_activeStop = 0;

    if (m_activeStop >= gradient.colorStops().count())
        m_activeStop = 0;

    fill_gradient = gradient;

    repaint();
}

const VGradient &GradientEdit::gradient()
{

    //    QList<VColorStop*> cstops = fill_gradient.colorStops();
    //    std::stable_sort(cstops.begin(), cstops.end(), compareStops);

    //    VGradient &grad(fill_gradient);
    //    grad.clearStops();

    //    foreach(VColorStop *stop, cstops){
    //        grad.addStop(*stop);
    //    }

    return fill_gradient;
}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */

QRect GradientEdit::canvasRect()
{
    return QRect(RADIUS, 0, width() - RADIUS * 2, height());
}

QRect GradientEdit::gradientRect()
{
    return canvasRect().adjusted(0,0,0, -height() / 2);
}


bool GradientEdit::isMouseOutside(QPoint mouse)
{
    return (mouse.y() <= rect().top() || mouse.y() >= rect().bottom());
}
