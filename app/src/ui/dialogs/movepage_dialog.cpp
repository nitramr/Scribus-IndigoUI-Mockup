#include "movepage_dialog.h"
#include "ui_movepage_dialog.h"

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

MovePageDialog::MovePageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovePageDialog)
{
    ui->setupUi(this);

    setup();

    setWindowTitle( tr( "Move Pages" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

MovePageDialog::~MovePageDialog()
{
    delete ui;
}

void MovePageDialog::setup()
{

}
