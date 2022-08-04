#include "block_character_advanced.h"
#include "ui_block_character_advanced.h"

BlockCharacterAdvanced::BlockCharacterAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockCharacterAdvanced)
{
    ui->setupUi(this);
}

BlockCharacterAdvanced::~BlockCharacterAdvanced()
{
    delete ui;
}
