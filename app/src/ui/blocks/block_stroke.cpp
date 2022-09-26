#include "block_stroke.h"
#include "ui_block_stroke.h"

#include "colorpicker.h"
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockStroke::BlockStroke(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockStroke)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockStroke::~BlockStroke()
{
    delete ui;
}


void BlockStroke::setup()
{

    // Color Buttons
    ui->buttonFill->setConfiguration(ColorPickerConfig::Stroke);

}

void BlockStroke::connectSlots()
{
    connect(ui->buttonFill, &ColorButton::colorChanged, this, &BlockStroke::setFillColor);
    connect(ui->buttonFill, &ColorButton::gradientChanged, this, &BlockStroke::setFillGradient);

  }

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void BlockStroke::setFillColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonFill->setColor(color);
}

void BlockStroke::setFillGradient(VGradient gradient)
{
    // TODO: handle selected document elements

    ui->buttonFill->setGradient(gradient);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

