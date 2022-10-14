#include "quicktool_snap.h"
#include "icon_manager.h"
#include "ui_quicktool_snap.h"

QuickToolSnap::QuickToolSnap(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolSnap)
{
    ui->setupUi(this);

    setup();
}

QuickToolSnap::~QuickToolSnap()
{
    delete ui;
}

void QuickToolSnap::setup()
{

    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonSnapGrid->setIcon( iconManager.icon("snap-grid") );
    ui->buttonSnapGuides->setIcon( iconManager.icon("snap-guides") );
    ui->buttonSnapItems->setIcon( iconManager.icon("snap-items") );

}
