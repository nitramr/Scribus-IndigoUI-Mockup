#include "color_button.h"

#include "popup_menu/popup_menu.h"

#include <QPainter>
#include <QPainterPath>
#include <render_utils.h>
#include "colorpicker.h"
#include "colorpicker_color.h"
#include "stickypopup_widget/stickypopup.h"
#include "widget_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */
ColorButton::ColorButton(QWidget *parent) : ColorButton(ColorPickerConfig::Default, ColorPickerType::ColorPickerFull, parent){}

ColorButton::ColorButton(ColorPickerConfig config, ColorPickerType type, QWidget *parent) : QToolButton(parent)
{
    setFixedSize(26,26);
    setColor( ScColor(128,128,128) );
    setConfiguration(config);
    setColorPickerType(type);

}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */


bool ColorButton::hasDot()
{
    return m_hasDot;
}

ScColor ColorButton::color()
{
    return m_color;
}

VGradient ColorButton::gradient()
{
    return m_gradient;
}



QSize ColorButton::backgroundDotSize()
{
    int smallestSize = qMin(height(), width());

    return QSize(smallestSize,smallestSize);
}

QSize ColorButton::foregroundDotSize()
{
    int smallestSize = qMin(height()/2, width()/2);

    return QSize(smallestSize,smallestSize);
}

void ColorButton::setConfiguration(ColorPickerConfig config)
{
    m_config = config;
}

ColorPickerConfig ColorButton::configuration()
{
    return m_config;
}

void ColorButton::setColorPickerType(ColorPickerType type)
{
    m_colorPickerType = type;

    switch(m_colorPickerType){
    case ColorPickerType::ColorPickerFull:
    case ColorPickerType::ColorPickerSolid:
        connect(this, &QToolButton::pressed, this, &ColorButton::showContext);
        break;
    case ColorPickerType::None:
        disconnect(this, &QToolButton::pressed, this, &ColorButton::showContext);
        break;
    }

}

/* ********************************************************************************* *
 *
 * Methods
 *
 * ********************************************************************************* */

void ColorButton::renderFill(QPainter *painter, QPointF center, qreal radius, QBrush background)
{
    RenderUtils::renderCircularHandle(painter, center, radius, background);
}

void ColorButton::setColorFromPicker(ScColor color)
{
    ColorPicker * colorPicker = qobject_cast<ColorPicker*>(sender());

    if(colorPicker->colorButton() == this){
        setColor(color);
        emit colorChanged(color);
    }
}

void ColorButton::setGradientFromPicker(VGradient gradient)
{
    ColorPicker * colorPicker = qobject_cast<ColorPicker*>(sender());

    if(colorPicker->colorButton() == this){
        setGradient(gradient);
        emit gradientChanged(gradient);
    }
}


/* ********************************************************************************* *
 *
 * Slots
 *
 * ********************************************************************************* */
void ColorButton::setBackground(QBrush background)
{
    m_background = background;
    update();
}

void ColorButton::setForeground(QBrush foreground)
{
    m_foreground = foreground;
    update();
}

void ColorButton::setHasDot(bool enabled)
{
    m_hasDot = enabled;
    update();
}

void ColorButton::setColor(ScColor color)
{
    m_color = color;
    m_fillMode = ItemFillMode::Solid;

    int smallSide = backgroundDotSize().width();
    setBackground( RenderUtils::renderSplitColor(QSize(smallSide, smallSide), color.toQColor()) );

}

void ColorButton::setGradient(VGradient gradient)
{
    m_gradient = gradient;
    m_fillMode = ItemFillMode::Gradient;

    switch(m_gradient.type()){
    default:
    case GradientType::Linear:{
        QLinearGradient grad = gradient.toQLinearGradient();
        grad.setStart(0,0);
        grad.setFinalStop(width(), 0);

        QBrush background(grad);
        setBackground(background);
    }
        break;
    case GradientType::Radial:{
        QPointF center = QPointF( (width() -1 ) / 2., (height() -1 ) / 2. );
        QRadialGradient grad = gradient.toQRadialGradient();
        grad.setCenter( center );
        grad.setRadius( width()/2. );
        grad.setFocalPoint( center );

        QBrush background(grad);
        setBackground(background);
    }
        break;
    case GradientType::Conical:{
        QConicalGradient grad = gradient.toQConicalGradient();
        grad.setCenter(this->rect().center());

        QBrush background(grad);
        setBackground(background);
    }
        break;
    }



}

