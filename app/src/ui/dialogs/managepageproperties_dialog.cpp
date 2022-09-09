#include "managepageproperties_dialog.h"
#include "ui_managepageproperties_dialog.h"

ManagePagePropertiesDialog::ManagePagePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagePagePropertiesDialog)
{
    ui->setupUi(this);
    setup();

    setWindowTitle( tr( "Manage Page Properties" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

ManagePagePropertiesDialog::~ManagePagePropertiesDialog()
{
    delete ui;
}

void ManagePagePropertiesDialog::setup()
{
    ui->componentPageLayout->setUnitVisibility(false);
}
