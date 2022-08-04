#ifndef COLORPICKER_COLOR_H
#define COLORPICKER_COLOR_H

#include <QWidget>
#include <colorbutton.h>
#include "sccolor.h"
#include "colorblind.h"
#include "colorharmonywheel.h"
#include "colormap.h"

namespace Ui {
class ColorPickerColor;
}

class ColorPickerColor : public QWidget
{
    Q_OBJECT

public:    

    explicit ColorPickerColor(QWidget *parent = nullptr);
    explicit ColorPickerColor(ColorPickerConfig config, QWidget *parent = nullptr);
    ~ColorPickerColor();

    ScColor color();

    void setConfiguration(ColorPickerConfig config);
    ColorPickerConfig configuration();

private:
    enum SelectorMode {Slider = 0, Map = 1, Harmony = 2, Swatches = 3};

    Ui::ColorPickerColor *ui;
    ScColor m_color;
    ColorModel m_colorSpace;
    SelectorMode m_mode;
    VisionDefectColor::defectMode m_defectMode;
    ColorMap::Mode m_colorMapMode;
    ColorHarmonyWheel::Harmony m_harmony;
    ColorPickerConfig m_configuration;

    QMenu *menuColorBlind;
    QAction *actionColorBlindNormal;
    QAction *actionColorBlindRed;
    QAction *actionColorBlindGreen;
    QAction *actionColorBlindBlue;
    QAction *actionColorBlindFull;

    QMenu *menuSettings;
    QAction *actionColorBlind;
    QAction *actionSliderScale;

    QMenu *menuMapMode;
    QAction *actionMapHSVHue;
    QAction *actionMapHSVSaturation;
    QAction *actionMapHSVValue;
    QAction *actionMapRGBRed;
    QAction *actionMapRGBGreen;
    QAction *actionMapRGBBlue;
    QAction *actionMapLabL;
    QAction *actionMapLaba;
    QAction *actionMapLabb;

    QMenu *menuHarmony;
    QAction * actionHarmonyComplementary;
    QAction * actionHarmonySplitComplementary;
    QAction * actionHarmonyTriadic;
    QAction * actionHarmonyTetradic;
    QAction * actionHarmonySquare;
    QAction * actionHarmonyAnalogous;
    QAction * actionHarmonyMonochromatic;

    void setup();
    void connectSlots();
    void disconnectSlots();
    void updateColor(ScColor color);
    void updateColorButton(ColorButton *button, ScColor color);
    void updateColorLabel();


public slots:

    void setColor(ScColor color);

private slots:
    void changeSelectorMode();
    void switchColorBlind(bool enabled);
    void switchSliderScale(bool enabled);

    void setColorFromSwatch(ScColor color);

    void changeColor(ScColor color);
    void changeColorBlindness();
    void changeColorButtons(ColorHarmonyWheel::Harmony harmony);
    void changeColorSpace();
    void changeHarmony();
    void changeHarmonyColor();
    void changeMapMode();
    void changeUI();

signals:
    void colorChanged(ScColor);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // COLORPICKER_COLOR_H
