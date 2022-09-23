#include "spline_utils.h"
#include "qdebug.h"

SplineUtils::SplineUtils()
{

}

QList<QPointF> *SplineUtils::catmullToBezier(QList<QPointF> inputPoints, double t)
{
    // Inspired by the explanation on: https://pomax.github.io/bezierinfo/#catmullconv

    QList<QPointF> *result = new QList<QPointF>();

 //   qDebug() << "t" << t;

    double x0 = inputPoints[1].x();
    double y0 = inputPoints[1].y();
    double x1 = inputPoints[1].x() + (inputPoints[2].x() - inputPoints[0].x()) / (6 * t);
    double y1 = inputPoints[1].y() + (inputPoints[2].y() - inputPoints[0].y()) / (6 * t);
    double x2 = inputPoints[2].x() - (inputPoints[3].x() - inputPoints[1].x()) / (6 * t);
    double y2 = inputPoints[2].y() - (inputPoints[3].y() - inputPoints[1].y()) / (6 * t);
    double x3 = inputPoints[2].x();
    double y3 = inputPoints[2].y();

    result->append( QPointF(x0, y0) );
    result->append( QPointF(x1, y1) );
    result->append( QPointF(x2, y2) );
    result->append( QPointF(x3, y3) );

    return result;
}

double SplineUtils::distance(QPointF p1, QPointF p2)
{
    QPointF point = p2 - p1;
    return point.manhattanLength();
}

//QPointF SplineUtils::bezierArc(double point, double t)
//{
//    return QPointF(qPow(1 - t, 3) + 3 * pow(1 - t, 2) * t + 3* (1 - t) * t*t*point,
//                   3 * pow(1 - t, 2) * t*point + 3* (1 - t) * t*t + t*t*t);
//}

//double SplineUtils::bezierLength(double v, double from, double to, double epsilon)
//{
//    auto bisect = (from + to) / 2;
//    auto start = bezierArc(v, from);
//    auto middle = bezierArc(v,bisect);
//    auto end = bezierArc(v, to);

//    auto totalDistance = distance(start, end);
//    auto firstHalf = distance(middle, start);
//    auto secondHalf = distance(middle, end);
//    auto morePrecise = firstHalf + secondHalf;

//    if(morePrecise < totalDistance + epsilon){
//        return morePrecise;
//    }

//    return bezierLength(v, from, bisect, epsilon) + bezierLength(v, bisect, to, epsilon);

//}

//QPointF SplineUtils::findPointOnBezier(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF point)
//{

//    float detail = 10000;
//    double t = 0;
//    QPointF closest(0,0);
//    qreal minDist = 5; // std::numeric_limits<qreal>::max();// Mathf.Infinity;

//    // Create points on bezier curve
//    for (int i = 0; i < detail; i += 1)
//    {
//        QPointF p = pointAtBezier(p1, p2, p3, p4, t);

//        t+= i / detail;

//        float dist = distance(p, point);

//        if (dist < minDist)
//        {
//           // minDist = dist;
//            closest = p;
//            break;
//        }
//    }

//    return closest;
//}

//QPointF SplineUtils::pointAtBezier(QPointF p1, QPointF p2, QPointF p3, QPointF p4, double t)
//{
//    qreal x1 = p1.x();
//    qreal y1 = p1.y();
//    qreal x2 = p2.x();
//    qreal y2 = p2.y();
//    qreal x3 = p3.x();
//    qreal y3 = p3.y();
//    qreal x4 = p4.x();
//    qreal y4 = p4.y();

//    qreal x12 = (x2-x1)*t+x1;
//    qreal y12 = (y2-y1)*t+y1;

//    qreal x23 = (x3-x2)*t+x2;
//    qreal y23 = (y3-y2)*t+y2;

//    qreal x34 = (x4-x3)*t+x3;
//    qreal y34 = (y4-y3)*t+y3;

//    qreal x123 = (x23-x12)*t+x12;
//    qreal y123 = (y23-y12)*t+y12;

//    qreal x234 = (x34-x23)*t+x23;
//    qreal y234 = (y34-y23)*t+y23;

//    qreal x1234 = (x234-x123)*t+x123;
//    qreal y1234 = (y234-y123)*t+y123;

//    return QPointF(x1234, y1234);
//}
