#include "panel_aligndistribute.h"
#include "ui_panel_aligndistribute.h"
#include "icon_manager.h"

PanelAlignDistribute::PanelAlignDistribute(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelAlignDistribute)
{
    ui->setupUi(this);

    setup();
}

PanelAlignDistribute::~PanelAlignDistribute()
{
    delete ui;
}

void PanelAlignDistribute::setup()
{
    QIcon iconClose = IconManager::instance().icon("chevron-right");
    QIcon iconOpen = IconManager::instance().icon("chevron-down");

    // Blocks
    blockAlignment      = new BlockAlignment();
    blockDistribution   = new BlockDistribution();

    // Section
    ui->sectionAlignment->setCollapseIcons(iconClose, iconOpen);
    ui->sectionDistribution->setCollapseIcons(iconClose, iconOpen);

    // Add blocks
    ui->layoutAlignment->layout()->addWidget(blockAlignment);
    ui->layoutDistribution->layout()->addWidget(blockDistribution);

}
