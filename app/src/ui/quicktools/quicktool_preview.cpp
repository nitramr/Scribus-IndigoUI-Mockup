#include "quicktool_preview.h"
#include "colorblind.h"
#include "icon_manager.h"
#include "ui_quicktool_preview.h"
#include "enums.h"

QuickToolPreview::QuickToolPreview(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolPreview)
{
    ui->setupUi(this);

    setup();
}

QuickToolPreview::~QuickToolPreview()
{
    delete ui;
}

void QuickToolPreview::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonColorManagement->setIcon( iconManager.icon("preview-colormanagement") );
    ui->buttonPreview->setIcon( iconManager.icon("preview-document") );
    ui->buttonEdit->setIcon( iconManager.icon("preview-edit") );


}
