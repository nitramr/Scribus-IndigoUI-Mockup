#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H


#include "colorpicker.h"
#include "vgradient.h"
#include <QToolButton>
#include <QWidget>
#include <sccolor.h>

class ColorButton : public QToolButton
{
    Q_OBJECT
public:

    enum ColorPickerType {
        None = 0,
        ColorPickerFull = 1,
        ColorPickerSolid = 2
    };

    ColorButton(QWidget *parent = nullptr);
    ColorButton(ColorPickerConfig config, ColorPickerType type = ColorPickerType::ColorPickerFull, QWidget *parent = nullptr);
    ~ColorButton(){};

    bool hasDot();
    ScColor color();
    VGradient gradient();
    QSize backgroundDotSize();
    QSize foregroundDotSize();

    void setConfiguration(ColorPickerConfig config);
    ColorPickerConfig configuration();

    void setColorPickerType(ColorPickerType type);


public slots:
    void setBackground(QBrush background);
    void setForeground(QBrush foreground);
    void setHasDot(bool enabled);
    void setColor(ScColor color);
    void setGradient(VGradient gradient);
    void showContext();

protected:
    void paintEvent(QPaintEvent *e);

    void renderFill(QPainter *painter, QPointF center, qreal radius, QBrush background);

private:
    QBrush m_background {Qt::NoBrush};
    QBrush m_foreground {Qt::NoBrush};
    bool m_hasDot {false};
    ScColor m_color;
    VGradient m_gradient;

    ItemFillMode m_fillMode;
    ColorPickerConfig m_config;
    ColorPickerType m_colorPickerType {ColorPickerType::ColorPickerFull};

private slots:
    void setColorFromPicker(ScColor color);
    void setGradientFromPicker(VGradient gradient);

signals:
    void colorChanged(ScColor);
    void gradientChanged(VGradient);

};

#endif // COLOR_BUTTON_H
