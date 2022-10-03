#include "eyedropperscreen_widget.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

EyeDropperScreenWidget::EyeDropperScreenWidget(QWidget *parent)
    : QWidget{parent, /*Qt::Window |*/ Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint}
{
    setMouseTracking(true);
    m_zoomFactor = 12;
    m_magnifierSize = QSize(120, 120); // this must be a multiple of zoom factor
    m_grid = true;
    m_drawMagnifier = false;
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void EyeDropperScreenWidget::show()
{
    takeScreenshot();
    setGeometry(m_screenshot.rect());
    m_drawMagnifier = false;
    QWidget::show();
}

/* ********************************************************************************* *
 *
 * Public Events
 *
 * ********************************************************************************* */

void EyeDropperScreenWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    // Screenshot
    QPainter painter(this);
    painter.drawPixmap(rect(), m_screenshot);

    if(m_drawMagnifier){

        // Magnifier mask
        QPainterPath mask;
        mask.addEllipse(magnifierRect());

        // Magnifier zoom pixmap
        QPixmap pixmapZoom;
        pixmapZoom = m_screenshot.copy(magnifierRect(m_zoomFactor));
        pixmapZoom.scaled(magnifierRect().size());

        painter.setClipPath(mask);
        painter.drawPixmap(magnifierRect(), pixmapZoom);

        // Magnifier pixel grid
        if(m_grid){

            QRect gridRect = magnifierRect();

            QVarLengthArray<QLineF, 1> lines;
            for (int x = gridRect.left(); x < gridRect.right(); x += m_zoomFactor)
                lines.append(QLineF(x, gridRect.top(), x, gridRect.bottom()));

            for (int y = gridRect.top(); y < gridRect.bottom(); y += m_zoomFactor)
                lines.append(QLineF(gridRect.left(), y, gridRect.right(), y));

            QColor gridColor(128,128,128);
            gridColor.setAlphaF(0.2);

            painter.setPen(gridColor);
            painter.drawLines(lines.data(), lines.size());

        }

        painter.setClipping(false);

        // Magnifier border
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawEllipse(magnifierRect().adjusted(-1, -1, 1, 1));
        painter.setPen(QPen(Qt::white, 2));
        painter.drawEllipse(magnifierRect());

        // Magnifier color label
        QFont m_labelFont(font());
        m_labelFont.setPointSize(8);
        QString m_labelText = QString("%1, %2, %3").arg(m_color.red()).arg(m_color.green()).arg(m_color.blue());
        QRect m_labelRect = labelRect(m_labelFont, m_labelText);

        painter.setFont(m_labelFont);
        painter.setBrush(palette().color(QPalette::Window));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(m_labelRect, 2, 2);
        painter.setPen(palette().color(QPalette::WindowText));
        painter.drawText(m_labelRect, Qt::AlignVCenter | Qt::AlignCenter, m_labelText);

    }

    painter.end();
}


void EyeDropperScreenWidget::mouseReleaseEvent(QMouseEvent *m)
{
    m_color = grabScreenColor(m->pos());
    emit screenColor(m_color);

    hide();
}

void EyeDropperScreenWidget::mouseMoveEvent(QMouseEvent *m)
{
    m_mousePos = m->pos();
    m_color = grabScreenColor(m->pos());
    m_drawMagnifier = true;
    update();
}

void EyeDropperScreenWidget::keyPressEvent(QKeyEvent *e)
{

    switch(e->key()){
    case Qt::Key_Backspace:
    case Qt::Key_Escape:

        hide();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */


QColor EyeDropperScreenWidget::grabScreenColor(const QPoint &p)
{
    if(!m_screenshot.rect().contains(p)) return QColor(0,0,0);

    return m_screenshot.toImage().pixel(p);
}

void EyeDropperScreenWidget::takeScreenshot()
{
    QList<QScreen*> screens = QGuiApplication::screens();
    QList<QPair<QRect, QPixmap>> screenshots;
    QRect bounds;

    // take screenshot of each screen
    foreach (auto screen, screens) {

        QRect rect = screen->geometry();
        QPixmap pixmap = screen->grabWindow(0);

        // extend final screenshot size
        bounds = bounds.united(rect);

        // add screenshot
        QPair<QRect, QPixmap> screenshot(rect, pixmap);
        screenshots.append(screenshot);
    }

    QPixmap finalScreenshot(bounds.width(), bounds.height());
    QPainter painter(&finalScreenshot);
    finalScreenshot.fill(Qt::black);

    // draw each screenshot on right position
    foreach (auto screenshot, screenshots) {
        painter.drawPixmap(screenshot.first, screenshot.second);
    }

    m_screenshot = finalScreenshot;

}

const QRect EyeDropperScreenWidget::magnifierRect(int zoomFactor)
{
    zoomFactor = qBound(1, zoomFactor, 16);

    int xPos = qBound(0, m_mousePos.x(), m_screenshot.width());
    int yPos = qBound(0, m_mousePos.y(), m_screenshot.height());


    return QRect(
                xPos - (m_magnifierSize.width() / zoomFactor) / 2,
                yPos - (m_magnifierSize.height() / zoomFactor) / 2,
                m_magnifierSize.width() / zoomFactor,
                m_magnifierSize.height() / zoomFactor);
}

const QRect EyeDropperScreenWidget::labelRect(QFont font, QString text)
{
    QFontMetrics fm(font);
    QRect labelRect = fm.boundingRect(text).adjusted(0, 0, 16, 4);

    labelRect.translate(
                magnifierRect().x() + (magnifierRect().width() - labelRect.width()) / 2,
                magnifierRect().bottom() - labelRect.height() - 8
                );

    return labelRect;
}
