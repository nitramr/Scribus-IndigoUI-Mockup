#ifndef IMAGEEFFECT_BLUR_H
#define IMAGEEFFECT_BLUR_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectBlur;
}

class ImageEffectBlur : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectBlur(QWidget *parent = nullptr);
    ~ImageEffectBlur();

private:
    Ui::ImageEffectBlur *ui;
};

#endif // IMAGEEFFECT_BLUR_H
