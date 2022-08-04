#include "block_alignment.h"
#include "iconmanager.h"
#include "ui_block_alignment.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockAlignment::BlockAlignment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockAlignment)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockAlignment::~BlockAlignment()
{
    delete ui;
}

void BlockAlignment::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->buttonLeftAnchor->setIcon( iconManager.icon("align-left-anchor") );
    ui->buttonLeft->setIcon( iconManager.icon("align-left") );
    ui->buttonCenter->setIcon( iconManager.icon("align-center") );
    ui->buttonRight->setIcon( iconManager.icon("align-right") );
    ui->buttonRightAnchor->setIcon( iconManager.icon("align-right-anchor") );

    ui->buttonTopAnchor->setIcon( iconManager.icon("align-top-anchor") );
    ui->buttonTop->setIcon( iconManager.icon("align-top") );
    ui->buttonMiddle->setIcon( iconManager.icon("align-middle") );
    ui->buttonBottom->setIcon( iconManager.icon("align-bottom") );
    ui->buttonBottomAnchor->setIcon( iconManager.icon("align-bottom-anchor") );

    ui->comboReference->addItem(tr("First Selected"), QVariant::fromValue(AlignmentReference::FirstSelected));
    ui->comboReference->addItem(tr("Last Selected"), QVariant::fromValue(AlignmentReference::LastSelected));
    ui->comboReference->addItem(tr("Page"), QVariant::fromValue(AlignmentReference::Page));
    ui->comboReference->addItem(tr("Margins"), QVariant::fromValue(AlignmentReference::Margins));
    ui->comboReference->addItem(tr("Guides"), QVariant::fromValue(AlignmentReference::Guides));
    ui->comboReference->addItem(tr("Selection"), QVariant::fromValue(AlignmentReference::Selection));

    ui->comboMode->addItem(tr("Move"), QVariant::fromValue(AlignmentMode::Move));
    ui->comboMode->addItem(tr("Size"), QVariant::fromValue(AlignmentMode::Size));

    ui->textGuide->setVisible(false);


}

void BlockAlignment::connectSlots()
{
    connect(ui->comboReference, &QComboBox::currentIndexChanged, this, &BlockAlignment::changeReference);
}

void BlockAlignment::changeReference()
{

    AlignmentReference m_reference = static_cast<AlignmentReference>(ui->comboReference->currentData(Qt::UserRole).toInt());

    switch(m_reference){
    case AlignmentReference::Guides:
        ui->textGuide->setVisible(true);
        break;
    default:
         ui->textGuide->setVisible(false);
        break;
    }

}
