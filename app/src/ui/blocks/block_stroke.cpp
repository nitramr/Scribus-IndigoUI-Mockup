#include "block_stroke.h"
#include "ui_block_stroke.h"

#include "colorpicker.h"
#include "iconmanager.h"

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


    // Fill Picker
    colorFillPicker = new ColorPicker(ColorPickerConfig::Stroke);
    colorFillPicker->setColorButton(ui->buttonFill);

}

void BlockStroke::connectSlots()
{
    connect(colorFillPicker, &ColorPicker::colorChanged, this, &BlockStroke::setFillColor);

    connect(ui->buttonFill, &QToolButton::pressed, this, &BlockStroke::openFillPicker);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void BlockStroke::setFillColor(ScColor color)
{
    // TODO: handle selected document elements
}

void BlockStroke::setFillGradient()
{
    // TODO: handle selected document elements
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockStroke::openFillPicker()
{

}