void ColorButton::showContext()
{

    WidgetManager &widgetManager = WidgetManager::instance();

    StickyPopup *popup;

    switch(m_colorPickerType){
    case ColorPickerType::ColorPickerFull:{
        popup = widgetManager.colorPicker();
        break;
    }
    default:
    case ColorPickerType::ColorPickerSolid:{
        popup = widgetManager.colorPickerColor();
        break;
    }
    }

    if(popup != nullptr){
        ColorPicker *colorPicker = qobject_cast<ColorPicker*>(popup->child());

        if(colorPicker != nullptr){
            colorPicker->setColorButton(this);
            colorPicker->setConfiguration(m_config);

            switch(m_fillMode){
            case ItemFillMode::Solid:
                colorPicker->setColor(m_color);
                break;
            case ItemFillMode::Gradient:
                colorPicker->setGradient(m_gradient);
                break;
            default:
                break;
            }

            connect(colorPicker, &ColorPicker::colorChanged, this, &ColorButton::setColorFromPicker);
            connect(colorPicker, &ColorPicker::gradientChanged, this, &ColorButton::setGradientFromPicker);

        }

        popup->show(this);
    }



    //    switch(m_colorPickerType){
    //    case ColorPickerType::ColorPickerFull:{

    //        StickyPopup *popup = widgetManager.colorPicker();
    //        ColorPicker *colorPicker = qobject_cast<ColorPicker*>(popup->child());

    //        if(colorPicker != nullptr){
    //            colorPicker->setColorButton(this);
    //            colorPicker->setConfiguration(m_config);

    //            switch(m_fillMode){
    //            case ItemFillMode::Solid:
    //                colorPicker->setColor(m_color);
    //                break;
    //            case ItemFillMode::Gradient:
    //                colorPicker->setGradient(m_gradient);
    //                break;
    //            default:
    //                break;
    //            }

    //            connect(colorPicker, &ColorPicker::colorChanged, this, &ColorButton::setColorFromPicker);
    //            connect(colorPicker, &ColorPicker::gradientChanged, this, &ColorButton::setGradientFromPicker);

    //        }

    //        popup->show(this);

    //        break;
    //    }
    //    case ColorPickerType::ColorPickerSolid:{

    //        StickyPopup *popup = widgetManager.colorPickerColor();

    //        ColorPicker *solidColor = qobject_cast<ColorPicker*>(popup->child());

    //        if(solidColor != nullptr){
    //            solidColor->setColorButton(this);
    //            solidColor->setConfiguration(m_config);

    //            switch(m_fillMode){
    //            case ItemFillMode::Solid:
    //                solidColor->setColor(m_color);
    //                break;
    //            default:
    //                break;
    //            }

    //            connect(solidColor, &ColorPicker::colorChanged, this, &ColorButton::setColorFromPicker);


    //        }

    //        popup->show(this);

    //        break;
    //    }
    //    }



}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */


void ColorButton::paintEvent(QPaintEvent *e)
{    
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QSize bSize = backgroundDotSize();
    QSize fSize = foregroundDotSize();
    QPainterPath mask;

    int m_inset = 1;

    // Draw Background Dot
    QRectF bDot(rect().center() - QPointF(fSize.width() - m_inset -0.5 , fSize.height() - m_inset - 0.5), QSizeF(bSize.width() - m_inset, bSize.height() - m_inset) );
    mask.addEllipse(bDot.adjusted(m_inset,m_inset,-m_inset,-m_inset));
    painter.setClipPath(mask);
    RenderUtils::renderPattern(&painter, mask.boundingRect());
    painter.setClipping(false);


    renderFill(&painter, bDot.center(), bSize.width() - m_inset, m_background);

    // Draw Foreground Dot
    if(m_hasDot){
        mask.clear();
        QRectF fDot(rect().center().x(), rect().center().y(), fSize.width(), fSize.height());
        mask.addEllipse(fDot.adjusted(m_inset,m_inset,-m_inset,-m_inset));
        painter.setClipPath(mask);
        RenderUtils::renderPattern(&painter, mask.boundingRect());
        painter.setClipping(false);

        renderFill(&painter, fDot.center(), fSize.width() - m_inset, m_foreground);
    }

    painter.end();

}

