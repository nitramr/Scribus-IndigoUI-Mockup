#include "toolbarproperty_arc.h"
#include "form_widget/form_widget.h"
#include <QHBoxLayout>
#include "icon_manager.h"

ToolBarPropertyArc::ToolBarPropertyArc(QWidget *parent) : ToolBarProperty(parent)
{

    double min = 0;
    double max = 359;
    QString suffix = "°";
    QFont fontLabel = this->font();
    fontLabel.setPointSize(8);

    setIcon( IconManager::instance().pixmap("tool-arc") );

    // Start Angle
    numberStartAngle = new QDoubleSpinBox();
    numberStartAngle->setMinimum(min);
    numberStartAngle->setMaximum(max);
    numberStartAngle->setSuffix(suffix);

    // End Angle
    numberEndAngle = new QDoubleSpinBox();
    numberEndAngle->setMinimum(min);
    numberEndAngle->setMaximum(max);
    numberEndAngle->setSuffix(suffix);


    this->addFormWidget("start", tr("Start Angle:"), QList<QWidget*>() << numberStartAngle );
    this->addFormWidget("end", tr("End Angle:"), QList<QWidget*>() << numberEndAngle );


}


