#include "imageeffect_sharpen.h"
#include "ui_imageeffect_sharpen.h"

ImageEffectSharpen::ImageEffectSharpen(QWidget *parent) :
    ImageEffectItem(tr("Sharpen"),true, parent),
    ui(new Ui::ImageEffectSharpen)
{
    ui->setupUi(this);
}

ImageEffectSharpen::~ImageEffectSharpen()
{
    delete ui;
}
