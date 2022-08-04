#include "component_margins.h"
#include "ui_component_margins.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

ComponentMargins::ComponentMargins(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentMargins)
{
    ui->setupUi(this);

    setup();
}

ComponentMargins::~ComponentMargins()
{
    delete ui;
}



void ComponentMargins::setup()
{
    QStringList marginPreset = QStringList();
    marginPreset.append("None");
    marginPreset.append("Gutenberg");
    marginPreset.append("Magazine");
    marginPreset.append("Fibonacci");
    marginPreset.append("Golden Mean");
    marginPreset.append("Nine Parts");

    // Margin
    ui->comboMarginPresets->addItems(marginPreset);
    ui->comboMarginPresets->setCurrentIndex(0);
}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

ComponentSpaceInput *ComponentMargins::componentSpaceInput()
{
    return ui->componentMargins;
}

QComboBox *ComponentMargins::comboMarginPreset()
{
    return ui->comboMarginPresets;
}

QPushButton *ComponentMargins::buttonPrinterMargins()
{
    return ui->buttonMarginPrinter;
}

