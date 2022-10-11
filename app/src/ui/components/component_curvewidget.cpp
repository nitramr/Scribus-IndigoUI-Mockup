#include "component_curvewidget.h"
#include "icon_manager.h"
#include "ui_component_curvewidget.h"

ComponentCurveWidget::ComponentCurveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentCurveWidget)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

ComponentCurveWidget::~ComponentCurveWidget()
{
    delete ui;
}

void ComponentCurveWidget::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->buttonInvert->setIcon(iconManager.icon("invert"));
    ui->buttonReset->setIcon(iconManager.icon("reset"));
    ui->buttonLoad->setIcon(iconManager.icon("load"));
    ui->buttonSave->setIcon(iconManager.icon("save"));
    ui->buttonToggleBezier->setIcon(iconManager.icon("bezier-curve"));


}

void ComponentCurveWidget::connectSlots()
{
    connect( ui->buttonToggleBezier, &QToolButton::clicked, this, &ComponentCurveWidget::toggleCurveBezier );

}

void ComponentCurveWidget::toggleCurveBezier()
{
    IconManager &iconManager = IconManager::instance();

    if(ui->curveEditWidget->isLinear()){
        ui->curveEditWidget->setLinear(false);
        ui->buttonToggleBezier->setIcon(iconManager.icon("bezier-curve"));

    }else{
        ui->curveEditWidget->setLinear(true);
        ui->buttonToggleBezier->setIcon(iconManager.icon("bezier-line"));
    }
}
