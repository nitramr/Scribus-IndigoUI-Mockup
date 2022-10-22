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
    StyleListViewItem *styleItemMark = new StyleListViewItem(ui->styleListView, tr("Mark"));

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
    ui->styleListView->addTopLevelItem(styleItemMark);
    ui->styleListView->expandItem(styleItemMark);

    // Add default styles
    StyleListViewItem *styleItemParagraphDefault = new StyleListViewItem(styleItemParagraph, tr("Default Paragraph Style"), "paragraph");
    styleItemParagraphDefault->setIcon(0, iconManager.icon("paragraph-style") );

    StyleListViewItem *styleItemCharacterDefault = new StyleListViewItem(styleItemCharacter, tr("Default Character Style"), "character");
    styleItemCharacterDefault->setIcon(0, iconManager.icon("character-style") );

    StyleListViewItem *styleItemTableDefault = new StyleListViewItem(styleItemTable, tr("Default Table Style"), "table");
    styleItemTableDefault->setIcon(0, iconManager.icon("table-style") );

    StyleListViewItem *styleItemTableCellDefault = new StyleListViewItem(styleItemCell, tr("Default Cell Style"), "table-cell");
    styleItemTableCellDefault->setIcon(0, iconManager.icon("table-cell-style") );

    StyleListViewItem *styleItemLineDefault = new StyleListViewItem(styleItemLine, tr("Default Line Style"), "line");
    styleItemLineDefault->setIcon(0, iconManager.icon("stroke-style") );


    // Buttons
    ui->buttonNewStyle->setIcon( iconManager.icon("new") );
    ui->buttonCopyStyle->setIcon( iconManager.icon("copy") );
    ui->buttonDeleteStyle->setIcon( iconManager.icon("delete") );
    ui->buttonImportStyle->setIcon( iconManager.icon("import") );

}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

