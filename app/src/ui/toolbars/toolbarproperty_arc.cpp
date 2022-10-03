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

    QHBoxLayout *layoutStartAngle = new QHBoxLayout;
    layoutStartAngle->addWidget(numberStartAngle);
    layoutStartAngle->setContentsMargins(0,0,0,0);

    FormWidget * formStartAngle = new FormWidget();
    formStartAngle->setLabel(tr("Start Angle"));
    formStartAngle->setLayout(layoutStartAngle);
    formStartAngle->setFont(fontLabel);

    this->addWidget(formStartAngle);
    this->addSpacing(4);

    // End Angle
    numberEndAngle = new QDoubleSpinBox();
    numberEndAngle->setMinimum(min);
    numberEndAngle->setMaximum(max);
    numberEndAngle->setSuffix(suffix);

    QHBoxLayout *layoutEndAngle = new QHBoxLayout;
    layoutEndAngle->addWidget(numberEndAngle);
    layoutEndAngle->setContentsMargins(0,0,0,0);

    FormWidget * formEndAngle = new FormWidget();
    formEndAngle->setLabel(tr("End Angle"));
    formEndAngle->setLayout(layoutEndAngle);
    formEndAngle->setFont(fontLabel);

    this->addWidget(formEndAngle);

    qDebug() << "Toolbar height" << this->height();

}


