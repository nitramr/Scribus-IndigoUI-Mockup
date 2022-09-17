#include "imageeffect_brightness.h"
#include "ui_imageeffect_brightness.h"

ImageEffectBrightness::ImageEffectBrightness(QWidget *parent) :
    ImageEffectItem(tr("Brightness"),true, parent),
    ui(new Ui::ImageEffectBrightness)
{
    ui->setupUi(this);
}

ImageEffectBrightness::~ImageEffectBrightness()
{
    delete ui;
}
