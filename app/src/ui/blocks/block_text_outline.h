#ifndef BLOCK_TEXT_OUTLINE_H
#define BLOCK_TEXT_OUTLINE_H

#include "sccolor.h"
#include <QWidget>

namespace Ui {
class BlockTextOutline;
}

class ColorPicker;

class BlockTextOutline : public QWidget
{
    Q_OBJECT

public:
    explicit BlockTextOutline(QWidget *parent = nullptr);
    ~BlockTextOutline();

private:
    Ui::BlockTextOutline *ui;

    void setup();
    void connectSlots();

public slots:
    void setOutlineColor(ScColor color);
};

#endif // BLOCK_TEXT_OUTLINE_H
