#include "block_xyz_transformation.h"
#include "ui_block_xyz_transformation.h"

#include "iconmanager.h"


/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockXYZTransformation::BlockXYZTransformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockXYZTransformation)
{
    ui->setupUi(this);

    ui->buttonFlipHorizontal->setIcon(IconManager::instance().icon("flip-horizontal"));
    ui->buttonFlipVertical->setIcon(IconManager::instance().icon("flip-vertical"));
    ui->buttonMoveTop->setIcon(IconManager::instance().icon("layer-top"));
    ui->buttonMoveUp->setIcon(IconManager::instance().icon("layer-up"));
    ui->buttonMoveDown->setIcon(IconManager::instance().icon("layer-down"));
    ui->buttonMoveBottom->setIcon(IconManager::instance().icon("layer-bottom"));

    connectSlots();
}

BlockXYZTransformation::~BlockXYZTransformation()
{
    delete ui;
}

void BlockXYZTransformation::connectSlots()
{
    // Buttons
    connect(ui->buttonFlipHorizontal, &QToolButton::toggled, this, &BlockXYZTransformation::flipHorizontal);
    connect(ui->buttonFlipVertical, &QToolButton::toggled, this, &BlockXYZTransformation::flipVertical);

    // Numeric Inputs
    connect(ui->numRotation, &QDoubleSpinBox::valueChanged, this, &BlockXYZTransformation::signalRotate);

}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void BlockXYZTransformation::flipVertical(bool state)
{

}

void BlockXYZTransformation::flipHorizontal(bool state)
{

}

void BlockXYZTransformation::lockFrame(bool state)
{
    ui->numRotation->setReadOnly(state);
    ui->formLevel->setDisabled(state);
}


