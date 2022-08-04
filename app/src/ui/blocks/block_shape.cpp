#include "block_shape.h"
#include "ui_block_shape.h"

#include <QButtonGroup>
#include <iconmanager.h>

BlockShape::BlockShape(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockShape)
{
    ui->setupUi(this);

    QButtonGroup * mFlowButtons = new QButtonGroup();
    mFlowButtons->addButton(ui->buttonFlowNone);
    mFlowButtons->addButton(ui->buttonFlowAroundShape);
    mFlowButtons->addButton(ui->buttonFlowAroundBoundingBox);
    mFlowButtons->addButton(ui->buttonFlowAroundContour);
    mFlowButtons->addButton(ui->buttonFlowAroundClipPath);

    ui->buttonFlowNone->setIcon(IconManager::instance().icon("flow-none"));
    ui->buttonFlowAroundShape->setIcon(IconManager::instance().icon("flow-shape"));
    ui->buttonFlowAroundBoundingBox->setIcon(IconManager::instance().icon("flow-bounding"));
    ui->buttonFlowAroundContour->setIcon(IconManager::instance().icon("flow-contour"));
    ui->buttonFlowAroundClipPath->setIcon(IconManager::instance().icon("flow-path"));

    m_lockFrame = false;
    m_lockSize = false;

    connectSlots();
}

BlockShape::~BlockShape()
{
    delete ui;
}

void BlockShape::lockFrame(bool state)
{
    m_lockFrame = state;

    if(!m_lockSize){
        ui->buttonShape->setDisabled(state);
    }

    ui->numberCornerRadius->setReadOnly(state);
}

void BlockShape::lockSize(bool state)
{
    m_lockSize = state;

    if(!m_lockFrame){
        ui->buttonShape->setDisabled(state);
    }
}

void BlockShape::connectSlots()
{

}
