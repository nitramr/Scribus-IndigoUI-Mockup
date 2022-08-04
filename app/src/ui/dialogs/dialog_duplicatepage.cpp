#include "dialog_duplicatepage.h"
#include "ui_dialog_duplicatepage.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogDuplicatePage::DialogDuplicatePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDuplicatePage)
{
    ui->setupUi(this);

    setup();

    setWindowTitle( tr( "Duplicate Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogDuplicatePage::~DialogDuplicatePage()
{
    delete ui;
}

void DialogDuplicatePage::setup()
{
    int index = ui->componentInsertPage->comboInsertType()->findData(QVariant::fromValue(PageInsert::Swap));
    ui->componentInsertPage->comboInsertType()->removeItem(index);
}
