#ifndef IMAGEEFFECT_COLORIZE_H
#define IMAGEEFFECT_COLORIZE_H

#include "colorpicker.h"
#include "component_curvewidget.h"
#include "imageeffect_item.h"

namespace Ui {
class ImageEffectColorize;
}

class ImageEffectColorize : public ImageEffectItem
{
    Q_OBJECT

public:

    enum Mode {
        Colorize = 0,
        Duotone = 1,
        Tritone = 2,
        Quadtone = 3
    };

    explicit ImageEffectColorize(Mode mode = Mode::Colorize, QWidget *parent = nullptr);
    ~ImageEffectColorize();

    void setMode(Mode mode);
    Mode mode();

private:
    Ui::ImageEffectColorize *ui;

    Mode m_mode;

    ComponentCurveWidget *curveWidget1;
    ComponentCurveWidget *curveWidget2;
    ComponentCurveWidget *curveWidget3;
    ComponentCurveWidget *curveWidget4;

    void setup();
    void connectSlots();
    void addMenu(QToolButton *button, QWidget *menuPanel);

private slots:
    void setColor1(ScColor color);
    void setColor2(ScColor color);
    void setColor3(ScColor color);
    void setColor4(ScColor color);

};

#endif // IMAGEEFFECT_COLORIZE_H
