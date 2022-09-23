#include "imageeffect_curves.h"
#include "ui_imageeffect_curves.h"

ImageEffectCurves::ImageEffectCurves(QWidget *parent) :
    ImageEffectItem(tr("Curves"),true, parent),
    ui(new Ui::ImageEffectCurves)
{
    ui->setupUi(this);
}

ImageEffectCurves::~ImageEffectCurves()
{
    delete ui;
}
