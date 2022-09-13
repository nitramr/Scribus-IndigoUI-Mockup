#ifndef BLOCK_TEXT_FONT_H
#define BLOCK_TEXT_FONT_H

#include "block_text_outline.h"
#include <QToolButton>
#include "sccolor.h"
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
    ColorPicker *colorOutlinePicker;

    BlockTextOutline * blockOutline;

    void setup();
    void connectSlots();
    void addMenu(QToolButton *button, QWidget *menuPanel);

public slots:
    void setTextColor(ScColor color);
    void setBackgroundColor(ScColor color);
};

#endif // BLOCK_TEXT_FONT_H
