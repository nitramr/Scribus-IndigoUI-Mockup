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


    this->addFormWidget("start", tr("Start Angle:"), QList<QWidget*>() << numberStartAngle );
    this->addFormWidget("end", tr("End Angle:"), QList<QWidget*>() << numberEndAngle );
    this->addFormWidget("factor", tr("Factor"), QList<QWidget*>() << numberFactor );

}
