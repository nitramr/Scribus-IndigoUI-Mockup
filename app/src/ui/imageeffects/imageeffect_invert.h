#ifndef IMAGEEFFECT_INVERT_H
#define IMAGEEFFECT_INVERT_H

#include "imageeffect_item.h"

namespace Ui {
class ImageEffectInvert;
}

class ImageEffectInvert : public ImageEffectItem
{
    Q_OBJECT

public:
    explicit ImageEffectInvert(QWidget *parent = nullptr);
    ~ImageEffectInvert();

private:
    Ui::ImageEffectInvert *ui;
};

#endif // IMAGEEFFECT_INVERT_H
