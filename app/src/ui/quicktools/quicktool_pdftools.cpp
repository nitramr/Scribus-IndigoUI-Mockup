#include "quicktool_pdftools.h"
#include "icon_manager.h"
#include "ui_quicktool_pdftools.h"

QuickToolPDFTools::QuickToolPDFTools(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolPDFTools)
{
    ui->setupUi(this);

    setup();
}

QuickToolPDFTools::~QuickToolPDFTools()
{
    delete ui;
}

void QuickToolPDFTools::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonPDFButton->setIcon( iconManager.icon("pdf-button") );
    ui->buttonPDFCheckbox->setIcon( iconManager.icon("pdf-checkbox") );
    ui->buttonPDFRadiobox->setIcon( iconManager.icon("pdf-radiobox") );
    ui->buttonPDFCombobox->setIcon( iconManager.icon("pdf-combobox") );
    ui->buttonPDFListbox->setIcon( iconManager.icon("pdf-listbox") );
    ui->buttonPDFTextbox->setIcon( iconManager.icon("pdf-textbox") );
    ui->buttonPDFTextAnnotation->setIcon( iconManager.icon("pdf-text-annotation") );
    ui->buttonPDFLinkAnnotation->setIcon( iconManager.icon("pdf-link-annotation") );

}
