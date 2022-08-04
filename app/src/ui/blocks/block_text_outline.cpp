#include "block_text_outline.h"
#include "colorpicker.h"
#include "ui_block_text_outline.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockTextOutline::BlockTextOutline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextOutline)
{
    ui->setupUi(this);

    setup();
}

BlockTextOutline::~BlockTextOutline()
{
    delete ui;
}

void BlockTextOutline::setup()
{
    // Color Picker
    colorOutlinePicker = new ColorPicker(ColorPickerConfig::Text);
    colorOutlinePicker->setColorButton(ui->buttonOutlineColor);
}
