#include "dialog_importpage.h"
#include "ui_dialog_importpage.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogImportPage::DialogImportPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImportPage)
{
    ui->setupUi(this);

    setup();
    connectSlots();

    setWindowTitle( tr( "Import Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogImportPage::~DialogImportPage()
{
    delete ui;
}

void DialogImportPage::setup()
{
    int index = ui->componentInsertPage->comboInsertType()->findData(QVariant::fromValue(PageInsert::Swap));
    ui->componentInsertPage->comboInsertType()->removeItem(index);
    ui->componentInsertPage->setEnabled(false);
}

void DialogImportPage::connectSlots()
{
    connect(ui->checkboxCreatePage, &QCheckBox::clicked, this, &DialogImportPage::enableInsertPage);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void DialogImportPage::enableInsertPage(bool isEnabled)
{
    ui->componentInsertPage->setEnabled(isEnabled);
}
