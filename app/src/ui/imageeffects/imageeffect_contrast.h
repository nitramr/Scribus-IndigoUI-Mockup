#ifndef IMAGEEFFECT_CONTRAST_H
#define IMAGEEFFECT_CONTRAST_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectContrast;
}

class ImageEffectContrast : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectContrast(QWidget *parent = nullptr);
    ~ImageEffectContrast();

private:
    Ui::ImageEffectContrast *ui;
};

#endif // IMAGEEFFECT_CONTRAST_H
