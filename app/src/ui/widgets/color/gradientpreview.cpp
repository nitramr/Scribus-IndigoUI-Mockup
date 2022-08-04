/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
                          gradienteditor  -  description
                             -------------------
    begin                : Mit Mai 26 2004
    copyright            : (C) 2004 by Franz Schmid
    email                : Franz.Schmid@altmuehlnet.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <algorithm>
#include <QApplication>
#include <QCursor>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPolygon>
#include <QToolTip>

#include "gradientpreview.h"
#include "iconmanager.h"
#include "helper.h"

const int RADIUS = 6;

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

GradientPreview::GradientPreview(QWidget *pa) : QFrame(pa)
{
    setFrameShape( QFrame::NoFrame );
    setFrameShadow( QFrame::Plain );
    setLineWidth( 0 );
    setMinimumSize(QSize(200, 40));
    setMaximumSize(QSize(3000, 40));
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);
    Mpressed = false;
    outside = true;
    onlyselect = true;
    isEditable = true;
    fill_gradient = VGradient(GradientType::Linear);
    fill_gradient.clearStops();

    canvasRect = QRect(RADIUS, 0, width() - RADIUS * 2, height());

    ScColor color;
    color = ScColor(255,255,255);
    fill_gradient.addStop( color, 0.0, 0.5, 1.0 );
    color = ScColor(0,0,0);
    fill_gradient.addStop( color, 1.0, 0.5, 1.0 );

    QList<VColorStop*> cstops = fill_gradient.colorStops();
    StopM.clear();
    contextStop = 0;
    activeStop = 0;
    for (int i = 0; i < fill_gradient.stops(); ++i)
    {
        int center = qRound(cstops.at(i)->rampPoint * canvasRect.width() ) + RADIUS;
        StopM.append(center);
    }
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void GradientPreview::paintEvent(QPaintEvent *e)
{
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    StopM.clear();

    for (int i = 0; i < fill_gradient.stops(); ++i)
    {
        int center = qRound(cstops.at(i)->rampPoint * canvasRect.width() ) + RADIUS;
        StopM.append(center);
    }

    // TODO: replace with ScPainter

    // Gradient
    QLinearGradient gradient = fill_gradient.toQLinearGradient();
    gradient.setStart(canvasRect.left(), 0);
    gradient.setFinalStop(canvasRect.right(), 0);

    QPainter painter;
    painter.begin(this);


    // Draw Background
    Helper::renderPattern(&painter, canvasRect);

    // Draw Gradient
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawRect(canvasRect);

    if (isEditable)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);

        qreal yCenter =  canvasRect.center().y() + 0.5;

        // Draw line
        if(fill_gradient.stops() >= 2){
            int start = qRound(cstops.first()->rampPoint * canvasRect.width() ) + RADIUS;
            int end = qRound(cstops.last()->rampPoint * canvasRect.width() ) + RADIUS;

            QPen pen;

            pen.setColor(Qt::white);
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawLine(QPointF(start, yCenter), QPointF(end, yCenter) );

            pen.setColor(Qt::black);
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawLine(QPointF(start, yCenter), QPointF(end, yCenter) );
        }


        // Draw Stops
        for (int i = 0; i < fill_gradient.stops(); ++i)
        {
            int hCenter = qRound(cstops.at(i)->rampPoint * canvasRect.width() ) + RADIUS;

            // Draw Marker
            if (StopM[qMax(activeStop,0)] == hCenter){
                Helper::renderColorHandle(&painter, QPointF(hCenter, yCenter), RADIUS, QBrush(cstops.at(i)->color.toQColor()) );
            }
            else{
                Helper::renderColorHandle(&painter, QPointF(hCenter, yCenter), RADIUS -2, QBrush(cstops.at(i)->color.toQColor()) );
            }

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

    QFrame::paintEvent(e);
}

void GradientPreview::keyPressEvent(QKeyEvent *e)
{
    if (isEditable)
    {
        if(e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace)
        {
            if ((activeStop > 0) && (activeStop != static_cast<int>(StopM.count()-1)))
            {
                onlyselect = false;
                fill_gradient.removeStop(activeStop);
                activeStop = 0;
                repaint();
                QList<VColorStop*> cstops = fill_gradient.colorStops();
                emit selectedStop(cstops.at(activeStop));
                emit selectedColor(activeStopColor());
            }
        }        

    }
}

void GradientPreview::mousePressEvent(QMouseEvent *m)
{
    QRect fpo;
    Mpressed = true;
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
    activeStop = -1;

    if (isEditable)
    {
        QList<VColorStop*> cstops = fill_gradient.colorStops();
        for (int yg = 0; yg < static_cast<int>(StopM.count()); ++yg)
        {
            fpo = QRect(static_cast<int>(StopM[yg]) - RADIUS/2, 0, RADIUS, canvasRect.height());
            if (fpo.contains(m->pos()))
            {
                activeStop = yg;
                emit selectedStop(cstops.at(activeStop));
                emit selectedColor(activeStopColor());
                repaint();
                onlyselect = true;
                return;
            }
        }
    }

}

