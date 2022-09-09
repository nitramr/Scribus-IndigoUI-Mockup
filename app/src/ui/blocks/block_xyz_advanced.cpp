#include "block_xyz_advanced.h"
#include "ui_block_xyz_advanced.h"

#include <icon_manager.h>

BlockXYZAdvanced::BlockXYZAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockXYZAdvanced)
{
    ui->setupUi(this);    

    connectSlots();

}

BlockXYZAdvanced::~BlockXYZAdvanced()
{
    delete ui;
}

void BlockXYZAdvanced::connectSlots()
{
    connect(ui->cbExport, &QCheckBox::clicked, this, &BlockXYZAdvanced::exportObject);
    connect(ui->textName, &QLineEdit::textChanged, this, &BlockXYZAdvanced::changedName);
}
