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
    colorFillPicker->setColorButton(ui->buttonFill);

    // Mask Picker
    colorMaskPicker = new ColorPicker(ColorPickerConfig::FillMask);
    colorMaskPicker->setColorButton(ui->buttonMask);


//    ui->layoutFillButtons->setVisible(false);

}

void BlockFill::connectSlots()
{

    connect(colorFillPicker, &ColorPicker::colorChanged, this, &BlockFill::setFillColor);
    connect(colorMaskPicker, &ColorPicker::colorChanged, this, &BlockFill::setMaskColor);

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

//    ui->layoutFillButtons->setVisible(false);
}

void BlockFill::setFillGradient()
{

    // TODO: handle selected document elements

//    ui->buttonFillproperty->setVisible(false);
//    ui->layoutFillButtons->setVisible(true);
}

void BlockFill::setFillPattern()
{
    // TODO: handle selected document elements


//    ui->buttonFillproperty->setVisible(true);
//    ui->layoutFillButtons->setVisible(true);
}

void BlockFill::setFillImage()
{
    // TODO: handle selected document elements

//    ui->layoutFillButtons->setVisible(false);
}

void BlockFill::setMaskColor(ScColor color)
{
    // TODO: handle selected document elements

    //ui->buttonMask->setColor(color);

    //ui->layoutMaskOpacity->setVisible(true);

}

void BlockFill::setMaskGradient()
{
    // TODO: handle selected document elements

    //ui->layoutMaskOpacity->setVisible(false);

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
