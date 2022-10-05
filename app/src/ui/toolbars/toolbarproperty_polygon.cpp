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
    numberFactor->setEnabled(false);

    numberInnerRotation = new QSpinBox();
    numberInnerRotation->setSuffix("°");
    numberInnerRotation->setEnabled(false);

    numberInnerCurvation = new QSpinBox();
    numberInnerCurvation->setSuffix("%");
    numberInnerCurvation->setEnabled(false);

    numberOuterCurvation = new QSpinBox();
    numberOuterCurvation->setSuffix("%");
    numberOuterCurvation->setEnabled(false);

    checkboxApplyFactor = new QCheckBox();
    checkboxApplyFactor->setText(tr("Apply Factor"));

    labelCorners = new QLabel(tr("Corners:"));
    labelRotation = new QLabel(tr("Rotation:"));
    labelFactor = new QLabel(tr("Factor:"));
    labelFactor->setEnabled(false);
    labelInnerRotation = new QLabel(tr("Inner Rotation:"));
    labelInnerRotation->setEnabled(false);
    labelInnerCurvation = new QLabel(tr("Inner Curvation:"));
    labelInnerCurvation->setEnabled(false);
    labelOuterCurvation = new QLabel(tr("Outer Curvation:"));
    labelOuterCurvation->setEnabled(false);

    this->addWidget( labelCorners );
    this->addWidget( numberCorners );
    this->addSpacing(4);
    this->addWidget( labelRotation );
    this->addWidget( numberRotation );
    this->addSeparator();
    this->addWidget( checkboxApplyFactor );
    this->addSpacing(4);
    this->addWidget( labelFactor );
    this->addWidget( numberFactor );
    this->addSpacing(4);
    this->addWidget( labelInnerRotation );
    this->addWidget( numberInnerRotation );
    this->addSpacing(4);
    this->addWidget( labelInnerCurvation );
    this->addWidget( numberInnerCurvation );
    this->addSpacing(4);
    this->addWidget( labelOuterCurvation );
    this->addWidget( numberOuterCurvation );


    connect(checkboxApplyFactor, &QCheckBox::clicked, this, &ToolBarPropertyPolygon::enableControls);


}

void ToolBarPropertyPolygon::enableControls(bool enabled)
{

    numberFactor->setEnabled(enabled);
    numberInnerRotation->setEnabled(enabled);
    numberInnerCurvation->setEnabled(enabled);
    numberOuterCurvation->setEnabled(enabled);

    labelFactor->setEnabled(enabled);
    labelInnerRotation->setEnabled(enabled);
    labelInnerCurvation->setEnabled(enabled);
    labelOuterCurvation->setEnabled(enabled);

}
