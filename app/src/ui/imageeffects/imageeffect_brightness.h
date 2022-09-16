#ifndef IMAGEEFFECT_BRIGHTNESS_H
#define IMAGEEFFECT_BRIGHTNESS_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectBrightness;
}

class ImageEffectBrightness : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectBrightness(QWidget *parent = nullptr);
    ~ImageEffectBrightness();

private:
    Ui::ImageEffectBrightness *ui;
};

#endif // IMAGEEFFECT_BRIGHTNESS_H
