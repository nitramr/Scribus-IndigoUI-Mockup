#include "colorswatches.h"
#include "ui_colorswatches.h"

#include "iconmanager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ColorSwatches::ColorSwatches(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSwatches)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

ColorSwatches::~ColorSwatches()
{
    delete ui;
}

void ColorSwatches::setConfiguration(ItemFillMode mode)
{
    m_configuration = mode;

    switch(m_configuration){
    case ItemFillMode::Solid:
        ui->listSwatches->setPixmapType(ColorListView::fancyPixmap);
        break;
    case ItemFillMode::Gradient:
        ui->listSwatches->setPixmapType(ColorListView::widePixmap);
        break;
    case ItemFillMode::Pattern:
        ui->listSwatches->setPixmapType(ColorListView::widePixmap);
        break;
    case ItemFillMode::Image:

        break;

    }

    dummyContent();

}

ItemFillMode ColorSwatches::configuration()
{
    return m_configuration;
}

void ColorSwatches::setup()
{

    IconManager& iconManager = IconManager::instance();

    dialogColorSwatchImport = new DialogColorSwatchImport();

    // Buttons
    ui->buttonAdd->setVisible(false);
    //ui->buttonAdd->setIcon(iconManager.icon("add"));
    ui->buttonRemove->setIcon(iconManager.icon("delete"));
    ui->buttonImport->setIcon(iconManager.icon("import"));
    ui->buttonLoad->setIcon(iconManager.icon("load"));
    ui->buttonSave->setIcon(iconManager.icon("save"));
    ui->buttonUnused->setIcon(iconManager.icon("remove-unused"));
    ui->buttonDuplicate->setIcon(iconManager.icon("copy"));

   // ui->buttonAdd->setToolTip(tr("Add a new color within the current color set"));
    ui->buttonRemove->setToolTip(tr("Delete the current selected color"));
    ui->buttonImport->setToolTip(tr("Import color to the current set from an existings document"));
    ui->buttonLoad->setToolTip(tr("Load color set"));
    ui->buttonSave->setToolTip(tr("Save the current color set"));
    ui->buttonUnused->setToolTip(tr("Remove unused colors from currently selected document's color set"));
    ui->buttonDuplicate->setToolTip(tr("Make a copy of the currently selected color"));

    // Default Values
    ui->listSwatches->setPixmapType(ColorListView::fancyPixmap);

    dummyContent();

}

void ColorSwatches::connectSlots()
{
    connect(ui->listSwatches, &ColorListView::currentRowChanged, this, &ColorSwatches::changedColor );

    // Buttons Parent
    connect(ui->buttonLoad, &QToolButton::pressed, this, &ColorSwatches::showColorSwatchImportDialog);
}

void ColorSwatches::dummyContent()
{
    ui->listSwatches->clear();

    switch(m_configuration){
    case ItemFillMode::Solid:{
        ScColor col;
        col.setCmykF(1,.5,.5,0);
        ui->listSwatches->insertItem(0, col, col.name());
        col.setCmykF(1,1,0,0);
        ui->listSwatches->insertItem(0, col, col.name());
        col.setLab(100,64,23);
        col.setRegistrationColor(true);
        ui->listSwatches->insertItem(0, col, col.name());
        col.setRgb(100,64,128);
        col.setSpotColor(true);
        col.setRegistrationColor(false);
        ui->listSwatches->insertItem(0, col, col.name());
        col.setRgb(255,255,255);
        col.setSpotColor(false);
        col.setRegistrationColor(false);
        ui->listSwatches->insertItem(0, col, col.name());
        col.setRgb(0,0,0);
        col.setIsOutOfGamut(true);
        ui->listSwatches->insertItem(0, col, col.name());
    }
        break;
    case ItemFillMode::Gradient:{

    }
        break;
    case ItemFillMode::Pattern:


        break;
    case ItemFillMode::Image:

        break;

    }



}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ColorSwatches::changedColor()
{
   ColorListModel* colorListModel = qobject_cast<ColorListModel*>(ui->listSwatches->model());
   emit colorChanged( colorListModel->colors().toList().at(ui->listSwatches->currentRow()).m_color );

}

void ColorSwatches::showColorSwatchImportDialog()
{
    if (dialogColorSwatchImport->exec())
    {

    }
}
