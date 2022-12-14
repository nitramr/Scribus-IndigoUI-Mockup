#ifndef COLORPICKER_GRADIENT_H
#define COLORPICKER_GRADIENT_H


#include "colorpicker_color.h"
#include "enums.h"
#include "vgradient.h"
#include <QWidget>

namespace Ui {
class ColorPickerGradient;
}

class ColorPickerGradient : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerGradient(QWidget *parent = nullptr);
    ~ColorPickerGradient();

    VGradient gradient();

    void setConfiguration(ColorPickerConfig config);
    ColorPickerConfig configuration();

private:
    Ui::ColorPickerGradient *ui;

    GradientType m_mode;
    VGradient m_gradient;
    ColorPickerConfig m_configuration {ColorPickerConfig::Default};


    void setup();
    void connectSlots();
    void disconnectSlots();
    void changeUI();
    void createGradient();
    void updateGradientControls();

private slots:
    void changeSelectorMode();    

    void updateGradientColor(ScColor color);
    void updateSimpleGradientInputPosition(double position);
    void updateSimpleGradientStep(int position);

//    void colorButtonClick();

public slots:
    void setGradient(VGradient gradient);
    void changeSize();

signals:
    void gradientChanged(VGradient);
     void sizeChanged();

};

#endif // COLORPICKER_GRADIENT_H
