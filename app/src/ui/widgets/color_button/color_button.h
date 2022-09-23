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
    ColorButton(QWidget *parent = nullptr);
    ~ColorButton(){};

    bool hasDot();
    ScColor color();
    VGradient gradient();
    QSize backgroundDotSize();
    QSize foregroundDotSize();

    void setContextWidget(QWidget *widget, bool isFloating = true);


public slots:
    void setBackground(QBrush background);
    void setForeground(QBrush foreground);
    void setHasDot(bool enabled);
    void setColor(ScColor color);
    void setGradient(VGradient gradient);

protected:
    void paintEvent(QPaintEvent *e);

    void renderFill(QPainter *painter, QPointF center, qreal radius, QBrush background);

private:
    QBrush m_background {Qt::NoBrush};
    QBrush m_foreground {Qt::NoBrush};
    bool m_hasDot {false};
    ScColor m_color;
    VGradient m_gradient;


};

#endif // COLOR_BUTTON_H