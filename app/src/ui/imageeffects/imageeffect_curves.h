#ifndef IMAGEEFFECT_CURVES_H
#define IMAGEEFFECT_CURVES_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectCurves;
}

class ImageEffectCurves : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectCurves(QWidget *parent = nullptr);
    ~ImageEffectCurves();

private:
    Ui::ImageEffectCurves *ui;
};

#endif // IMAGEEFFECT_CURVES_H