void GradientPreview::mouseReleaseEvent(QMouseEvent *m)
{
    qApp->restoreOverrideCursor();

    if (isEditable)
    {
        QRect fpo;
        //QPointF mousePos = m->position();
        mPos = m->pos();

        if (m->button() == Qt::LeftButton)
        {
            if ((Mpressed) && (activeStop > 0) && (activeStop != static_cast<int>(StopM.count()-1)) && (outside || !canvasRect.contains(m->pos())))
            {
                onlyselect = false;
                fill_gradient.removeStop(activeStop);
                activeStop = 0;
                repaint();
                QList<VColorStop*> cstops = fill_gradient.colorStops();
                emit selectedStop(cstops.at(activeStop));
                emit selectedColor(activeStopColor());
            }

            // Release on canvas
            if (canvasRect.contains(mPos) && (activeStop == -1))
            {
//                QList<VColorStop*> cstops = fill_gradient.colorStops();
//                double  newStop = static_cast<double>((mousePos.x() - RADIUS)) / static_cast<double>(canvasRect.width());
//                QColor  stopColor = (cstops.count() > 0) ? cstops.at(0)->color : QColor(255, 255, 255);
//                QString stopName  = (cstops.count() > 0) ? cstops.at(0)->name  : QString("White");
//                int     stopShade = (cstops.count() > 0) ? cstops.at(0)->shade : 100;
//                fill_gradient.addStop(stopColor, newStop, 0.5, 1.0, stopName, stopShade);
//                repaint();
//                onlyselect = false;
//                cstops = fill_gradient.colorStops();
//                for (int yg = 0; yg < static_cast<int>(StopM.count()); ++yg)
//                {
//                    fpo = QRect(static_cast<int>(StopM[yg]) - RADIUS/2, 0, RADIUS, canvasRect.height());
//                    if (fpo.contains(m->pos()))
//                    {
//                        activeStop = yg;
//                        emit selectedStop(cstops.at(activeStop));
//                        repaint();
//                        break;
//                    }
//                }

                addStop();
            }

            emit selectedColor(activeStopColor());
        }
        else if (m->button() == Qt::RightButton)
        {
            Mpressed = false;
//			QList<VColorStop*> cstops = fill_gradient.colorStops();
            int stop = -1;
            for (int yg = 0; yg < static_cast<int>(StopM.count()); ++yg)
            {
                fpo = QRect(static_cast<int>(StopM[yg]) - RADIUS/2, 0, RADIUS, canvasRect.height());
                if (fpo.contains(m->pos()))
                {
                    stop = yg;
                    break;
                }
            }
            contextStop = stop;
            mPos = m->pos();
            setCursor(QCursor(Qt::ArrowCursor));

            QMenu *pmen = new QMenu();
            pmen->addAction( tr("Add Stop"), this, SLOT(addStop()));

            if (stop != -1)
                pmen->addAction( tr("Remove Stop"), this, SLOT(removeStop()));

            pmen->exec(QCursor::pos());
            delete pmen;
        }
    }

    Mpressed = false;

    if ((!onlyselect) && (activeStop >= 0))
    {
        emit gradientChanged();
        QList<VColorStop*> cstops = fill_gradient.colorStops();
        emit currStep(cstops.at(activeStop)->rampPoint);
    }
}

void GradientPreview::mouseMoveEvent(QMouseEvent *m)
{
    if (isEditable)
    {
        QRect fpo;
        QPointF mousePos = m->position();

        qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));

        // Set Hover Cursor
        if ((!Mpressed) && canvasRect.contains(mousePos.toPoint()) )
        { 
            setCursor(IconManager::instance().cursor("cursor-point-add", 1, 1));

            for (int yg = 0; yg < static_cast<int>(StopM.count()); ++yg)
            {
                fpo = QRect(static_cast<int>(StopM[yg]) - RADIUS/2, 0, RADIUS, canvasRect.height());
                if (fpo.contains(m->pos()))
                {
                    setCursor(QCursor(Qt::SizeHorCursor));
                    return;
                }
            }
        }

        if (m->buttons() & Qt::LeftButton)
        {
            if ((Mpressed) && canvasRect.contains(mousePos.toPoint()) )
            {
                qApp->changeOverrideCursor(QCursor(Qt::SizeHorCursor));
                double newStop = static_cast<double>( (mousePos.x() - RADIUS)) / static_cast<double>(canvasRect.width());

                if (activeStop > 1)
                {
                    if (StopM[activeStop-1]+2 >= mousePos.x())
                        return;
                }

                if (activeStop < static_cast<int>(StopM.count()-2))
                {
                    if (StopM[activeStop+1]-2 < mousePos.x())
                        return;
                }

                StopM[activeStop] = mousePos.x();
                QList<VColorStop*> cstops = fill_gradient.colorStops();
                cstops.at(activeStop)->rampPoint = newStop;
                std::sort(cstops.begin(), cstops.end());
                onlyselect = false;
                repaint();


            }

            if ((Mpressed) && (outside || !canvasRect.contains(m->pos())) && (activeStop > 0) && (activeStop != static_cast<int>(StopM.count()-1)))
                qApp->changeOverrideCursor(IconManager::instance().cursor("cursor-point-delete", 1, 1));
        }
    }
}

