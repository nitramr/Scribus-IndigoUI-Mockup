#include "component_parentpageselector.h"
#include "ui_component_parentpageselector.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

ComponentParentPageSelector::ComponentParentPageSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentParentPageSelector)
{
    ui->setupUi(this);

    setup();
    setPageLayout(PageLayout::Single);
}

ComponentParentPageSelector::~ComponentParentPageSelector()
{
    delete ui;
}


void ComponentParentPageSelector::setup()
{
    QStringList dummyParentPage = QStringList();
    dummyParentPage.append("Normal");
    dummyParentPage.append("Normal Left");

    ui->comboParentPage->addItems(dummyParentPage);
    ui->comboLeft->addItems(dummyParentPage);
    ui->comboMiddleLeft->addItems(dummyParentPage);
    ui->comboMiddle->addItems(dummyParentPage);
    ui->comboMiddleRight->addItems(dummyParentPage);
    ui->comboRight->addItems(dummyParentPage);

}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void ComponentParentPageSelector::setPageLayout(PageLayout pageLayout)
{
    m_pageLayout = pageLayout;

    switch(m_pageLayout){
    case PageLayout::Single:

        ui->labelLeft->setVisible(false);
        ui->comboLeft->setVisible(false);

        ui->labelMiddleLeft->setVisible(false);
        ui->comboMiddleLeft->setVisible(false);

        ui->labelMiddle->setVisible(false);
        ui->comboMiddle->setVisible(false);

        ui->labelMiddleRight->setVisible(false);
        ui->comboMiddleRight->setVisible(false);

        ui->labelRight->setVisible(false);
        ui->comboRight->setVisible(false);

        ui->labelParentPage->setVisible(true);
        ui->comboParentPage->setVisible(true);

        break;
    case PageLayout::Double:
        ui->labelLeft->setVisible(true);
        ui->comboLeft->setVisible(true);

        ui->labelMiddleLeft->setVisible(false);
        ui->comboMiddleLeft->setVisible(false);

        ui->labelMiddle->setVisible(false);
        ui->comboMiddle->setVisible(false);

        ui->labelMiddleRight->setVisible(false);
        ui->comboMiddleRight->setVisible(false);

        ui->labelRight->setVisible(true);
        ui->comboRight->setVisible(true);

        ui->labelParentPage->setVisible(false);
        ui->comboParentPage->setVisible(false);
        break;
    case PageLayout::ThreeFacing:
        ui->labelLeft->setVisible(true);
        ui->comboLeft->setVisible(true);

        ui->labelMiddleLeft->setVisible(false);
        ui->comboMiddleLeft->setVisible(false);

        ui->labelMiddle->setVisible(true);
        ui->comboMiddle->setVisible(true);

        ui->labelMiddleRight->setVisible(false);
        ui->comboMiddleRight->setVisible(false);

        ui->labelRight->setVisible(true);
        ui->comboRight->setVisible(true);

        ui->labelParentPage->setVisible(false);
        ui->comboParentPage->setVisible(false);
        break;
    case PageLayout::FourFacing:
        ui->labelLeft->setVisible(true);
        ui->comboLeft->setVisible(true);

        ui->labelMiddleLeft->setVisible(true);
        ui->comboMiddleLeft->setVisible(true);

        ui->labelMiddle->setVisible(false);
        ui->comboMiddle->setVisible(false);

        ui->labelMiddleRight->setVisible(true);
        ui->comboMiddleRight->setVisible(true);

        ui->labelRight->setVisible(true);
        ui->comboRight->setVisible(true);

        ui->labelParentPage->setVisible(false);
        ui->comboParentPage->setVisible(false);
        break;

    }
}

PageLayout ComponentParentPageSelector::pageLayout()
{
    return m_pageLayout;
}
