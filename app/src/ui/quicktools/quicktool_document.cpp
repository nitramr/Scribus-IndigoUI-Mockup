#include "quicktool_document.h"
#include "icon_manager.h"
#include "ui_quicktool_document.h"

QuickToolDocument::QuickToolDocument(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolDocument)
{
    ui->setupUi(this);

    setup();
}

QuickToolDocument::~QuickToolDocument()
{
    delete ui;
}

void QuickToolDocument::setup()
{
    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonNew->setIcon( iconManager.icon("file-new") );
    ui->buttonOpen->setIcon( iconManager.icon("open") );
    ui->buttonSave->setIcon( iconManager.icon("save") );
    ui->buttonPrint->setIcon( iconManager.icon("print") );
    ui->buttonPreflight->setIcon( iconManager.icon("preflight") );
    ui->buttonSavePDF->setIcon( iconManager.icon("save-pdf") );

}
