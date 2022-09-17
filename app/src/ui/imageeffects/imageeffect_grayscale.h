#ifndef IMAGEEFFECT_GRAYSCALE_H
#define IMAGEEFFECT_GRAYSCALE_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectGrayscale;
}

class ImageEffectGrayscale : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectGrayscale(QWidget *parent = nullptr);
    ~ImageEffectGrayscale();

private:
    Ui::ImageEffectGrayscale *ui;
};

#endif // IMAGEEFFECT_GRAYSCALE_H
