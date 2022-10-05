#include "toolbarproperty_spiral.h"
#include "icon_manager.h"

ToolBarPropertySpiral::ToolBarPropertySpiral(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-spiral") );


    numberStartAngle = new QDoubleSpinBox();
    numberStartAngle->setSuffix("°");
    numberStartAngle->setDecimals(1);

    numberEndAngle = new QDoubleSpinBox();
    numberEndAngle->setSuffix("°");
    numberEndAngle->setDecimals(1);

    numberFactor = new QSpinBox();
    numberFactor->setSuffix("%");

    labelStartAngle = new QLabel( tr("Start Angle:") );
    labelEndAngle = new QLabel( tr("End Angle:") );
    labelFactor = new QLabel( tr("Factor:") );

    this->addWidget( labelStartAngle );
    this->addWidget(numberStartAngle);
    this->addSpacing(4);
    this->addWidget( labelEndAngle );
    this->addWidget(numberEndAngle);
    this->addSpacing(4);
    this->addWidget( labelFactor );
    this->addWidget(numberFactor);

}
