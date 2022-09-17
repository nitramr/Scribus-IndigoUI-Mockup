#include "imageeffect_blur.h"
#include "ui_imageeffect_blur.h"

ImageEffectBlur::ImageEffectBlur(QWidget *parent) :
    ImageEffectItem(tr("Blur"),true, parent),
    ui(new Ui::ImageEffectBlur)
{
    ui->setupUi(this);
}

ImageEffectBlur::~ImageEffectBlur()
{
    delete ui;
}
