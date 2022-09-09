#include "block_paragraph.h"
#include "icon_manager.h"
#include <QButtonGroup>
#include "ui_block_paragraph.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockParagraph::BlockParagraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockParagraph)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockParagraph::~BlockParagraph()
{
    delete ui;
}



void BlockParagraph::setup()
{
    IconManager &iconManager = IconManager::instance();



    QStringList mode = QStringList();
    mode.append("Gap");
    mode.append("Width");

    QButtonGroup * groupOffset = new QButtonGroup();
    groupOffset->addButton(ui->buttonOffsetBaseline);
    groupOffset->addButton(ui->buttonOffsetFontAscent);
    groupOffset->addButton(ui->buttonOffsetLineSpace);
    groupOffset->addButton(ui->buttonOffsetMaxAscent);

    QButtonGroup * groupMargin = new QButtonGroup();
    groupMargin->addButton(ui->buttonMarginBoth);
    groupMargin->addButton(ui->buttonMarginLeft);
    groupMargin->addButton(ui->buttonMarginNone);
    groupMargin->addButton(ui->buttonMarginRight);

    ui->comboMode->addItems(mode);
    ui->comboMode->setEnabled(false);
    ui->numberSize->setEnabled(false);

    ui->layoutSpaceAbove->setPixmap(iconManager.pixmap("paragraph-space-above"));
    ui->layoutSpaceBelow->setPixmap(iconManager.pixmap("paragraph-space-below"));

    ui->buttonOffsetBaseline->setIcon(iconManager.icon("paragraph-offset-baseline"));
    ui->buttonOffsetFontAscent->setIcon(iconManager.icon("paragraph-offset-fontascent"));
    ui->buttonOffsetLineSpace->setIcon(iconManager.icon("paragraph-offset-linespace"));
    ui->buttonOffsetMaxAscent->setIcon(iconManager.icon("paragraph-offset-maxascent"));

    ui->buttonMarginNone->setIcon(iconManager.icon("paragraph-margin-none"));
    ui->buttonMarginLeft->setIcon(iconManager.icon("paragraph-margin-left"));
    ui->buttonMarginRight->setIcon(iconManager.icon("paragraph-margin-right"));
    ui->buttonMarginBoth->setIcon(iconManager.icon("paragraph-margin-both"));
    ui->buttonMarginReset->setIcon(iconManager.icon("paragraph-margin-reset"));


}

void BlockParagraph::connectSlots()
{
    connect(ui->numberColumns, &QSpinBox::valueChanged, this, &BlockParagraph::columnsChanged);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */


void BlockParagraph::columnsChanged(int count)
{
    if(count > 1){
        ui->comboMode->setEnabled(true);
        ui->numberSize->setEnabled(true);
    }else{
        ui->comboMode->setEnabled(false);
        ui->numberSize->setEnabled(false);
    }
}
