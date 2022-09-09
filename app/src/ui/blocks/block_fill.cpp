#include "block_fill.h"
#include "ui_block_fill.h"

#include "colorpicker.h"
#include "menu_popup.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockFill::BlockFill(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockFill)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockFill::~BlockFill()
{
    delete ui;
}


void BlockFill::setup()
{


    // Fill Picker
    colorFillPicker = new ColorPicker(ColorPickerConfig::Fill);
    ui->buttonFill->setContextWidget(colorFillPicker);

    // Mask Picker
    colorMaskPicker = new ColorPicker(ColorPickerConfig::FillMask);
    ui->buttonMask->setContextWidget(colorMaskPicker);

}

void BlockFill::connectSlots()
{

    connect(colorFillPicker, &ColorPicker::colorChanged, this, &BlockFill::setFillColor);
    connect(colorFillPicker, &ColorPicker::gradientChanged, this, &BlockFill::setFillGradient);
    connect(colorMaskPicker, &ColorPicker::colorChanged, this, &BlockFill::setMaskColor);
    connect(colorMaskPicker, &ColorPicker::gradientChanged, this, &BlockFill::setMaskGradient);

    connect(ui->buttonFill, &QToolButton::pressed, this, &BlockFill::openFillPicker);
    connect(ui->buttonMask, &QToolButton::pressed, this, &BlockFill::openMaskPicker);


}


/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void BlockFill::setFillColor(ScColor color)
{

    // TODO: handle selected document elements

    ui->buttonFill->setColor(color);
}

void BlockFill::setFillGradient(VGradient gradient)
{

    // TODO: handle selected document elements

    ui->buttonFill->setGradient(gradient);
}

void BlockFill::setFillPattern()
{
    // TODO: handle selected document elements

}

void BlockFill::setFillImage()
{
    // TODO: handle selected document elements

}

void BlockFill::setMaskColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonMask->setColor(color);

}

void BlockFill::setMaskGradient(VGradient gradient)
{
    // TODO: handle selected document elements

    ui->buttonMask->setGradient(gradient);

}

void BlockFill::setMaskPattern()
{
    // TODO: handle selected document elements
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockFill::openFillPicker()
{



}

void BlockFill::openMaskPicker()
{

}
