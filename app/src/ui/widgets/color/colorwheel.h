#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <QWidget>

class ColorWheel : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWheel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    double m_hue;
    double m_saturation;
    double m_value;
    bool m_hitRing;

    QImage colorMap;
    QTransform m_transform;
    QPointF markRing;
    QRect canvas();
    QPainterPath ring();
    QPainterPath triangle();

    void updateRingMarker(QPointF pos);
    void renderTriangle();

    void setAngle(double angle);

signals:

};

#endif // COLORWHEEL_H
