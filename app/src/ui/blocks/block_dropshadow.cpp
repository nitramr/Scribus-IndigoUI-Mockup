#include "block_dropshadow.h"
#include "colorpicker.h"
#include "ui_block_dropshadow.h"


/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockDropShadow::BlockDropShadow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockDropShadow)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockDropShadow::~BlockDropShadow()
{
    delete ui;
}

void BlockDropShadow::setup()
{

    // Fill Picker
    colorFillPicker = new ColorPicker(ColorPickerConfig::Shadow);
    colorFillPicker->setColorButton(ui->buttonColor);
}

void BlockDropShadow::connectSlots()
{

}
