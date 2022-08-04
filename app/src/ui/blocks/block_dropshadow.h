#ifndef BLOCK_DROPSHADOW_H
#define BLOCK_DROPSHADOW_H

#include <QWidget>

class ColorPicker;

namespace Ui {
class BlockDropShadow;
}

class BlockDropShadow : public QWidget
{
    Q_OBJECT

public:
    explicit BlockDropShadow(QWidget *parent = nullptr);
    ~BlockDropShadow();

private:
    Ui::BlockDropShadow *ui;

    ColorPicker *colorFillPicker;

    void setup();
    void connectSlots();
};

#endif // BLOCK_DROPSHADOW_H
