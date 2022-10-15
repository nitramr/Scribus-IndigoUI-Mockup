#include "stylemanager_dialog.h"
#include "ui_stylemanager_dialog.h"

StyleManagerDialog::StyleManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleManagerDialog)
{
    ui->setupUi(this);
}

StyleManagerDialog::~StyleManagerDialog()
{
    delete ui;
}
