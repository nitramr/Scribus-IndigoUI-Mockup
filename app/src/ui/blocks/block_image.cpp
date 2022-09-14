#include "block_image.h"
#include "ui_block_image.h"
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

BlockImage::BlockImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockImage)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

BlockImage::~BlockImage()
{
    delete ui;
}

void BlockImage::setup()
{

    ui->buttonLink->setIcon(IconManager::instance().icon("link"));

    QStringList pdfCompressionMethod = QStringList();
    pdfCompressionMethod.append("Global");
    pdfCompressionMethod.append("Automatic");
    pdfCompressionMethod.append("Lossy - JPEG");
    pdfCompressionMethod.append("Lossless - Zip");
    pdfCompressionMethod.append("None");

    QStringList pdfCompressionQuality = QStringList();
    pdfCompressionQuality.append("Global");
    pdfCompressionQuality.append("Maximum");
    pdfCompressionQuality.append("High");
    pdfCompressionQuality.append("Medium");
    pdfCompressionQuality.append("Low");
    pdfCompressionQuality.append("Minimum");

    ui->comboBoxPDFCompressionMethod->addItems(pdfCompressionMethod);
    ui->comboBoxPDFCompressionQuality->addItems(pdfCompressionQuality);

}

void BlockImage::connectSlots()
{
    connect(ui->checkBoxAutoFit, &QCheckBox::toggled, this, &BlockImage::changeAutoFit);
    connect(ui->buttonLink, &QToolButton::toggled, this, &BlockImage::linkInput);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockImage::linkInput(bool state)
{
    if(state){
        ui->buttonLink->setIcon(IconManager::instance().icon("link"));
    }else{
        ui->buttonLink->setIcon(IconManager::instance().icon("link-off"));
    }

    emit signalLinkInput(state);
}

void BlockImage::changeAutoFit(bool doesFit)
{
    ui->layoutDpiX->setEnabled(!doesFit);
    ui->layoutDpiY->setEnabled(!doesFit);
    ui->layoutScaleX->setEnabled(!doesFit);
    ui->layoutScaleY->setEnabled(!doesFit);
//    ui->layoutPositionX->setEnabled(!doesFit);
//    ui->layoutPositionY->setEnabled(!doesFit);

}
