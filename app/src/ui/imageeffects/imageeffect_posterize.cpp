#include "imageeffect_posterize.h"
#include "ui_imageeffect_posterize.h"

ImageEffectPosterize::ImageEffectPosterize(QWidget *parent) :
    ImageEffectItem(tr("Posterize"),true, parent),
    ui(new Ui::ImageEffectPosterize)
{
    ui->setupUi(this);
}

ImageEffectPosterize::~ImageEffectPosterize()
{
    delete ui;
}
