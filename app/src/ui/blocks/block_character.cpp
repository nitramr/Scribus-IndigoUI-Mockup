#include "block_character.h"
#include "icon_manager.h"
#include "ui_block_character.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockCharacter::BlockCharacter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockCharacter)
{
    ui->setupUi(this);

    setup();
}

BlockCharacter::~BlockCharacter()
{
    delete ui;
}

void BlockCharacter::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->layoutCharacterHeight->setPixmap(iconManager.pixmap("character-scale-height"));
    ui->layoutCharacterWidth->setPixmap(iconManager.pixmap("character-scale-width"));
    ui->layoutSpaceWidth->setPixmap(iconManager.pixmap("character-scale-space"));
    ui->layoutManualTracking->setPixmap(iconManager.pixmap("character-tracking"));
    ui->layoutOffsetBaseline->setPixmap(iconManager.pixmap("character-offset-baseline"));

}
