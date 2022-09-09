#ifndef BLOCK_FILL_H
#define BLOCK_FILL_H

#include "vgradient.h"
#include <QWidget>
#include <sccolor.h>

class ColorPicker;

namespace Ui {
class BlockFill;
}

class BlockFill : public QWidget
{
    Q_OBJECT

public:
    explicit BlockFill(QWidget *parent = nullptr);
    ~BlockFill();

public slots:
    void setFillColor(ScColor color);
    void setFillGradient(VGradient gradient);
    void setFillPattern();
    void setFillImage();

    void setMaskColor(ScColor color);
    void setMaskGradient(VGradient gradient);
    void setMaskPattern();

private slots:
    void openFillPicker();
    void openMaskPicker();

private:
    Ui::BlockFill *ui;

    ColorPicker *colorFillPicker;
    ColorPicker *colorMaskPicker;

    void setup();
    void connectSlots();


};

#endif // BLOCK_FILL_H
