#include "colorbutton.h"
#include "menu_popup.h"

#include <QPainter>
#include <QPainterPath>
#include <util_render.h>
#include "colorpicker.h"

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
    int smalletestSize = qMin(height(), width());

    return QSize(smalletestSize,smalletestSize);
}

QSize ColorButton::foregroundDotSize()
{
    int smalletestSize = qMin(height()/2, width()/2);

    return QSize(smalletestSize,smalletestSize);
}

void ColorButton::setContextWidget(QWidget *widget)
{
//    MenuPopup * menu = new MenuPopup(widget);
//    menu->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

//    this->setCheckable(true);
//    this->setMenu(menu);

//    connect(this, &ColorButton::toggled, this, [menu](bool t) {
//        menu->setVisible(t);
//        menu->raise();
//        menu->activateWindow();

//    });

   // this->setCheckable(true);
    connect(this, &ColorButton::clicked, this, [widget]() {
        if(widget->isVisible()){
             widget->setVisible(false);
        }else{
            widget->setVisible(true);
            widget->raise();
            widget->activateWindow();
        }
    });


}

/* ********************************************************************************* *
 *
 * Methods
 *
 * ********************************************************************************* */

void ColorButton::renderFill(QPainter *painter, QPointF center, qreal radius, QBrush background)
{
    UtilRender::renderCircularHandle(painter, center, radius, background);
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
    setBackground( UtilRender::renderSplitColor(QSize(smallSide, smallSide), color.toQColor()) );

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
    UtilRender::renderPattern(&painter, mask.boundingRect());
    painter.setClipping(false);


    renderFill(&painter, bDot.center(), bSize.width() - m_inset, m_background);

    // Draw Foreground Dot
    if(m_hasDot){
        mask.clear();
        QRectF fDot(rect().center().x(), rect().center().y(), fSize.width(), fSize.height());
        mask.addEllipse(fDot.adjusted(m_inset,m_inset,-m_inset,-m_inset));
        painter.setClipPath(mask);
        UtilRender::renderPattern(&painter, mask.boundingRect());
        painter.setClipping(false);

        renderFill(&painter, fDot.center(), fSize.width() - m_inset, m_foreground);
    }

    painter.end();

}