void GradientPreview::leaveEvent(QEvent*)
{
    if (isEditable)
    {
        if (Mpressed)
        {
            if ((activeStop > 0) && (activeStop != static_cast<int>(StopM.count()-1)))
                qApp->changeOverrideCursor(IconManager::instance().cursor("cursor-point-delete", 1, 1));
            else
                qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));
        }
        outside = true;
    }
}

void GradientPreview::enterEvent(QEnterEvent *)
{
    outside = false;
}

void GradientPreview::resizeEvent(QResizeEvent *e)
{
    if (e->oldSize() != e->size()){

        canvasRect = QRect(RADIUS, 0, width() - RADIUS * 2, height());
    }
    QFrame::resizeEvent(e);
}

/* ********************************************************************************* *
 *
 * Methods
 *
 * ********************************************************************************* */

void GradientPreview::addStop()
{

    QList<VColorStop*> cstops = fill_gradient.colorStops();
    double  newStop = static_cast<double>((mPos.x() - RADIUS)) / static_cast<double>(canvasRect.width());
    ScColor  stopColor = (cstops.count() > 0) ? cstops.at(0)->color : ScColor(255, 255, 255);
    QString stopName  = (cstops.count() > 0) ? cstops.at(0)->name  : QString("White");
    int     stopShade = (cstops.count() > 0) ? cstops.at(0)->shade : 100;
    fill_gradient.addStop(stopColor, newStop, 0.5, 1.0, stopName, stopShade);
    repaint();
    onlyselect = false;
    cstops = fill_gradient.colorStops();
    for (int yg = 0; yg < static_cast<int>(StopM.count()); ++yg)
    {
        QRect fpo = QRect(static_cast<int>(StopM[yg]) - RADIUS/2, 0, RADIUS, canvasRect.height());
        if (fpo.contains(mPos))
        {
            activeStop = yg;
            emit selectedStop(cstops.at(activeStop));
            emit selectedColor(activeStopColor());
            repaint();
            break;
        }
    }
}

void GradientPreview::removeStop()
{
    if ((contextStop > 0) && (contextStop != static_cast<int>(StopM.count()-1)))
    {
        onlyselect = false;
        fill_gradient.removeStop(contextStop);
        activeStop = 0;
        repaint();
        QList<VColorStop*> cstops = fill_gradient.colorStops();
        emit selectedStop(cstops.at(activeStop));
        emit selectedColor(activeStopColor());
    }
}

void GradientPreview::updateDisplay()
{
    repaint();
    if (!fill_gradient.colorStops().isEmpty())
    {
        QList<VColorStop*> cstops = fill_gradient.colorStops();
        emit selectedStop(cstops.at(activeStop));
        emit selectedColor(activeStopColor());
    }
}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

void GradientPreview::setActiveStopColor(const ScColor &c)
{
    if (activeStop == -1)
        return;
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    cstops.at(activeStop)->color = c;
    cstops.at(activeStop)->name = c.name();
    cstops.at(activeStop)->shade = c.alpha();
    repaint();
}

ScColor GradientPreview::activeStopColor()
{
    ScColor col;

    if (activeStop == -1)
        return col;

    QList<VColorStop*> cstops = fill_gradient.colorStops();
    col = cstops.at(activeStop)->color;
    return col;
}

void GradientPreview::setActiveStopTransparency(double t)
{
    if (activeStop == -1)
        return;
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    cstops.at(activeStop)->opacity = t;
    repaint();
}

void GradientPreview::setActiveStopPosition(double t)
{
    if (activeStop == -1)
        return;
    QList<VColorStop*> cstops = fill_gradient.colorStops();
    cstops.at(activeStop)->rampPoint = t;
    repaint();
}

void GradientPreview::setGradient(const VGradient& gradient)
{
    if ((gradient.colorStops().count() == fill_gradient.colorStops().count()) && (activeStop >= 0))
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
            activeStop = 0;
    }
    if ((activeStop < 0) && (gradient.colorStops().count() > 0))
        activeStop = 0;
    if (activeStop >= gradient.colorStops().count())
        activeStop = 0;
    fill_gradient = gradient;
}

void GradientPreview::setGradientEditable(bool val)
{
    isEditable = val;
    repaint();
}

bool GradientPreview::isGradientEditable()
{
    return isEditable;
}
