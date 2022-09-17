#include "imageeffect_grayscale.h"
#include "ui_imageeffect_grayscale.h"

ImageEffectGrayscale::ImageEffectGrayscale(QWidget *parent) :
    ImageEffectItem(tr("Grayscale"),true, parent),
    ui(new Ui::ImageEffectGrayscale)
{
    ui->setupUi(this);
}

ImageEffectGrayscale::~ImageEffectGrayscale()
{
    delete ui;
}
