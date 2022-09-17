#ifndef IMAGEEFFECT_POSTERIZE_H
#define IMAGEEFFECT_POSTERIZE_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectPosterize;
}

class ImageEffectPosterize : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectPosterize(QWidget *parent = nullptr);
    ~ImageEffectPosterize();

private:
    Ui::ImageEffectPosterize *ui;
};

#endif // IMAGEEFFECT_POSTERIZE_H
