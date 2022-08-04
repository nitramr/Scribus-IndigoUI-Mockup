#ifndef BLOCK_STROKE_H
#define BLOCK_STROKE_H

#include "sccolor.h"
#include <QWidget>

class ColorPicker;

namespace Ui {
class BlockStroke;
}

class BlockStroke : public QWidget
{
    Q_OBJECT

public:
    explicit BlockStroke(QWidget *parent = nullptr);
    ~BlockStroke();

public slots:
    void setFillColor(ScColor color);
    void setFillGradient();

private slots:
    void openFillPicker();

private:
    Ui::BlockStroke *ui;

    ColorPicker *colorFillPicker;

    void setup();
    void connectSlots();
};

#endif // BLOCK_STROKE_H
