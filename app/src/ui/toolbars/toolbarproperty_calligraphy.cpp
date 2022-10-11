#include "toolbarproperty_calligraphy.h"
#include "icon_manager.h"

ToolBarPropertyCalligraphy::ToolBarPropertyCalligraphy(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-calligraphy") );

    numberAngle = new QDoubleSpinBox();
    numberAngle->setSuffix(tr("°"));
    numberAngle->setMinimum(0);
    numberAngle->setMaximum(180);

    numberWidth = new QDoubleSpinBox();
    numberWidth->setSuffix(tr("pt"));
    numberWidth->setMinimum(0);
    numberWidth->setMaximum(100);

    this->addFormWidget("angle", tr("Angle:"), QList<QWidget*>() << numberAngle );
    this->addFormWidget("width", tr("Width:"), QList<QWidget*>() << numberWidth );

}
