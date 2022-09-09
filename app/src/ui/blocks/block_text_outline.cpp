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
    connectSlots();
}

BlockTextOutline::~BlockTextOutline()
{
    delete ui;
}

void BlockTextOutline::setup()
{
    // Color Picker
    colorOutlinePicker = new ColorPicker(ColorPickerConfig::Text);  
    ui->buttonOutlineColor->setContextWidget(colorOutlinePicker);
}

void BlockTextOutline::connectSlots()
{
    connect(colorOutlinePicker, &ColorPicker::colorChanged, this, &BlockTextOutline::setOutlineColor);
}

void BlockTextOutline::setOutlineColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonOutlineColor->setColor(color);
}

