#include "headline_widget.h"
#include <QVBoxLayout>
#include <QFrame>

HeadlineWidget::HeadlineWidget(const QString text, FontSize fontSize, QWidget *parent)
    : QWidget{parent}
{

    m_label = new QLabel();
    setText(text);
    setFontSize(fontSize);

    m_line = new QFrame();
    m_line->setLineWidth(1);
    m_line->setFrameShape(QFrame::HLine);
    m_line->setFrameShadow(QFrame::Sunken);
    m_line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    QVBoxLayout *layoutHeader = new QVBoxLayout;
    layoutHeader->setContentsMargins(0 ,8, 0, 4);
    layoutHeader->setSpacing(4);
    layoutHeader->addWidget(m_label);
    layoutHeader->addWidget(m_line);

    this->setLayout(layoutHeader);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

}

HeadlineWidget::HeadlineWidget(QWidget *parent) :HeadlineWidget(QString(), FontSize::H3, parent){}

const QString HeadlineWidget::text()
{
    return m_label->text();
}

void HeadlineWidget::setText(const QString text)
{
    m_label->setText(text);
}

HeadlineWidget::FontSize HeadlineWidget::fontSize()
{
    return m_fontSize;
}

void HeadlineWidget::setFontSize(FontSize size)
{
    m_fontSize = size;
    double factor = 1;
    bool bold = true;
    QFont m_font = font();

    switch(m_fontSize){
    default:
    case FontSize::Normal:
        factor = 1;
        bold = false;
        break;
    case FontSize::H1:
        factor = 1.5;
        bold = false;
        break;
    case FontSize::H2:
        factor = 1.25;
        bold = true;
        break;
    case FontSize::H3:
        factor = 1;
        bold = true;
        break;
    }

    m_font.setBold(bold);
    m_font.setPointSizeF(m_font.pointSizeF() * factor);
    m_label->setFont(m_font);
}

bool HeadlineWidget::lineVisible()
{
    return m_line->isVisible();
}

void HeadlineWidget::setLineVisible(bool visible)
{
    m_line->setVisible(visible);

}
