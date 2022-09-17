#include "imageeffect_contrast.h"
#include "ui_imageeffect_contrast.h"

ImageEffectContrast::ImageEffectContrast(QWidget *parent) :
    ImageEffectItem(tr("Contrast"),true, parent),
    ui(new Ui::ImageEffectContrast)
{
    ui->setupUi(this);
}

ImageEffectContrast::~ImageEffectContrast()
{
    delete ui;
}
