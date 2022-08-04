#include "dialog_colorswatchimport.h"
#include "ui_dialog_colorswatchimport.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DialogColorSwatchImport::DialogColorSwatchImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColorSwatchImport)
{
    ui->setupUi(this);
    setup();

    setWindowTitle( tr( "Load Color Set" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());
}

DialogColorSwatchImport::~DialogColorSwatchImport()
{
    delete ui;
}

void DialogColorSwatchImport::setup()
{
    // tmp
    ui->listSwatches->setPixmapType(ColorListView::fancyPixmap);

    ScColor col;
    col.setCmykF(1,.5,.5,0);
    ui->listSwatches->insertItem(0, col, col.name());
    col.setCmykF(1,1,0,0);
    ui->listSwatches->insertItem(0, col, col.name());
    col.setLab(100,64,23);
    col.setRegistrationColor(true);
    ui->listSwatches->insertItem(0, col, col.name());
    col.setRgb(100,64,128);
    col.setSpotColor(true);
    col.setRegistrationColor(false);
    ui->listSwatches->insertItem(0, col, col.name());
    col.setRgb(255,255,255);
    col.setSpotColor(false);
    col.setRegistrationColor(false);
    ui->listSwatches->insertItem(0, col, col.name());
    col.setRgb(0,0,0);
    col.setIsOutOfGamut(true);
    ui->listSwatches->insertItem(0, col, col.name());
}
