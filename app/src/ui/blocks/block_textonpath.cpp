#include "block_textonpath.h"
#include "enums.h"
#include "ui_block_textonpath.h"


BlockTextOnPath::BlockTextOnPath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextOnPath)
{
    ui->setupUi(this);

    setup();
}

BlockTextOnPath::~BlockTextOnPath()
{
    delete ui;
}

void BlockTextOnPath::setup()
{
    ui->comboType->addItem(tr("Default"), QVariant::fromValue(TextOnPathType::Default));
    ui->comboType->addItem(tr("Stair Step"), QVariant::fromValue(TextOnPathType::StairStep));
    ui->comboType->addItem(tr("Skew"), QVariant::fromValue(TextOnPathType::Skew));
}
