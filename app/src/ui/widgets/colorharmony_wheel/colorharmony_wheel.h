#ifndef COLORHARMONYWHEEL_H
#define COLORHARMONYWHEEL_H

#include <QMap>
#include <QWidget>
#include <sccolor.h>

class ColorHarmonyWheel : public QWidget
{
    Q_OBJECT


public:

    enum Color {
        Main = 0,
        Variant1 = 1,
        Variant2 = 2,
        Variant3 = 3,
        Variant4 = 4
    };

    enum Harmony {
        None = 0,
        Monochromatic = 1,
        Complementary = 2,
        SplitComplementary = 3,
        Analogous = 4,
        Triadic = 5,
        Tetradic = 6,
        Square = 7
    };

    explicit ColorHarmonyWheel(QWidget *parent = nullptr);

    Harmony harmony();
    ScColor color(ColorHarmonyWheel::Color color);
    QPointF position(ColorHarmonyWheel::Color color);
    QMap<ColorHarmonyWheel::Color, ScColor> colors();

public slots:
    void setHarmony(ColorHarmonyWheel::Harmony harmony);
    void setColor(ScColor color);


protected:

    void renderMap();

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent* e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:

    bool m_hitWheel {false};
    double m_value;
    double m_alpha;
    double m_shade;
    QPainterPath wheel();
    QRect canvas();
    QMap<ColorHarmonyWheel::Color, QPair<QPointF, ScColor>> m_colors;
    Harmony m_harmony;
    QImage m_map;

    void setup();
    void positionFromColor(ScColor color);
    void updateRingMarker(QPointF pos);
    void updateColorPoint(ColorHarmonyWheel::Color color, QPointF pos, double angle, double s = 1.0);
    double normalizeAngle(double angle);

signals:
    void colorChanged(ScColor color);
    void harmonyChanged(ColorHarmonyWheel::Harmony harmony);

};

#endif // COLORHARMONYWHEEL_H
