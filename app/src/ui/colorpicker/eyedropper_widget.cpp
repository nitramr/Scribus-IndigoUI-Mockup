#include "eyedropper_widget.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>

EyeDropperWidget::EyeDropperWidget(QWidget *parent)
    : QWidget{parent, Qt::Window | Qt::Tool | Qt::FramelessWindowHint}
{
    setMouseTracking(true);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void EyeDropperWidget::show()
{
    QScreen *screen = QGuiApplication::screenAt(QPoint());

    QRect screenRect = screen->geometry();
    m_screenshot = screen->grabWindow(0, 0, 0, screenRect.width(), screenRect.height());

    qDebug() << screenRect;
    setGeometry(screenRect);

    QWidget::show();
}

/* ********************************************************************************* *
 *
 * Public Events
 *
 * ********************************************************************************* */

void EyeDropperWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.drawPixmap(this->rect(), m_screenshot);

    painter.setPen(Qt::red);
    painter.drawRect(this->rect());

    // Paint Magnifier
    painter.drawEllipse(QRect(m_MousePos.x() - 30, m_MousePos.y() - 30, 60,60));

    painter.end();
}

void EyeDropperWidget::mousePressEvent(QMouseEvent *m)
{


}

void EyeDropperWidget::mouseReleaseEvent(QMouseEvent *m)
{
    ScColor color = grabScreenColor(m->pos());

    qDebug() << "EyeDropper Color:" << color;

    emit screenColor(color);

    this->hide();
}

void EyeDropperWidget::mouseMoveEvent(QMouseEvent *m)
{
    m_MousePos = m->pos();
    update();
}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */


ScColor EyeDropperWidget::grabScreenColor(const QPoint &p)
{
        QColor color = m_screenshot.toImage().pixel(p);
        ScColor sColor;
        sColor.fromQColor(color);

        return sColor;
}
