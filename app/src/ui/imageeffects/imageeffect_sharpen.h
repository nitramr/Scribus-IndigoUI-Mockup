#ifndef IMAGEEFFECT_SHARPEN_H
#define IMAGEEFFECT_SHARPEN_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectSharpen;
}

class ImageEffectSharpen : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectSharpen(QWidget *parent = nullptr);
    ~ImageEffectSharpen();

private:
    Ui::ImageEffectSharpen *ui;
};

#endif // IMAGEEFFECT_SHARPEN_H
