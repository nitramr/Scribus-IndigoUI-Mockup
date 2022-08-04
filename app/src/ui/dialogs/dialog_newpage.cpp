#include "dialog_newpage.h"
#include "ui_dialog_newpage.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogNewPage::DialogNewPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewPage)
{
    ui->setupUi(this);


    setup();

    setWindowTitle( tr( "Insert Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());

}

DialogNewPage::~DialogNewPage()
{
    delete ui;
}


void DialogNewPage::setup()
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

void DialogNewPage::setPageLayout(PageLayout pageLayout)
{
    ui->componentParentPages->setPageLayout(pageLayout);
    adjustSize();
}
