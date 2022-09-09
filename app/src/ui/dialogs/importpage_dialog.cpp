#include "importpage_dialog.h"
#include "ui_importpage_dialog.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ImportPageDialog::ImportPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportPageDialog)
{
    ui->setupUi(this);

    setup();
    connectSlots();

    setWindowTitle( tr( "Import Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

ImportPageDialog::~ImportPageDialog()
{
    delete ui;
}

void ImportPageDialog::setup()
{
    int index = ui->componentInsertPage->comboInsertType()->findData(QVariant::fromValue(PageInsert::Swap));
    ui->componentInsertPage->comboInsertType()->removeItem(index);
    ui->componentInsertPage->setEnabled(false);
}

void ImportPageDialog::connectSlots()
{
    connect(ui->checkboxCreatePage, &QCheckBox::clicked, this, &ImportPageDialog::enableInsertPage);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ImportPageDialog::enableInsertPage(bool isEnabled)
{
    ui->componentInsertPage->setEnabled(isEnabled);
}
