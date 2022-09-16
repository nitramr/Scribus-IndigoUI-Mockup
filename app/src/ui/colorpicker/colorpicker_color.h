#ifndef COLORPICKER_COLOR_H
#define COLORPICKER_COLOR_H

#include <QWidget>
#include "color_button/color_button.h"
#include <QComboBox>
#include "eyedropperscreen_widget/eyedropperscreen_widget.h"
#include "sccolor.h"
#include "colorblind.h"
#include "colorharmony_wheel/colorharmony_wheel.h"
#include "color_map/color_map.h"

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

    enum PickerMode {Map = 0, Harmony = 1};

    Ui::ColorPickerColor *ui;
    ScColor m_color;
    ColorModel m_colorSpace;
    VisionDefectColor::defectMode m_defectMode;
    ColorMap::Mode m_colorMapMode;
    ColorHarmonyWheel::Harmony m_harmony;
    PickerMode m_pickerMode;
    ColorPickerConfig m_configuration;
    QToolButton *buttonPickerToggle;
    QComboBox * comboColorSpace;
    EyeDropperScreenWidget * eyeDropper;

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

    QMenu *menuPicker;
    QAction * actionPickerMap;
    QAction * actionPickerHarmony;

    void setup();
    void connectSlots();
    void disconnectSlots();
    void updateColor(ScColor color);
    void updateColorButton(ColorButton *button, ScColor color);
    void updateColorLabel();

    void setVisibleSwatches(bool isVisible);
    void setVisiblePicker(bool isVisible);
    void setVisibleAlpha(bool isVisible);
    void setVisibleShade(bool isVisible);



public slots:

    void setColor(ScColor color);

private slots:

    void switchColorBlind(bool enabled);
    void switchSliderScale(bool enabled);

    void setColorFromSwatch(ScColor color);
    void setColorFromEyeDropper(QColor color);
    void setSpotFlag(bool isSpot);

    void changeColor(ScColor color);
    void changeColorBlindness();
    void changeColorButtons(ColorHarmonyWheel::Harmony harmony);
    void changeColorSpace();
    void changeHarmony();
    void changeHarmonyColor();
    void changeMapMode();
    void changeUI();
    void changeSize();
    void changePickerMode();

signals:
    void colorChanged(ScColor);
    void sizeChanged();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // COLORPICKER_COLOR_H
