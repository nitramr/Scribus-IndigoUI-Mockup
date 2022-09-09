#include "block_distribution.h"
#include "icon_manager.h"
#include "ui_block_distribution.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockDistribution::BlockDistribution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockDistribution)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockDistribution::~BlockDistribution()
{
    delete ui;
}

void BlockDistribution::setup()
{
    IconManager &iconManager = IconManager::instance();

    ui->buttonLeft->setIcon( iconManager.icon("distribute-left") );
    ui->buttonCenter->setIcon( iconManager.icon("distribute-center") );
    ui->buttonRight->setIcon( iconManager.icon("distribute-right") );
    ui->buttonHorizontalSpace->setIcon( iconManager.icon("distribute-item-horizontal") );

    ui->buttonBottom->setIcon( iconManager.icon("distribute-bottom") );
    ui->buttonMiddle->setIcon( iconManager.icon("distribute-middle") );
    ui->buttonTop->setIcon( iconManager.icon("distribute-top") );
    ui->buttonVerticalSpace->setIcon( iconManager.icon("distribute-item-vertical") );

    ui->buttonPageHorizontalSpace->setIcon( iconManager.icon("distribute-page-horizontal") );
    ui->buttonPageVerticalSpace->setIcon( iconManager.icon("distribute-page-vertical") );

    ui->buttonMarginHorizontalSpace->setIcon( iconManager.icon("distribute-margin-horizontal") );
    ui->buttonMarginVerticalSpace->setIcon( iconManager.icon("distribute-margin-vertical") );

//    ui->buttonItemHorizontalSpace->setIcon( iconManager.icon("distribute-item-horizontal-custom") );
//    ui->buttonItemVerticalSpace->setIcon( iconManager.icon("distribute-item-vertical-custom") );

    ui->buttonSwapLeft->setIcon( iconManager.icon("distribute-swap-left") );
    ui->buttonSwapRight->setIcon( iconManager.icon("distribute-swap-right") );


    // Default Values
    ui->numberDistance->setEnabled(false);

}

void BlockDistribution::connectSlots()
{
    connect(ui->checkBoxSpacing, &QCheckBox::clicked, [this](bool isEnabled) {
        ui->numberDistance->setEnabled(isEnabled);
    } );
}

