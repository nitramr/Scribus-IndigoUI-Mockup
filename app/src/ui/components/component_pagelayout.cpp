#include "component_pagelayout.h"
#include "ui_component_pagelayout.h"
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ComponentPageLayout::ComponentPageLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentPageLayout)
{
    ui->setupUi(this);

    orientationButtons = new QButtonGroup();

    setup();

}

ComponentPageLayout::~ComponentPageLayout()
{
    delete ui;
}


void ComponentPageLayout::setup()
{

    QStringList pageSizes = QStringList();
    pageSizes.append("A4");
    pageSizes.append("Letter");
    pageSizes.append("Custom");


    // Layout
    ui->comboPageSize->addItems(pageSizes);
    ui->comboPageSize->setCurrentIndex(0);


    // Orientation
    ui->buttonPortrait->setIcon(IconManager::instance().icon("document-portrait"));
    ui->buttonLandscape->setIcon(IconManager::instance().icon("document-landscape"));
    orientationButtons->addButton(ui->buttonPortrait);
    orientationButtons->addButton(ui->buttonLandscape);


}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

QComboBox *ComponentPageLayout::comboPageSize()
{
    return ui->comboPageSize;
}

QComboBox *ComponentPageLayout::comboUnits()
{
    return ui->comboUnits;
}

AdvancedSpinBox *ComponentPageLayout::numberPageWidth()
{
    return ui->numberWidth;
}

AdvancedSpinBox *ComponentPageLayout::numberPageHeight()
{
    return ui->numberHeight;
}

QCheckBox *ComponentPageLayout::checkBoxMoveObjects()
{
    return ui->checkBoxMoveObjects;
}

void ComponentPageLayout::setUnitVisibility(bool isVisible)
{
    ui->comboUnits->setVisible(isVisible);
    ui->labelUnits->setVisible(isVisible);
}

bool ComponentPageLayout::unitVisibility()
{
    return ui->comboUnits->isVisible() + ui->labelUnits->isVisible();
}

void ComponentPageLayout::setMoveObjectsVisibility(bool isVisible)
{
    ui->checkBoxMoveObjects->setVisible(isVisible);
}

bool ComponentPageLayout::moveObjectsVisibility()
{
    return ui->checkBoxMoveObjects->isVisible();
}
