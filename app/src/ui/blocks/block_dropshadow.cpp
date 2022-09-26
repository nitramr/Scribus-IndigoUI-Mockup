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

    // Color Buttons
    ui->buttonColor->setConfiguration(ColorPickerConfig::Shadow);
}

void BlockDropShadow::connectSlots()
{
    connect(ui->buttonColor, &ColorButton::colorChanged, this, &BlockDropShadow::setFillColor);
}

void BlockDropShadow::setFillColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonColor->setColor(color);
}
