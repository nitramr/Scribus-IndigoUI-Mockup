#include "basepointwidget.h"
#include "util_color.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BasePointWidget::BasePointWidget(Mode mode, QWidget *parent) : QWidget(parent)
{
    setFixedSize(QSize(51, 51));
    setMouseTracking(true);

    m_mode = mode;
    m_hoveredAnchor = None;
    m_pressed = false;
    anchors = QMap<AnchorPoint, QRect>();
    m_angle = 0;

    setup();

}

BasePointWidget::BasePointWidget(QWidget *parent) : BasePointWidget(BasePointWidget::Full, parent){}

void BasePointWidget::setup()
{
    int p = 8; // save area padding for rotation
    int s = 4; // space
    int a = 9; // anchor

    // Widget / Save Area ratio = 1:1.4
    // Sizes for rows and columns for square
    // |   p   |    a   |   s   |   a   |   s   |   a   |   p   |
    // |   8   |    8   |   5   |   8   |   5   |   8   |   8   | = 50
    // |   8   |    9   |   4   |   9   |   4   |   9   |   8   | = 51

    // Calculated TopLeft points of anchors
    // |       |  8,8   |       | 21,15 |       | 34,8  |       |
    // |       |  8,21  |       | 21,21 |       | 34,28 |       |
    // |       |  8,34  |       | 21,34 |       | 34,34 |       |

    // Add available anchor points

    switch(m_mode){
    case Mode::Full:
        m_baseRect = QRectF(p + a/2,
                           p + a/2,
                           (a + s) *2,
                           (a + s) *2
                           ).adjusted(0.5,0.5,0.5,0.5);
        m_selectedAnchor = TopLeft;

        anchors.insert(TopLeft,     QRect(p             ,p              ,a  ,a) );
        anchors.insert(Top,         QRect(p + a + s     ,p              ,a  ,a) );
        anchors.insert(TopRight,    QRect(p +(a + s) *2 ,p              ,a  ,a) );
        anchors.insert(Left,        QRect(p             ,p + a + s      ,a  ,a) );
        anchors.insert(Center,      QRect(p + a + s     ,p + a + s      ,a  ,a) );
        anchors.insert(Right,       QRect(p +(a + s) *2 ,p + a + s      ,a  ,a) );
        anchors.insert(BottomLeft,  QRect(p             ,p +(a + s) *2  ,a  ,a) );
        anchors.insert(Bottom,      QRect(p + a + s     ,p +(a + s) *2  ,a  ,a) );
        anchors.insert(BottomRight, QRect(p +(a + s) *2 ,p +(a + s) *2  ,a  ,a) );

        break;
    case Mode::Frame:
        m_baseRect = QRectF(p + a/2,
                           p + a/2,
                           (a + s) *2,
                           (a + s) *2
                           ).adjusted(0.5,0.5,0.5,0.5);
        m_selectedAnchor = TopLeft;

        anchors.insert(TopLeft,     QRect(p             ,p              ,a  ,a) );
        anchors.insert(TopRight,    QRect(p +(a + s) *2 ,p              ,a  ,a) );
        anchors.insert(Center,      QRect(p + a + s     ,p + a + s      ,a  ,a) );
        anchors.insert(BottomLeft,  QRect(p             ,p +(a + s) *2  ,a  ,a) );
        anchors.insert(BottomRight, QRect(p +(a + s) *2 ,p +(a + s) *2  ,a  ,a) );

        break;
    case Mode::Line:
        m_baseRect = QRectF(p + a/2,
                           p + a + s + a/2,
                           (a + s) *2,
                           1
                           ).adjusted(0.5,0.5,-0.5,-0.5);
        m_selectedAnchor = Left;

        anchors.insert(Left,        QRect(p             ,p + a + s      ,a  ,a) );
        anchors.insert(Center,      QRect(p + a + s     ,p + a + s      ,a  ,a) );
        anchors.insert(Right,       QRect(p +(a + s) *2 ,p + a + s      ,a  ,a) );
    break;

    }
}


/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void BasePointWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p;
    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setTransform(m_transform, true);

    QColor normal( ColorUtils::colorBlend( palette().color(QPalette::WindowText), QColor(128,128,128), 0.8 ));
    QColor dark( ColorUtils::colorAlpha( palette().color(QPalette::WindowText), 0.15 ));

//    QColor normal(palette().color(QPalette::WindowText));
//    QColor dark(palette().color(QPalette::Dark));

    // Base
    p.setBrush(QBrush( dark ));
    p.setPen(QPen( normal, 1) );
    p.drawRect(m_baseRect);

    p.setPen(Qt::NoPen);

    // Anchor Normal    
    p.setBrush(QBrush( normal ));

    QMapIterator<AnchorPoint, QRect> i(anchors);
    while (i.hasNext()) {
        i.next();
        p.drawRect( i.value().adjusted(2,2,-2,-2));
    }


    // Anchor Hovered
    if (m_hoveredAnchor != None)
    {
        p.setBrush(QBrush(palette().color(QPalette::Highlight)));
        p.drawRect(anchors.value(m_hoveredAnchor));
    }


    // Anchor Selected
    p.setBrush(palette().color(QPalette::WindowText));
    p.drawRect(anchors.value(m_selectedAnchor));

    p.end();

}

void BasePointWidget::mousePressEvent(QMouseEvent *m)
{
    m->accept();
    m_pressed = true;
}

void BasePointWidget::mouseReleaseEvent(QMouseEvent *m)
{
    m->accept();
    if (m_pressed)
    {
        QPoint p = mapToTransformation(m->pos());

        QMapIterator<AnchorPoint, QRect> i(anchors);
        while (i.hasNext()) {
            i.next();
            if(i.value().contains(p)) m_selectedAnchor = i.key();
        }

        emit buttonClicked(m_selectedAnchor);
    }
    update();
}

void BasePointWidget::mouseMoveEvent(QMouseEvent *m)
{
    m->accept();

    QPoint p = mapToTransformation(m->pos());

    m_hoveredAnchor = None;

    QMapIterator<AnchorPoint, QRect> i(anchors);
    while (i.hasNext()) {
        i.next();
        if(i.value().contains(p)) m_hoveredAnchor = i.key();
    }

    update();
}

void BasePointWidget::leaveEvent(QEvent*)
{
    m_hoveredAnchor = None;
    update();
}

/* ********************************************************************************* *
 *
 * Helper
 *
 * ********************************************************************************* */

QPoint BasePointWidget::mapToTransformation(QPoint position)
{
    return position * m_transform.inverted();
}


/* ********************************************************************************* *
 *
 * Properties
 *
 * ********************************************************************************* */

BasePointWidget::AnchorPoint BasePointWidget::selectedAnchor()
{
    return m_selectedAnchor;
}

void BasePointWidget::setSelectedAnchor(AnchorPoint id)
{
    m_selectedAnchor = id;
    update();
}

void BasePointWidget::setMode(Mode mode)
{
    m_mode = mode;
    anchors.clear();
    setup();
    update();
}

void BasePointWidget::setAngle(int angle)
{
    m_angle = angle;
    QPoint center = rect().center();
    m_transform = QTransform()
            .translate( center.x() + 1, center.y() + 1 )
            .rotate( m_angle )
            .translate( -center.x() - 1, -center.y() - 1 );

    update();
}

int BasePointWidget::angle()
{
    return m_angle;
}

BasePointWidget::Mode BasePointWidget::mode()
{
    return m_mode;
}
