#include "quicktool_layer.h"
#include "icon_manager.h"
#include "ui_quicktool_layer.h"

QuickToolLayer::QuickToolLayer(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolLayer)
{
    ui->setupUi(this);

    setup();
}

QuickToolLayer::~QuickToolLayer()
{
    delete ui;
}

void QuickToolLayer::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonLayerForeground->setIcon( iconManager.icon("layer-top") );
    ui->buttonLayerUp->setIcon( iconManager.icon("layer-up") );
    ui->buttonLayerDown->setIcon( iconManager.icon("layer-down") );
    ui->buttonLayerBackground->setIcon( iconManager.icon("layer-bottom") );

}
