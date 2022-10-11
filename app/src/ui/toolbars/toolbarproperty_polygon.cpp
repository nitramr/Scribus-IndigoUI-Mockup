#include "toolbarproperty_polygon.h"
#include "icon_manager.h"

ToolBarPropertyPolygon::ToolBarPropertyPolygon(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-star") );


    numberCorners = new QSpinBox();

    numberRotation = new QSpinBox();
    numberRotation->setSuffix("°");

    numberFactor = new QSpinBox();
    numberFactor->setSuffix("%");

    numberInnerRotation = new QSpinBox();
    numberInnerRotation->setSuffix("°");

    numberInnerCurvation = new QSpinBox();
    numberInnerCurvation->setSuffix("%");

    numberOuterCurvation = new QSpinBox();
    numberOuterCurvation->setSuffix("%");

    checkboxApplyFactor = new QCheckBox();
    checkboxApplyFactor->setText(tr("Apply Factor"));


    this->addFormWidget("corners", tr("Corners:"), QList<QWidget*>() << numberCorners );
    this->addFormWidget("rotation", tr("Rotation:"), QList<QWidget*>() << numberRotation );
    this->addSeparator();
    this->addFormWidget("applyfactor", "", QList<QWidget*>() << checkboxApplyFactor );
    this->addFormWidget("factor", tr("Factor:"), QList<QWidget*>() << numberFactor );
    this->addFormWidget("innerrotation", tr("Inner Rotation:"), QList<QWidget*>() << numberInnerRotation );
    this->addFormWidget("innercurvation", tr("Inner Curvation:"), QList<QWidget*>() << numberInnerCurvation );
    this->addFormWidget("outercurvation", tr("Outer Curvation:"), QList<QWidget*>() << numberOuterCurvation );

    enableControls(false);

    connect(checkboxApplyFactor, &QCheckBox::clicked, this, &ToolBarPropertyPolygon::enableControls);


}

void ToolBarPropertyPolygon::enableControls(bool enabled)
{

    formWidget("factor")->setEnabled(enabled);
    formWidget("innerrotation")->setEnabled(enabled);
    formWidget("innercurvation")->setEnabled(enabled);
    formWidget("outercurvation")->setEnabled(enabled);


}
