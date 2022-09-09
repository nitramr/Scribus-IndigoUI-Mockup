#include "block_text_alignment.h"
#include "colorpicker.h"
#include "icon_manager.h"
#include "popup_menu.h"
#include "qbuttongroup.h"
#include "ui_block_text_alignment.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockTextAlignment::BlockTextAlignment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextAlignment)
{
    ui->setupUi(this);

    setup();
}

BlockTextAlignment::~BlockTextAlignment()
{
    delete ui;
}

void BlockTextAlignment::setup()
{

    IconManager &iconManager = IconManager::instance();

    blockOutline = new BlockTextOutline;

    ui->buttonLTR->setIcon(iconManager.icon("text-direction-ltr"));
    ui->buttonRTL->setIcon(iconManager.icon("text-direction-rtl"));

    ui->buttonAlignBottom->setIcon(iconManager.icon("text-align-bottom"));
    ui->buttonAlignCenter->setIcon(iconManager.icon("text-align-center"));
    ui->buttonAlignForcedJustified->setIcon(iconManager.icon("text-align-forcedjustified"));
    ui->buttonAlignJustified->setIcon(iconManager.icon("text-align-justified"));
    ui->buttonAlignLeft->setIcon(iconManager.icon("text-align-left"));
    ui->buttonAlignMiddle->setIcon(iconManager.icon("text-align-middle"));
    ui->buttonAlignRight->setIcon(iconManager.icon("text-align-right"));
    ui->buttonAlignTop->setIcon(iconManager.icon("text-align-top"));

    ui->buttonOutline->setIcon(iconManager.icon("text-format-outline"));
    ui->buttonSubscript->setIcon(iconManager.icon("text-format-subscript"));
    ui->buttonSuperscript->setIcon(iconManager.icon("text-format-superscript"));
    ui->buttonStrikeout->setIcon(iconManager.icon("text-format-strikeout"));
    ui->buttonUnderline->setIcon(iconManager.icon("text-format-underline"));


    QButtonGroup *direction = new QButtonGroup();
    direction->addButton(ui->buttonLTR);
    direction->addButton(ui->buttonRTL);

    QButtonGroup *hAlignment = new QButtonGroup();
    hAlignment->addButton(ui->buttonAlignLeft);
    hAlignment->addButton(ui->buttonAlignCenter);
    hAlignment->addButton(ui->buttonAlignRight);
    hAlignment->addButton(ui->buttonAlignJustified);
    hAlignment->addButton(ui->buttonAlignForcedJustified);

    QButtonGroup *vAlignment = new QButtonGroup();
    vAlignment->addButton(ui->buttonAlignTop);
    vAlignment->addButton(ui->buttonAlignMiddle);
    vAlignment->addButton(ui->buttonAlignBottom);


    // Add menu
    addMenu(ui->buttonOutline, blockOutline);


}

void BlockTextAlignment::addMenu(QToolButton *button, QWidget *menuPanel)
{
    PopupMenu * menu = new PopupMenu(menuPanel);
    button->setMenu(menu);
    button->setPopupMode(QToolButton::DelayedPopup);
   // button->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );
}
