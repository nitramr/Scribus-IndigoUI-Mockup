#include "block_stroke_advanced.h"

#include <QButtonGroup>

#include "iconmanager.h"
#include "ui_block_stroke_advanced.h"

BlockStrokeAdvanced::BlockStrokeAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockStrokeAdvanced)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockStrokeAdvanced::~BlockStrokeAdvanced()
{
    delete ui;
}

void BlockStrokeAdvanced::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->buttonCapFlat->setIcon(iconManager.icon("stroke-cap-flat"));
    ui->buttonCapRound->setIcon(iconManager.icon("stroke-cap-round"));
    ui->buttonCapSquare->setIcon(iconManager.icon("stroke-cap-square"));

    QButtonGroup *caps = new QButtonGroup;
    caps->addButton(ui->buttonCapFlat);
    caps->addButton(ui->buttonCapRound);
    caps->addButton(ui->buttonCapSquare);


    ui->buttonJoinBevel->setIcon(iconManager.icon("stroke-join-bevel"));
    ui->buttonJoinMiter->setIcon(iconManager.icon("stroke-join-miter"));
    ui->buttonJoinRound->setIcon(iconManager.icon("stroke-join-round"));

    QButtonGroup *joins = new QButtonGroup;
    joins->addButton(ui->buttonJoinBevel);
    joins->addButton(ui->buttonJoinMiter);
    joins->addButton(ui->buttonJoinRound);

    ui->comboShapeStart->setArrowDirection(ArrowDirection::StartArrow);
    ui->comboShapeEnd->setArrowDirection(ArrowDirection::EndArrow);


}

void BlockStrokeAdvanced::connectSlots()
{

}
