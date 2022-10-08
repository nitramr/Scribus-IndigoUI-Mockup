#include "quicktool_edit.h"
#include "icon_manager.h"
#include "ui_quicktool_edit.h"

QuickToolEdit::QuickToolEdit(QWidget *parent) :
    FormWidget(parent),
    ui(new Ui::QuickToolEdit)
{
    ui->setupUi(this);

    setup();
}

QuickToolEdit::~QuickToolEdit()
{
    delete ui;
}

void QuickToolEdit::setup()
{

    IconManager &iconManager = IconManager::instance();

    // Buttons
    ui->buttonUndo->setIcon( iconManager.icon("undo") );
    ui->buttonRedo->setIcon( iconManager.icon("redo") );
    ui->buttonCut->setIcon( iconManager.icon("cut") );
    ui->buttonCopy->setIcon( iconManager.icon("copy") );
    ui->buttonPaste->setIcon( iconManager.icon("paste") );

}
