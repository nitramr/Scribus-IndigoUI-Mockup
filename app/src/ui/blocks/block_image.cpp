#include "block_image.h"
#include "ui_block_image.h"
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

BlockImage::BlockImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockImage)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockImage::~BlockImage()
{
    delete ui;
}

void BlockImage::setup()
{

    ui->buttonLink->setIcon(IconManager::instance().icon("link"));

}

void BlockImage::connectSlots()
{
    connect(ui->checkBoxAutoFit, &QCheckBox::toggled, this, &BlockImage::changeAutoFit);
    connect(ui->buttonLink, &QToolButton::toggled, this, &BlockImage::linkInput);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockImage::linkInput(bool state)
{
    if(state){
        ui->buttonLink->setIcon(IconManager::instance().icon("link"));
    }else{
        ui->buttonLink->setIcon(IconManager::instance().icon("link-off"));
    }

    emit signalLinkInput(state);
}

void BlockImage::changeAutoFit(bool doesFit)
{
    ui->layoutDpiX->setEnabled(!doesFit);
    ui->layoutDpiY->setEnabled(!doesFit);
    ui->layoutScaleX->setEnabled(!doesFit);
    ui->layoutScaleY->setEnabled(!doesFit);
//    ui->layoutPositionX->setEnabled(!doesFit);
//    ui->layoutPositionY->setEnabled(!doesFit);

}
