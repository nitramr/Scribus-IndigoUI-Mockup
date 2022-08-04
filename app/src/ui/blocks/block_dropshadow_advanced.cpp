#include "block_dropshadow_advanced.h"
#include "ui_block_dropshadow_advanced.h"

BlockDropShadowAdvanced::BlockDropShadowAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockDropShadowAdvanced)
{
    ui->setupUi(this);
}

BlockDropShadowAdvanced::~BlockDropShadowAdvanced()
{
    delete ui;
}
