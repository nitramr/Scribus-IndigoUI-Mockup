#ifndef BLOCK_TEXT_ALIGNMENT_H
#define BLOCK_TEXT_ALIGNMENT_H

#include "block_text_outline.h"
#include <QToolButton>
#include <QWidget>

class ColorPicker;

namespace Ui {
class BlockTextAlignment;
}

class BlockTextAlignment : public QWidget
{
    Q_OBJECT

public:
    explicit BlockTextAlignment(QWidget *parent = nullptr);
    ~BlockTextAlignment();

private:
    Ui::BlockTextAlignment *ui;

    ColorPicker *colorOutlinePicker;

    BlockTextOutline * blockOutline;


    void setup();
    void addMenu(QToolButton *button, QWidget *menuPanel);

};

#endif // BLOCK_TEXT_ALIGNMENT_H
