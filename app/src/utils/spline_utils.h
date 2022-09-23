#ifndef SPLINEUTILS_H
#define SPLINEUTILS_H

#include <QPointF>
#include <QList>

// Based on code of https://pomax.github.io/bezierinfo/#catmullconv

class SplineUtils
{
public:
    SplineUtils();

    /**
     * @brief CatmullToBezier
     * @param inputPoints Point Array of at least 4 points (p0, p1, p2, p3). You will get cubic bezier points from p1 to p2.
     * @param t
     * @return
     */
    static QList<QPointF> *catmullToBezier(QList<QPointF> inputPoints, double t = 1);

    static double distance(QPointF p1, QPointF p2);
//    static QPointF bezierArc(double point, double t);

//    static double bezierLength(double v, double from, double to, double epsilon);

//    static QPointF findPointOnBezier(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF point);
//    static QPointF pointAtBezier(QPointF p1, QPointF p2, QPointF p3, QPointF p4, double t);


};

#endif // SPLINEUTILS_H
