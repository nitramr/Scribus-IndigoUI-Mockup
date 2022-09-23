#ifndef CURVEEDITWIDGET_H
#define CURVEEDITWIDGET_H

#include <QWidget>
#include "fpointarray.h"
#include "scribusapi.h"

class SCRIBUS_API CurveEditWidget : public QWidget
{
    Q_OBJECT

public:
    CurveEditWidget(QWidget *parent);
    virtual ~CurveEditWidget();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent (QMouseEvent * e);
    void mouseReleaseEvent ( QMouseEvent * e );
    void mouseMoveEvent ( QMouseEvent * e );

public:
//    double getCurveValue(double x);
    FPointArray getCurve();
    QPainterPath curvePath();
    void setCurve(const FPointArray& inlist);
    void resetCurve();
    void setLinear(bool setter);
    bool isLinear();

signals:
    void modified();

private:
    double m_leftmost;
    double m_rightmost;
    bool m_dragging;
    bool m_linear;
    FPointArray m_points;
    FPointArray m_points_back;
    QPointF m_mousePos;

//    QPointF pointOnBezier(QPointF mouse);
    int m_selectedPoint;

};


#endif // CURVEEDITWIDGET_H
