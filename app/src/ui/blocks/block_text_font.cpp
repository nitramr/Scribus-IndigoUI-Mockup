#include "block_text_font.h"
#include "icon_manager.h"
#include "popup_menu/popup_menu.h"
#include "ui_block_text_font.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockTextFont::BlockTextFont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextFont)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockTextFont::~BlockTextFont()
{
    delete ui;
}

void BlockTextFont::setup()
{

    IconManager &iconManager = IconManager::instance();

    QStringList weight = QStringList();
    weight.append("100 Thin");
    weight.append("200 Extra Light");
    weight.append("300 Light");
    weight.append("400 Regular");
    weight.append("500 Medium");
    weight.append("600 Semi Bold");
    weight.append("700 Bold");
    weight.append("800 Black");
    weight.append("900 Super");

    ui->comboWeight->addItems(weight);

    // Vertical Alignment
    ui->buttonAlignBottom->setIcon(iconManager.icon("text-align-bottom"));
    ui->buttonAlignMiddle->setIcon(iconManager.icon("text-align-middle"));
    ui->buttonAlignTop->setIcon(iconManager.icon("text-align-top"));

    QButtonGroup *vAlignment = new QButtonGroup();
    vAlignment->addButton(ui->buttonAlignTop);
    vAlignment->addButton(ui->buttonAlignMiddle);
    vAlignment->addButton(ui->buttonAlignBottom);


    blockOutline = new BlockTextOutline;

//    ui->numberLineHeight->setValue(15.0);
    ui->numberFontSize->setValue(12.0);    

    ui->buttonOutline->setIcon(iconManager.icon("text-format-outline"));
    ui->buttonSubscript->setIcon(iconManager.icon("text-format-subscript"));
    ui->buttonSuperscript->setIcon(iconManager.icon("text-format-superscript"));
    ui->buttonStrikeout->setIcon(iconManager.icon("text-format-strikeout"));
    ui->buttonUnderline->setIcon(iconManager.icon("text-format-underline"));

    // Add menu
    addMenu(ui->buttonOutline, blockOutline);

    // Color Buttons
    ui->buttonColor->setConfiguration(ColorPickerConfig::Text);
    ui->buttonColorBackground->setConfiguration(ColorPickerConfig::Text);


}

void BlockTextFont::connectSlots()
{
    connect( ui->buttonColor, &ColorButton::colorChanged, this, &BlockTextFont::setTextColor);
    connect( ui->buttonColorBackground, &ColorButton::colorChanged, this, &BlockTextFont::setBackgroundColor);
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void BlockTextFont::addMenu(QToolButton *button, QWidget *menuPanel)
{
    PopupMenu * menu = new PopupMenu(menuPanel);
    button->setMenu(menu);
    button->setPopupMode(QToolButton::DelayedPopup);
   // button->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void BlockTextFont::setTextColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonColor->setColor(color);
}

void BlockTextFont::setBackgroundColor(ScColor color)
{
    // TODO: handle selected document elements

    ui->buttonColorBackground->setColor(color);
}
