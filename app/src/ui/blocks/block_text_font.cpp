#include "block_text_font.h"
#include "colorpicker.h"
#include "ui_block_text_font.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockTextFont::BlockTextFont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextFont)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockTextFont::~BlockTextFont()
{
    delete ui;
}

void BlockTextFont::setup()
{

    QStringList weight = QStringList();
    weight.append("100 Thin");
    weight.append("200 Extra Light");
    weight.append("300 Light");
    weight.append("400 Regular");
    weight.append("500 Medium");
    weight.append("600 Semi Bold");
    weight.append("700 Bold");
    weight.append("800 Black");
    weight.append("900 Super");

    ui->comboWeight->addItems(weight);


    QStringList lineAlignment = QStringList();
    lineAlignment.append("Fixed");
    lineAlignment.append("Automatic");
    lineAlignment.append("Baseline");

    ui->comboAlignment->addItems(lineAlignment);


    ui->numberLineHeight->setValue(15.0);
    ui->numberFontSize->setValue(12.0);

    // Color Picker
    colorPicker = new ColorPicker(ColorPickerConfig::Text);
    ui->buttonColor->setContextWidget(colorPicker);

    colorBackgroundPicker = new ColorPicker(ColorPickerConfig::Text);
    ui->buttonColorBackground->setContextWidget(colorBackgroundPicker);

}

void BlockTextFont::connectSlots()
{
    connect(colorPicker, &ColorPicker::colorChanged, this, &BlockTextFont::setTextColor);
    connect(colorBackgroundPicker, &ColorPicker::colorChanged, this, &BlockTextFont::setBackgroundColor);
}

void BlockTextFont::setTextColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonColor->setColor(color);
}

void BlockTextFont::setBackgroundColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonColorBackground->setColor(color);
}
