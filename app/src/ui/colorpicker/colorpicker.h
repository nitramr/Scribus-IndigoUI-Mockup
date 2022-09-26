#ifndef COLORPICKER_H
#define COLORPICKER_H

//#include "colorbutton.h"
#include "enums.h"
#include "sccolor.h"
#include "vgradient.h"
#include <QButtonGroup>
#include <QWidget>

class ColorButton;

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT

public:



    explicit ColorPicker(ColorPickerConfig config, QWidget *parent = nullptr);
    ~ColorPicker();

    void setConfiguration(ColorPickerConfig config);
    ColorPickerConfig configuration();

    void setColorButton(ColorButton *button);
    ColorButton *colorButton();

public slots:
//    void setColorButton(ColorButton *button);

    void setColor(ScColor color);
    void setGradient(VGradient gradient);
    void setPattern();
    void setImage();

private slots:
//    void updateColorButton();

    void updateColor(ScColor color);
    void updateGradient(VGradient gradient);
    void updatePattern();
    void updateImage();
    void updateSize();

    void updatePicker(ItemFillMode mode);
    void changedTab();

private:

    Ui::ColorPicker *ui;

 //   ColorButton *m_colorButton;
    ItemFillMode m_fillMode;
    ScColor m_color;
    VGradient m_gradient;
    ColorPickerConfig m_configuration {ColorPickerConfig::Default};
    QButtonGroup *m_buttonGroup;

    ColorButton *m_colorButton;

    void setup();
    void connectSlots();

signals:

    void colorChanged(ScColor);
    void gradientChanged(VGradient);
    void patternChanged();
    void imageChanged();
};

#endif // COLORPICKER_H
