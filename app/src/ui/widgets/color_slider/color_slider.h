#ifndef COLORSLIDER_H
#define COLORSLIDER_H


#include <QSlider>
#include <sccolor.h>
#include "scribusapi.h"

class QPaintEvent;
class QWidget;

class SCRIBUS_API ColorSlider : public QSlider
{
    Q_OBJECT

public:

    enum Mode {
        Alpha = 0,
        HSVHue = 1, HSVSaturation = 2, HSVValue = 3,
        RGBRed = 4, RGBGreen = 5, RGBBlue = 6,
        LabLightness = 7, LabA = 8, LabB = 9,
        CMYKCyan = 10, CMYKMagenta = 11, CMYKYellow = 12, CMYKKey = 13,
        Shade = 14

    };

    ColorSlider(QWidget* parent = nullptr);
    ColorSlider(Mode mode, QWidget* parent = nullptr);

    Mode mode();

public slots:
    void setColor(ScColor color);
    void setMode(ColorSlider::Mode mode);
    void setValue(double value);

private slots:
    void updateColor();

protected:
    virtual void paintEvent(QPaintEvent * e);
    void resizeEvent(QResizeEvent* e);

private:
    QGradientStops m_stops;
    ScColor m_color;
    Mode m_mode {HSVHue};
    QImage m_background;

    void setup();
    void connectSlots();
    void disconnectSlots();

    void renderMap();
    void updateValues();

signals:
    void colorChanged(ScColor);
//    void valueChanged(double) ;


};

#endif // COLORSLIDER_H
