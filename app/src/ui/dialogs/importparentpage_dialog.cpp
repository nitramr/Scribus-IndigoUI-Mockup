#include "importparentpage_dialog.h"
#include "ui_importparentpage_dialog.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ImportParentPageDialog::ImportParentPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportParentPageDialog)
{
    ui->setupUi(this);

    setup();
    connectSlots();

    setWindowTitle( tr( "Import Parent Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

ImportParentPageDialog::~ImportParentPageDialog()
{
    delete ui;
}

void ImportParentPageDialog::setup()
{

}

void ImportParentPageDialog::connectSlots()
{

}
