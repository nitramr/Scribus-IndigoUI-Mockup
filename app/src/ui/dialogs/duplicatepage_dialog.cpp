#include "duplicatepage_dialog.h"
#include "ui_duplicatepage_dialog.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DuplicatePageDialog::DuplicatePageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuplicatePageDialog)
{
    ui->setupUi(this);

    setup();

    setWindowTitle( tr( "Duplicate Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DuplicatePageDialog::~DuplicatePageDialog()
{
    delete ui;
}

void DuplicatePageDialog::setup()
{
    int index = ui->componentInsertPage->comboInsertType()->findData(QVariant::fromValue(PageInsert::Swap));
    ui->componentInsertPage->comboInsertType()->removeItem(index);
}
