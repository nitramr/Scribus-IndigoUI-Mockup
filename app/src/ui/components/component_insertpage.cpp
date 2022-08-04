#include "component_insertpage.h"
#include "ui_component_insertpage.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ComponentInsertPage::ComponentInsertPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentInsertPage)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

ComponentInsertPage::~ComponentInsertPage()
{
    delete ui;
}


void ComponentInsertPage::setup()
{
    ui->comboInsertPosition->addItem("After Page", QVariant::fromValue(PageInsert::After));
    ui->comboInsertPosition->addItem("Before Page", QVariant::fromValue(PageInsert::Before));
    ui->comboInsertPosition->addItem("At End", QVariant::fromValue(PageInsert::AtEnd));
    ui->comboInsertPosition->addItem("Swap with Page", QVariant::fromValue(PageInsert::Swap));
    ui->comboInsertPosition->setCurrentIndex(2);

    ui->numberPage->setEnabled(false);
}

void ComponentInsertPage::connectSlots()
{
    connect(ui->comboInsertPosition, &QComboBox::currentIndexChanged, this, &ComponentInsertPage::enablePageInput);
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

QComboBox *ComponentInsertPage::comboInsertType()
{
    return ui->comboInsertPosition;
}

QSpinBox *ComponentInsertPage::numberPage()
{
    return ui->numberPage;
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ComponentInsertPage::enablePageInput()
{
    PageInsert pInsert = static_cast<PageInsert>(ui->comboInsertPosition->currentData(Qt::UserRole).toInt());

    ui->numberPage->setEnabled( pInsert == PageInsert::AtEnd ? false : true );

}
