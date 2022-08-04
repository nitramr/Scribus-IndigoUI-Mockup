#include "dialog_importparentpage.h"
#include "ui_dialog_importparentpage.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogImportParentPage::DialogImportParentPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImportParentPage)
{
    ui->setupUi(this);

    setup();
    connectSlots();

    setWindowTitle( tr( "Import Parent Page" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogImportParentPage::~DialogImportParentPage()
{
    delete ui;
}

void DialogImportParentPage::setup()
{

}

void DialogImportParentPage::connectSlots()
{

}
