#include "dialog_managepageproperties.h"
#include "ui_dialog_managepageproperties.h"

DialogManagePageProperties::DialogManagePageProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogManagePageProperties)
{
    ui->setupUi(this);
    setup();

    setWindowTitle( tr( "Manage Page Properties" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogManagePageProperties::~DialogManagePageProperties()
{
    delete ui;
}

void DialogManagePageProperties::setup()
{
    ui->componentPageLayout->setUnitVisibility(false);
}
