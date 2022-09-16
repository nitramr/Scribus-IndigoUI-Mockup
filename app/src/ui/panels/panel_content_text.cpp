#include "panel_content_text.h"
#include "icon_manager.h"
#include "popup_menu/popup_menu.h"
#include "ui_panel_content_text.h"

#include <QComboBox>

PanelContentText::PanelContentText(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelContentText)
{
    ui->setupUi(this);

    setup();
}

PanelContentText::~PanelContentText()
{
    delete ui;
}

void PanelContentText::setup()
{
    QIcon iconClose = IconManager::instance().icon("chevron-right");
    QIcon iconOpen = IconManager::instance().icon("chevron-down");

    QStringList stylePreset = QStringList();
    stylePreset.append("No Style");

    // Blocks
    blockTextFont           = new BlockTextFont();
    blockTextAdvanced       = new BlockTextAdvanced();
    blockParagraph          = new BlockParagraph();
    blockParagraphAdvanced  = new BlockParagraphAdvanced();
    blockCharacter          = new BlockCharacter();
    blockCharacterAdvanced  = new BlockCharacterAdvanced();
    blockLists              = new BlockLists();
    blockTextOnPath         = new BlockTextOnPath();


    // Section
    ui->sectionText->setCollapseIcons(iconClose, iconOpen);
    ui->sectionParagraph->setCollapseIcons(iconClose, iconOpen);
    ui->sectionCharacter->setCollapseIcons(iconClose, iconOpen);
    ui->sectionLists->setCollapseIcons(iconClose, iconOpen);
    ui->sectionTextOnPath->setCollapseIcons(iconClose, iconOpen);


    // Add custom elements in header
    QComboBox * comboParagraphStyle = new QComboBox();
    comboParagraphStyle->addItems(stylePreset);
    ui->sectionParagraph->addHeaderSuffixWidget(comboParagraphStyle);
    ui->sectionParagraph->addHeaderSuffixSpacing(8);

    QComboBox * comboCharacterStyle = new QComboBox();
    comboCharacterStyle->addItems(stylePreset);
    ui->sectionCharacter->addHeaderSuffixWidget(comboCharacterStyle);
    ui->sectionCharacter->addHeaderSuffixSpacing(8);


    // Add Menus
    addMenu(ui->sectionText, blockTextAdvanced);
    addMenu(ui->sectionParagraph, blockParagraphAdvanced);
    addMenu(ui->sectionCharacter, blockCharacterAdvanced);


    // Add blocks
    ui->layoutText->layout()->addWidget(blockTextFont);
    ui->layoutParagraph->layout()->addWidget(blockParagraph);
    ui->layoutCharacter->layout()->addWidget(blockCharacter);
    ui->layoutLists->layout()->addWidget(blockLists);
    ui->layoutTextOnPath->layout()->addWidget(blockTextOnPath);

}

