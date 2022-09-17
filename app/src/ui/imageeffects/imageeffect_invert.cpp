#include "imageeffect_invert.h"
#include "ui_imageeffect_invert.h"

ImageEffectInvert::ImageEffectInvert(QWidget *parent) :
    ImageEffectItem(tr("Invert"),true, parent),
    ui(new Ui::ImageEffectInvert)
{
    ui->setupUi(this);
}

ImageEffectInvert::~ImageEffectInvert()
{
    delete ui;
}
