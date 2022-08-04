#include "block_paragraph_advanced.h"
#include "ui_block_paragraph_advanced.h"

BlockParagraphAdvanced::BlockParagraphAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockParagraphAdvanced)
{
    ui->setupUi(this);
}

BlockParagraphAdvanced::~BlockParagraphAdvanced()
{
    delete ui;
}
