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

    // Image Render Quality
    ui->comboImageQuality->addItem( tr("High"), QVariant::fromValue(ImageRenderQuality::High) );
    ui->comboImageQuality->addItem( tr("Normal"), QVariant::fromValue(ImageRenderQuality::Normal) );
    ui->comboImageQuality->addItem( tr("Low"), QVariant::fromValue(ImageRenderQuality::Low) );
    ui->comboImageQuality->setCurrentIndex(1);

    // Buttons
    ui->buttonColorManagement->setIcon( iconManager.icon("preview-colormanagement") );
    ui->buttonPreview->setIcon( iconManager.icon("preview-document") );
    ui->buttonEdit->setIcon( iconManager.icon("preview-edit") );


}
