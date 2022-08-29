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
    ColorPickerColor *colorPickerEdit;
    ColorPickerColor *colorPicker4CTopLeft;
    ColorPickerColor *colorPicker4CTopRight;
    ColorPickerColor *colorPicker4CBottomLeft;
    ColorPickerColor *colorPicker4CBottomRight;
    ColorPickerColor *colorPickerMeshNode;
    ColorPickerConfig m_configuration {ColorPickerConfig::Default};


    void setup();
    void connectSlots();
    void disconnectSlots();
    void changeUI();
    void createGradient();

private slots:
    void changeSelectorMode();    

    void openColorPicker();

    void update4ColorGradientColor(ScColor color);
    void updateMeshNodeGradientColor(ScColor color);
    void updateSimpleGradientColor(ScColor color);
    void updateSimpleGradientInputPosition(double position);
    void updateSimpleGradientStep(int position);

public slots:
    void setGradient(VGradient gradient);
    void changeSize();

signals:
    void gradientChanged(VGradient);
     void sizeChanged();

};

#endif // COLORPICKER_GRADIENT_H
