#include "block_fill.h"
#include "ui_block_fill.h"

#include "colorpicker.h"
#include "popup_menu/popup_menu.h"

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
    // Color Buttons
    ui->buttonMask->setConfiguration(ColorPickerConfig::FillMask);
    ui->buttonFill->setConfiguration(ColorPickerConfig::Fill);

    QButtonGroup * fillRuleGroup = new QButtonGroup();
    fillRuleGroup->addButton(ui->buttonEvenodd);
    fillRuleGroup->addButton(ui->buttonNonezero);

}

void BlockFill::connectSlots()
{

    connect(ui->buttonFill, &ColorButton::colorChanged, this, &BlockFill::setFillColor);
    connect(ui->buttonFill, &ColorButton::gradientChanged, this, &BlockFill::setFillGradient);
    connect(ui->buttonMask, &ColorButton::colorChanged, this, &BlockFill::setMaskColor);
    connect(ui->buttonMask, &ColorButton::gradientChanged, this, &BlockFill::setMaskGradient);

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

