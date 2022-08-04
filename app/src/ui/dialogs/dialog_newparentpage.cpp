#include "dialog_newparentpage.h"
#include "ui_dialog_newparentpage.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogNewParentPage::DialogNewParentPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewParentPage)
{
    ui->setupUi(this);

    setup();

    setWindowTitle( tr( "New Parent Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogNewParentPage::~DialogNewParentPage()
{
    delete ui;
}


void DialogNewParentPage::setup()
{
    ui->textPageName->setText("New Parent Page");
    ui->comboParentPage->setVisible(false);
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void DialogNewParentPage::setPageLayout(PageLayout pageLayout)
{
    ui->comboParentPage->clear();

    switch(pageLayout){
    case PageLayout::Single:
        ui->comboParentPage->setVisible(false);


        break;
    case PageLayout::Double:
        ui->comboParentPage->setVisible(true);

        ui->comboParentPage->addItem("Left", QVariant::fromValue(FirstPage::Left));
        ui->comboParentPage->addItem("Right", QVariant::fromValue(FirstPage::Right));

        break;
    case PageLayout::ThreeFacing:
        ui->comboParentPage->setVisible(true);

        ui->comboParentPage->addItem("Left", QVariant::fromValue(FirstPage::Left));
        ui->comboParentPage->addItem("Middle", QVariant::fromValue(FirstPage::Middle));
        ui->comboParentPage->addItem("Right", QVariant::fromValue(FirstPage::Right));

        break;
    case PageLayout::FourFacing:
        ui->comboParentPage->setVisible(true);

        ui->comboParentPage->addItem("Left", QVariant::fromValue(FirstPage::Left));
        ui->comboParentPage->addItem("Middle Left", QVariant::fromValue(FirstPage::MiddleLeft));
        ui->comboParentPage->addItem("Middle Right", QVariant::fromValue(FirstPage::MiddleRight));
        ui->comboParentPage->addItem("Right", QVariant::fromValue(FirstPage::Right));

        break;

    }
}
