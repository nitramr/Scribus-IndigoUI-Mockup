#include "toolbarproperty_calligraphy.h"
#include "icon_manager.h"

ToolBarPropertyCalligraphy::ToolBarPropertyCalligraphy(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-calligraphy") );

    labelAngle = new QLabel(tr("Angle:"));
    numberAngle = new QDoubleSpinBox();
    numberAngle->setSuffix(tr("°"));
    numberAngle->setMinimum(0);
    numberAngle->setMaximum(180);

    labelWidth = new QLabel(tr("Width:"));
    numberWidth = new QDoubleSpinBox();
    numberWidth->setSuffix(tr("pt"));
    numberWidth->setMinimum(0);
    numberWidth->setMaximum(100);

    this->addWidget(labelAngle);
    this->addWidget(numberAngle);
    this->addSpacing(4);
    this->addWidget(labelWidth);
    this->addWidget(numberWidth);

}
