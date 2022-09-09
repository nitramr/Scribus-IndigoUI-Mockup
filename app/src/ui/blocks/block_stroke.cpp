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


    // Fill Picker
    colorFillPicker = new ColorPicker(ColorPickerConfig::Stroke);
    ui->buttonFill->setContextWidget(colorFillPicker);

}

void BlockStroke::connectSlots()
{
    connect(colorFillPicker, &ColorPicker::colorChanged, this, &BlockStroke::setFillColor);
    connect(colorFillPicker, &ColorPicker::gradientChanged, this, &BlockStroke::setFillGradient);

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

void BlockStroke::openFillPicker()
{

}
