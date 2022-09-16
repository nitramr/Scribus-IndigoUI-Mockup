#include "color_button.h"

#include "popup_menu/popup_menu.h"

#include <QPainter>
#include <QPainterPath>
#include <render_utils.h>
#include "colorpicker.h"
#include "colorpicker_color.h"
#include "colorpicker_gradient.h"
#include "stickypopup_widget/stickypopup.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */
ColorButton::ColorButton(QWidget *parent) : QToolButton(parent)
{
    setFixedSize(26,26);
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

void ColorButton::setContextWidget(QWidget *widget, bool isFloating)
{

//    ColorPicker *colorPicker = qobject_cast<ColorPicker*>(widget);
//    ColorPickerColor *colorPickerColor = qobject_cast<ColorPickerColor*>(widget);
//    ColorPickerGradient *colorPickerGradient = qobject_cast<ColorPickerGradient*>(widget);

//    if(colorPicker){
//        connect(colorPicker, &ColorPicker::colorChanged, this, &ColorButton::setColor);
//        connect(colorPicker, &ColorPicker::gradientChanged, this, &ColorButton::setGradient);
//    }

//    if(colorPickerColor){
//        connect(colorPickerColor, &ColorPickerColor::colorChanged, this, &ColorButton::setColor);
//    }

//    if(colorPickerGradient){
//        connect(colorPickerGradient, &ColorPickerGradient::gradientChanged, this, &ColorButton::setGradient);
//    }


    if(isFloating){

        StickyPopup * stickyPopup = new StickyPopup(widget, this);

        connect(this, &ColorButton::clicked, this, [stickyPopup]() {
            if(stickyPopup->isVisible()){
                 stickyPopup->hide();
            }else{
                stickyPopup->show();
            }
        });

    }else{
        PopupMenu * menu = new PopupMenu(widget);

        this->setCheckable(true);
        this->setMenu(menu);

        connect(this, &ColorButton::toggled, this, [menu](bool t) {
            menu->setVisible(t);
            menu->raise();

        });

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

    int smallSide = backgroundDotSize().width();
    setBackground( RenderUtils::renderSplitColor(QSize(smallSide, smallSide), color.toQColor()) );

}

void ColorButton::setGradient(VGradient gradient)
{
    m_gradient = gradient;

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

