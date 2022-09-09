#include "newpage_dialog.h"
#include "ui_newpage_dialog.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

NewPageDialog::NewPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPageDialog)
{
    ui->setupUi(this);


    setup();

    setWindowTitle( tr( "Insert Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());

}

NewPageDialog::~NewPageDialog()
{
    delete ui;
}


void NewPageDialog::setup()
{
    int index = ui->componentInsertPage->comboInsertType()->findData(QVariant::fromValue(PageInsert::Swap));
    ui->componentInsertPage->comboInsertType()->removeItem(index);

    ui->componentPageLayout->setUnitVisibility(false);
}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void NewPageDialog::setPageLayout(PageLayout pageLayout)
{
    ui->componentParentPages->setPageLayout(pageLayout);
    adjustSize();
}
