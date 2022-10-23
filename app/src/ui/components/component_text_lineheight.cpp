#include "component_text_lineheight.h"
#include "ui_component_text_lineheight.h"

#include "enums.h"

ComponentTextLineHeight::ComponentTextLineHeight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentTextLineHeight)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

ComponentTextLineHeight::~ComponentTextLineHeight()
{
    delete ui;
}

void ComponentTextLineHeight::setup()
{

    ui->comboAlignment->addItem(tr("Fixed"), QVariant::fromValue(TextLineSpacing::Fixed));
    ui->comboAlignment->addItem(tr("Automatic"), QVariant::fromValue(TextLineSpacing::Automatic));
    ui->comboAlignment->addItem(tr("Baseline"), QVariant::fromValue(TextLineSpacing::AlignToBaseline));
    ui->comboAlignment->setCurrentIndex(0);

    ui->numberLineHeight->setValue(15.0);
}

void ComponentTextLineHeight::connectSlots()
{
    connect(ui->comboAlignment, &QComboBox::currentIndexChanged, this, &ComponentTextLineHeight::changedLineSpacing);
}

void ComponentTextLineHeight::changedLineSpacing()
{
    TextLineSpacing lineSpacing = static_cast<TextLineSpacing>(ui->comboAlignment->currentData(Qt::UserRole).toInt());

    switch(lineSpacing){
    case TextLineSpacing::Fixed:
        ui->numberLineHeight->setEnabled(true);
        break;
    case TextLineSpacing::Automatic:
    case TextLineSpacing::AlignToBaseline:
        ui->numberLineHeight->setEnabled(false);
        break;
    }
}
