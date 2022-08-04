#include "block_fill_advanced.h"
#include "ui_block_fill_advanced.h"

BlockFillAdvanced::BlockFillAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockFillAdvanced)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockFillAdvanced::~BlockFillAdvanced()
{
    delete ui;
}

void BlockFillAdvanced::setup()
{
    ui->comboFillRule->addItem("Evenodd");
    ui->comboFillRule->addItem("Nonzero");

    ui->comboOverprinting->addItem("Knockout");
    ui->comboOverprinting->addItem("Overprint");

}

void BlockFillAdvanced::connectSlots()
{

}
