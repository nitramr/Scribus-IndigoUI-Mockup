#include <QPainter>
#include <QStyleOption>

#include "formwidget.h"

FormWidget::FormWidget(QWidget *parent)
    : QWidget(parent)
{

    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    m_label = "Label";
    m_position = Bottom;
    m_font = this->font();
    m_space = 4;
    m_pixmap = QPixmap();
    m_pixmapSize = QSize(16,16);
    m_preserveLabelSpace = false;

    setSizePolicy(policy);
    calculateFrame();

}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

QSize FormWidget::minimumSizeHint() const
{
    int w = 0, h = 0;
    labelSize(w,h);

    return QSize(w, h).expandedTo(QWidget::minimumSizeHint());
}

/* ********************************************************************************* *
 *
 * Helper
 *
 * ********************************************************************************* */

void FormWidget::calculateFrame()
{

    int w, h;
    labelSize(w,h);

    switch(m_position){
    case Left:
        setContentsMargins(w,0,0,0);
        break;
    case Right:
        setContentsMargins(0,0,w,0);
        break;
    case Top:
        setContentsMargins(0,h,0,0);
        break;
    case Bottom:
        setContentsMargins(0,0,0,h);
        break;
    }

    update();
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void FormWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QStyle *style = QWidget::style();
    QStyleOption opt;
    opt.initFrom(this);
    int align = QStyle::visualAlignment(this->layoutDirection(), Qt::AlignCenter);

    QPen pen(QPalette::Text);
    painter.setPen(pen);
    painter.setFont(m_font);

    QRect r = rect();
    QPixmap pix = m_pixmap;
    if(hasPixmap()) pix = pix.scaled(m_pixmapSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (!isEnabled())
        pix = style->generatedIconPixmap(QIcon::Disabled, pix, &opt);

    switch(m_position){
    case Left:
        if(hasPixmap()){
            r= QRect (0, (height() - m_pixmap.height()) / 2, m_pixmap.width(), m_pixmap.height());
            style->drawItemPixmap(&painter, r, align, pix);

        }else{
            style->drawItemText(&painter, r, Qt::AlignLeft|Qt::AlignVCenter, opt.palette, isEnabled(), m_label, foregroundRole());
        }

        break;
    case Right:

        if(hasPixmap()){
            r= QRect (width() - m_pixmap.width(), (height() - m_pixmap.height()) / 2, m_pixmap.width(), m_pixmap.height());
            style->drawItemPixmap(&painter, r, align, pix);

        }else{
            style->drawItemText(&painter, r, Qt::AlignRight|Qt::AlignVCenter, opt.palette, isEnabled(), m_label, foregroundRole());
        }

        break;
    case Top:

        if(hasPixmap()){
            r= QRect ((width() - m_pixmap.width()) / 2, 0, m_pixmap.width(), m_pixmap.height());
            style->drawItemPixmap(&painter, r, align, pix);

        }else{
            style->drawItemText(&painter, r, Qt::AlignHCenter | Qt::AlignTop, opt.palette, isEnabled(), m_label, foregroundRole());
        }

        break;
    case Bottom:

        if(hasPixmap()){
            r= QRect ((width() - m_pixmap.width()) / 2, height() - m_pixmap.height(), m_pixmap.width(), m_pixmap.height());
            style->drawItemPixmap(&painter, r, align, pix);

        }else{
            style->drawItemText(&painter, r, Qt::AlignHCenter | Qt::AlignBottom, opt.palette, isEnabled(), m_label, foregroundRole());
        }

        break;
    }

   // painter.drawRect(rect().adjusted(0,0,-1,-1));

}



/* ********************************************************************************* *
 *
 * Properties
 *
 * ********************************************************************************* */


void FormWidget::labelSize(int &w, int &h) const
{   
    if(hasPixmap()){
        w = m_pixmapSize.width() + m_space*2;
        h = m_pixmapSize.height() + m_space*2;
    }else{

        if(m_label.isEmpty() && m_preserveLabelSpace == false){
            w = 0;
            h = 0;
        }else{
             QFontMetrics metrics(m_font);
            w = metrics.horizontalAdvance(m_label) + metrics.horizontalAdvance(QLatin1Char(' ')) + m_space;
            h = metrics.height() + m_space;
        }

    }
}


void FormWidget::setLabel(const QString &text)
{
    m_label = text;
    calculateFrame();
}

QString FormWidget::label()
{
    return m_label;
}

void FormWidget::setPreserveLabelSpace(bool preserveSpace)
{
    m_preserveLabelSpace = preserveSpace;
    calculateFrame();
}

bool FormWidget::preserveLabelSpace()
{
    return m_preserveLabelSpace;
}

void FormWidget::setDirection(LabelPosition direction)
{
    m_position = direction;
    calculateFrame();
}

FormWidget::LabelPosition FormWidget::direction()
{
    return m_position;
}

void FormWidget::setFont(QFont font)
{
    m_font = font;
    calculateFrame();
}

QFont FormWidget::font()
{
    return m_font;
}

void FormWidget::setSpace(int space)
{
    m_space = space;
    calculateFrame();
}

int FormWidget::space()
{
    return m_space;
}

void FormWidget::setPixmap(QPixmap icon)
{
    m_pixmap = icon;
    calculateFrame();

}

QPixmap FormWidget::pixmap()
{
    return m_pixmap;
}

void FormWidget::setPixmapSize(QSize size)
{
    m_pixmapSize = size;
    calculateFrame();
}

QSize FormWidget::pixmapSize()
{
    return m_pixmapSize;
}

bool FormWidget::hasPixmap() const
{
    return !m_pixmap.isNull();
}
