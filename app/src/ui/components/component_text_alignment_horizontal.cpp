#include "component_text_alignment_horizontal.h"
#include "ui_component_text_alignment_horizontal.h"

#include <QButtonGroup>
#include "icon_manager.h"
#include "enums.h"

ComponentTextAlignmentHorizontal::ComponentTextAlignmentHorizontal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentTextAlignmentHorizontal)
{
    ui->setupUi(this);
    setup();
    connectSlots();
}

ComponentTextAlignmentHorizontal::~ComponentTextAlignmentHorizontal()
{
    delete ui;
}

void ComponentTextAlignmentHorizontal::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Direction
    ui->buttonLTR->setIcon(iconManager.icon("text-direction-ltr"));
    ui->buttonRTL->setIcon(iconManager.icon("text-direction-rtl"));

    direction = new QButtonGroup();
    direction->addButton(ui->buttonLTR, 0);
    direction->addButton(ui->buttonRTL, 1);
    direction->setExclusive(true);

    // Horizontal Alignment
    ui->buttonAlignCenter->setIcon(iconManager.icon("text-align-center"));
    ui->buttonAlignForcedJustified->setIcon(iconManager.icon("text-align-forcedjustified"));
    ui->buttonAlignJustified->setIcon(iconManager.icon("text-align-justified-ltr"));
    ui->buttonAlignLeft->setIcon(iconManager.icon("text-align-left"));
    ui->buttonAlignRight->setIcon(iconManager.icon("text-align-right"));

    QButtonGroup *hAlignment = new QButtonGroup();
    hAlignment->addButton(ui->buttonAlignLeft);
    hAlignment->addButton(ui->buttonAlignCenter);
    hAlignment->addButton(ui->buttonAlignRight);
    hAlignment->addButton(ui->buttonAlignJustified);
    hAlignment->addButton(ui->buttonAlignForcedJustified);
    hAlignment->setExclusive(true);


}

void ComponentTextAlignmentHorizontal::connectSlots()
{
    connect(direction, &QButtonGroup::idToggled, this, &ComponentTextAlignmentHorizontal::changedTextDirection);
}

void ComponentTextAlignmentHorizontal::changedTextDirection(int id, bool checked)
{
    IconManager &iconManager = IconManager::instance();

    // LTR
    if(id == 0 && checked){
        if(ui->buttonAlignRight->isChecked()) ui->buttonAlignLeft->setChecked(true);
        ui->buttonAlignJustified->setIcon(iconManager.icon("text-align-justified-ltr"));

    }
    // RTL
    else if(id == 1 && checked){
        if(ui->buttonAlignLeft->isChecked()) ui->buttonAlignRight->setChecked(true);
        ui->buttonAlignJustified->setIcon(iconManager.icon("text-align-justified-rtl"));
    }
}
