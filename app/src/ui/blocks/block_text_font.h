#ifndef BLOCK_TEXT_FONT_H
#define BLOCK_TEXT_FONT_H

#include <QWidget>

class ColorPicker;

namespace Ui {
class BlockTextFont;
}

class BlockTextFont : public QWidget
{
    Q_OBJECT

public:
    explicit BlockTextFont(QWidget *parent = nullptr);
    ~BlockTextFont();

private:
    Ui::BlockTextFont *ui;

    ColorPicker *colorPicker;
    ColorPicker *colorBackgroundPicker;

    void setup();
};

#endif // BLOCK_TEXT_FONT_H
