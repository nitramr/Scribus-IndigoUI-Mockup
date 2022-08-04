#ifndef COLORMAP_H
#define COLORMAP_H

#include "sccolor.h"
#include <QWidget>

class ColorMap : public QWidget
{
    Q_OBJECT

public:

    enum Mode {
        HSVHue = 0, HSVSaturation = 1, HSVValue = 2,
        RGBRed = 3, RGBGreen = 4, RGBBlue = 5,
        LabLightness = 6, LabA = 7, LabB = 8
    };

    explicit ColorMap(QWidget *parent = nullptr);

    ColorMap::Mode mode();
    ScColor color();

public slots:
    void setColor(ScColor color);
    void setMode(ColorMap::Mode mode);

private:
    QImage m_colorMap;
    Mode m_drawMode { HSVHue };
    ScColor m_color;
    QPointF m_mark;
    QRect canvas();
    QPointF posFromCanvas(QPointF pos);
    QPointF posToCanvas(QPointF pos);

    void renderMap();

protected:

//    void drawHSV(int w, int h, qreal base);

    void drawHSVHue(int w, int h);
    void drawHSVSaturation(int w, int h);
    void drawHSVValue(int w, int h);
    void drawRGBRed(int w, int h);
    void drawRGBGreen(int w, int h);
    void drawRGBBlue(int w, int h);
    void drawLabLightness(int w, int h);
    void drawLabA(int w, int h);
    void drawLabB(int w, int h);

    void colorFromPosition(QPointF pos);
    void positionFromColor(ScColor color);

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent* e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void colorChanged(ScColor color);
};

#endif // COLORMAP_H
