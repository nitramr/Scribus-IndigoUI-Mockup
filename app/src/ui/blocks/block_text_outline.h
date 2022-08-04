#ifndef BLOCK_TEXT_OUTLINE_H
#define BLOCK_TEXT_OUTLINE_H

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

    ColorPicker * colorOutlinePicker;

    void setup();
};

#endif // BLOCK_TEXT_OUTLINE_H
