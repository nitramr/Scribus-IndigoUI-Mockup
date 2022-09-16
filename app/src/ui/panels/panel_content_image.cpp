#include "panel_content_image.h"
#include "popup_menu/popup_menu.h"
#include "icon_manager.h"
#include "ui_panel_content_image.h"

PanelContentImage::PanelContentImage(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelContentImage)
{
    ui->setupUi(this);
    setup();
    connectSlots();
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
    blockImage          = new BlockImage();
    blockImageEffects   = new BlockImageEffects();


    // Section
    ui->sectionImage->setCollapseIcons(iconClose, iconOpen);
    ui->sectionImageEffects->setCollapseIcons(iconClose, iconOpen);


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
    ui->layoutImageEffects->layout()->addWidget(blockImageEffects);

}

void PanelContentImage::connectSlots()
{
    connect(ui->sectionImageEffects, &SectionContainer::collapsedState, this, &PanelContentImage::updateLayout);
}

void PanelContentImage::updateLayout(bool isCollapsed)
{
    if(!isCollapsed){
        ui->sectionImageEffects->setSizePolicy(ui->sectionImageEffects->sizePolicy().horizontalPolicy(), QSizePolicy::Expanding);
        ui->verticalSpacer->changeSize(this->width(), 0, ui->verticalSpacer->sizePolicy().horizontalPolicy(), QSizePolicy::Maximum );
    }else{
        ui->sectionImageEffects->setSizePolicy(ui->sectionImageEffects->sizePolicy().horizontalPolicy(), QSizePolicy::Maximum);
        ui->verticalSpacer->changeSize(this->width(), this->height(), ui->verticalSpacer->sizePolicy().horizontalPolicy(), QSizePolicy::Expanding );
    }
}

