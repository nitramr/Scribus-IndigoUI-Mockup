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

#ifndef GRADIENTPREVIEW_H
#define GRADIENTPREVIEW_H

#include "sccolor.h"
#include <QList>
#include <QFrame>
#include <QEnterEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

class QEvent;

#include "scribusapi.h"
#include "vgradient.h"

class SCRIBUS_API GradientPreview : public QFrame
{
    Q_OBJECT

public:
    GradientPreview(QWidget *pa);
    ~GradientPreview() {};
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *m);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *m);
    void leaveEvent(QEvent*);
    void enterEvent(QEnterEvent*);
    void resizeEvent(QResizeEvent *e);

    void updateDisplay();

    void setActiveStopColor(const ScColor& c);
    ScColor activeStopColor();

    void setActiveStopTransparency(double t);
    void setActiveStopPosition(double t);
    void setGradient(const VGradient& gradient);
    void setGradientEditable(bool val);
    bool isGradientEditable();

    const VGradient& gradient() { return fill_gradient; }

private:
    VGradient fill_gradient;
    QRect canvasRect;

    QList<int> StopM;
    bool Mpressed;
    bool outside;
    bool onlyselect;
    bool isEditable;
    int activeStop;
    int contextStop;
    QPoint mPos;

private slots:
    void addStop();
    void removeStop();

signals:
    void selectedColor(ScColor);
    void selectedStop(VColorStop*);
    void currTrans(double);
    void currStep(double);
    void gradientChanged();
};
#endif // GRADIENTPREVIEW_H
