#include "quicktool_level.h"
#include "icon_manager.h"
#include "ui_quicktool_level.h"

QuickToolLevel::QuickToolLevel(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolLevel)
{
    ui->setupUi(this);

    setup();
}

QuickToolLevel::~QuickToolLevel()
{
    delete ui;
}

void QuickToolLevel::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonLayerForeground->setIcon( iconManager.icon("level-foreground") );
    ui->buttonLayerUp->setIcon( iconManager.icon("level-up") );
    ui->buttonLayerDown->setIcon( iconManager.icon("level-down") );
    ui->buttonLayerBackground->setIcon( iconManager.icon("level-background") );

}
