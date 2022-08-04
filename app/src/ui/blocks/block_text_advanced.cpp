#include "block_text_advanced.h"
#include "colorpicker.h"
#include "qbuttongroup.h"
#include "ui_block_text_advanced.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockTextAdvanced::BlockTextAdvanced(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockTextAdvanced)
{
    ui->setupUi(this);

    setup();
}

BlockTextAdvanced::~BlockTextAdvanced()
{
    delete ui;
}

void BlockTextAdvanced::setup()
{

    QStringList languages = QStringList();
    languages.append("English");
    languages.append("German");
    languages.append("French");
    languages.append("Spanish");

    ui->comboLanguage->addItems(languages);


    QButtonGroup * capitals = new QButtonGroup();
    capitals->addButton(ui->radioCapitalsDefault);
    capitals->addButton(ui->radioCapitalsSmall);
    ui->radioCapitalsDefault->setChecked(true);

    QButtonGroup * numerals = new QButtonGroup();
    numerals->addButton(ui->radioNumerals);
    numerals->addButton(ui->radioLining);
    ui->radioNumerals->setChecked(true);

    QButtonGroup * width = new QButtonGroup();
    width->addButton(ui->radioNumeralWidth);
    width->addButton(ui->radioProportional);
    ui->radioNumeralWidth->setChecked(true);




}
