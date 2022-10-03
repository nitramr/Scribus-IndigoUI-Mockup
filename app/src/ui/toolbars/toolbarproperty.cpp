#include "toolbarproperty.h"
#include "form_widget/form_widget.h"

#include <QDoubleSpinBox>
#include <QHBoxLayout>

ToolBarProperty::ToolBarProperty(QWidget * parent) : QToolBar(parent)
{

    m_icon = new QLabel();

    this->setMovable(false);
    this->setFloatable(false);
    this->setOrientation(Qt::Horizontal);
    this->setAllowedAreas(Qt::TopToolBarArea);
    this->setFixedHeight( 60 );

    this->addSpacing(8);
    this->addWidget(m_icon);
    this->addSpacing(8);

}

void ToolBarProperty::setIcon(QPixmap icon)
{
    m_icon->setPixmap(icon);
}

void ToolBarProperty::addSpacing(int spacing)
{
    QLabel *label = new QLabel(this);
    addWidget(label);
    label->setFixedWidth(spacing);
}

int ToolBarProperty::calculateMinHeight()
{
    QFont fontLabel = this->font();
    fontLabel.setPointSize(8);

    QDoubleSpinBox *spinBox = new QDoubleSpinBox();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->setContentsMargins(0,0,0,0);

    FormWidget * form = new FormWidget();
    form->setLabel(tr("Start Angle"));
    form->setLayout(layout);
    form->setFont(fontLabel);
    form->adjustSize();

    return form->height();
}
