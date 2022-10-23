#include "stylemanager_dialog.h"
#include "ui_stylemanager_dialog.h"
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

StyleManagerDialog::StyleManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleManagerDialog)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

StyleManagerDialog::~StyleManagerDialog()
{
    delete ui;
}

void StyleManagerDialog::setup()
{
    IconManager &iconManager = IconManager::instance();

    this->setWindowTitle(tr("Style Manager"));
    ui->styleListView->headerItem()->setText(0, tr("Styles"));


    // Add root style types
    StyleListViewItem *styleItemParagraph = new StyleListViewItem(ui->styleListView, tr("Paragraph"));
    styleItemParagraph->setIcon(0, iconManager.icon("paragraph-style") );
    StyleListViewItem *styleItemCharacter = new StyleListViewItem(ui->styleListView, tr("Character"));
    styleItemCharacter->setIcon(0, iconManager.icon("character-style") );
    StyleListViewItem *styleItemTable = new StyleListViewItem(ui->styleListView, tr("Table"));
    styleItemTable->setIcon(0, iconManager.icon("table-style") );
    StyleListViewItem *styleItemCell = new StyleListViewItem(ui->styleListView, tr("Cell"));
    styleItemCell->setIcon(0, iconManager.icon("table-cell-style") );
    StyleListViewItem *styleItemLine = new StyleListViewItem(ui->styleListView, tr("Line"));
    styleItemLine->setIcon(0, iconManager.icon("stroke-style") );
    StyleListViewItem *styleItemNote = new StyleListViewItem(ui->styleListView, tr("Note"));
    styleItemNote->setIcon(0, iconManager.icon("note-style") );

    ui->styleListView->addTopLevelItem(styleItemParagraph);
    ui->styleListView->expandItem(styleItemParagraph);
    ui->styleListView->addTopLevelItem(styleItemCharacter);
    ui->styleListView->expandItem(styleItemCharacter);
    ui->styleListView->addTopLevelItem(styleItemTable);
    ui->styleListView->expandItem(styleItemTable);
    ui->styleListView->addTopLevelItem(styleItemCell);
    ui->styleListView->expandItem(styleItemCell);
    ui->styleListView->addTopLevelItem(styleItemLine);
    ui->styleListView->expandItem(styleItemLine);
    ui->styleListView->addTopLevelItem(styleItemNote);
    ui->styleListView->expandItem(styleItemNote);

    // Add default styles
    StyleListViewItem *styleItemParagraphDefault = new StyleListViewItem(styleItemParagraph, tr("Default Paragraph Style"), StyleType::Paragraph);
    styleItemParagraphDefault->setIcon(0, iconManager.icon("paragraph-style") );

    StyleListViewItem *styleItemCharacterDefault = new StyleListViewItem(styleItemCharacter, tr("Default Character Style"), StyleType::Character);
    styleItemCharacterDefault->setIcon(0, iconManager.icon("character-style") );

    StyleListViewItem *styleItemTableDefault = new StyleListViewItem(styleItemTable, tr("Default Table Style"), StyleType::Table);
    styleItemTableDefault->setIcon(0, iconManager.icon("table-style") );

    StyleListViewItem *styleItemTableCellDefault = new StyleListViewItem(styleItemCell, tr("Default Cell Style"), StyleType::TableCell);
    styleItemTableCellDefault->setIcon(0, iconManager.icon("table-cell-style") );

    StyleListViewItem *styleItemLineDefault = new StyleListViewItem(styleItemLine, tr("Default Line Style"), StyleType::Stroke);
    styleItemLineDefault->setIcon(0, iconManager.icon("stroke-style") );

    StyleListViewItem *styleItemNoteDefault = new StyleListViewItem(styleItemNote, tr("Default Note Style"), StyleType::Note);
    styleItemNoteDefault->setIcon(0, iconManager.icon("note-style") );


    // Buttons
    ui->buttonNewStyle->setIcon( iconManager.icon("new") );
    ui->buttonCopyStyle->setIcon( iconManager.icon("copy") );
    ui->buttonDeleteStyle->setIcon( iconManager.icon("delete") );
    ui->buttonImportStyle->setIcon( iconManager.icon("import") );

}

void StyleManagerDialog::connectSlots()
{
    connect(ui->styleListView, &StyleListView::itemClicked, this, &StyleManagerDialog::changeStyleSelection);
}


/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */



/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void StyleManagerDialog::changeStyleSelection(QTreeWidgetItem * item)
{
    if(!item) return;

    StyleListViewItem * styleItem = static_cast<StyleListViewItem *>(item);

    switch(styleItem->rootName()){
    case StyleType::Paragraph:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case StyleType::Character:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case StyleType::Table:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(2);
        break;
    case StyleType::TableCell:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(3);
        break;
    case StyleType::Stroke:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(4);
        break;
    case StyleType::Note:
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(5);
        break;
    default:
    case StyleType::None:
        ui->stackedWidget->setEnabled(false);

        break;
    }

}
