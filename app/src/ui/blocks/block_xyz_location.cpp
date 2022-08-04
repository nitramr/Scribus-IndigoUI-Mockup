#include "block_xyz_location.h"
#include "ui_block_xyz_location.h"

#include <QComboBox>
#include <iconmanager.h>


/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockXYZLocation::BlockXYZLocation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockXYZLocation)
{
    ui->setupUi(this);


    setup();
    connectSlots();
}

BlockXYZLocation::~BlockXYZLocation()
{
    delete ui;
}

void BlockXYZLocation::setup()
{
    IconManager &iconManager = IconManager::instance();

    ui->buttonLinkSize->setIcon(iconManager.icon("link-off"));
    ui->buttonLockFrame->setIcon(iconManager.icon("lock-open"));
    ui->buttonLockSize->setIcon(iconManager.icon("lock-open"));
}

void BlockXYZLocation::connectSlots()
{
    // Buttons
    connect(ui->buttonLockFrame, &QToolButton::toggled, this, &BlockXYZLocation::lockFrame);
    connect(ui->buttonLockSize, &QToolButton::toggled, this, &BlockXYZLocation::lockSize);
    connect(ui->buttonLinkSize, &QToolButton::toggled, this, &BlockXYZLocation::linkSize);


}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void BlockXYZLocation::lockFrame(bool state)
{
    if(state){
        ui->buttonLockFrame->setIcon(IconManager::instance().icon("lock"));
        ui->numHeight->setReadOnly(state);
        ui->numWidth->setReadOnly(state);
    }else{
        ui->buttonLockFrame->setIcon(IconManager::instance().icon("lock-open"));
        if(!ui->buttonLockSize->isChecked()){
            ui->numHeight->setReadOnly(state);
            ui->numWidth->setReadOnly(state);
        }
    }

    ui->numXPos->setReadOnly(state);
    ui->numYPos->setReadOnly(state);

    emit signalLockFrame(state);
}

void BlockXYZLocation::lockSize(bool state)
{
    if(state){
        ui->buttonLockSize->setIcon(IconManager::instance().icon("lock"));
        ui->numHeight->setReadOnly(state);
        ui->numWidth->setReadOnly(state);

    }else{
        ui->buttonLockSize->setIcon(IconManager::instance().icon("lock-open"));
        if(!ui->buttonLockFrame->isChecked()){
            ui->numHeight->setReadOnly(state);
            ui->numWidth->setReadOnly(state);
        }
    }

    emit signalLockSize(state);
}

void BlockXYZLocation::linkSize(bool state)
{
    if(state){
        ui->buttonLinkSize->setIcon(IconManager::instance().icon("link"));
    }else{
        ui->buttonLinkSize->setIcon(IconManager::instance().icon("link-off"));
    }

    emit signalLinkSize(state);
}

void BlockXYZLocation::rotate(double angle)
{
    ui->basePoint->setAngle(angle);
}





