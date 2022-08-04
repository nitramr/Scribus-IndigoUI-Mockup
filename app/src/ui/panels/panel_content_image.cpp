#include "panel_content_image.h"
#include "menu_popup.h"
#include "iconmanager.h"
#include "ui_panel_content_image.h"

PanelContentImage::PanelContentImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelContentImage)
{
    ui->setupUi(this);
    setup();
}

PanelContentImage::~PanelContentImage()
{
    delete ui;
}

void PanelContentImage::setup()
{
    QIcon iconClose = IconManager::instance().icon("chevron-right");
    QIcon iconOpen = IconManager::instance().icon("chevron-down");

//    QStringList stylePreset = QStringList();
//    stylePreset.append("No Style");

    // Blocks
    blockImage           = new BlockImage();


    // Section
    ui->sectionImage->setCollapseIcons(iconClose, iconOpen);


//    // Add custom elements in header
//    QComboBox * comboParagraphStyle = new QComboBox();
//    comboParagraphStyle->addItems(stylePreset);
//    ui->sectionParagraph->addHeaderWidget(comboParagraphStyle);
//    ui->sectionParagraph->addHeaderSpacing(8);

//    QComboBox * comboCharacterStyle = new QComboBox();
//    comboCharacterStyle->addItems(stylePreset);
//    ui->sectionCharacter->addHeaderWidget(comboCharacterStyle);
//    ui->sectionCharacter->addHeaderSpacing(8);


//    // Add Menus
//    addMenu(ui->sectionText, blockTextAdvanced);
//    addMenu(ui->sectionParagraph, blockParagraphAdvanced);
//    addMenu(ui->sectionCharacter, blockCharacterAdvanced);


    // Add blocks
    ui->layoutImage->layout()->addWidget(blockImage);

}

void PanelContentImage::addMenu(SectionContainer *section, QWidget *menuPanel)
{
    MenuPopup * menu = new MenuPopup(menuPanel);
    QToolButton *buttonMenu = new QToolButton();
    buttonMenu->setMenu(menu);
    buttonMenu->setPopupMode(QToolButton::InstantPopup);
    buttonMenu->setIcon(IconManager::instance().icon("setting"));
    buttonMenu->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );

    section->addHeaderWidget(buttonMenu);
}

