#include "dialog_movepage.h"
#include "ui_dialog_movepage.h"

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

DialogMovePage::DialogMovePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMovePage)
{
    ui->setupUi(this);

    setup();

    setWindowTitle( tr( "Move Pages" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogMovePage::~DialogMovePage()
{
    delete ui;
}

void DialogMovePage::setup()
{

}
