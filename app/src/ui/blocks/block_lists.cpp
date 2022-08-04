#include "block_lists.h"
#include "ui_block_lists.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

BlockLists::BlockLists(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockLists)
{
    ui->setupUi(this);
    setup();
    connectSlots();

}

BlockLists::~BlockLists()
{
    delete ui;
}

void BlockLists::setup()
{
    // ListType
    ui->comboListType->addItem("None", QVariant::fromValue(ListType::None));
    ui->comboListType->addItem("Drop Cap", QVariant::fromValue(ListType::DropCap));
    ui->comboListType->addItem("Bullet List", QVariant::fromValue(ListType::Bullet));
    ui->comboListType->addItem("Numbered List", QVariant::fromValue(ListType::Numbered));

    QStringList formats = QStringList();
    formats.append("1, 2, 3, ...");
    formats.append("i, ii, iii, ...");
    formats.append("I, II, III, ...");
    formats.append("a, b, c, ...");
    formats.append("A, B, C, ...");
    ui->comboFormat->addItems(formats);

    QStringList bullets = QStringList();
    bullets.append("•");
    bullets.append("*");
    bullets.append("-");
    ui->comboBullet->addItems(bullets);

    QStringList sets = QStringList();
    sets.append("<local block>");
    sets.append("default");
    ui->comboSet->addItems(sets);

    // hide sections
    ui->widgetDropCaps->setVisible(false);
    ui->widgetBullet->setVisible(false);
    ui->widgetNumbered->setVisible(false);
    ui->widgetStyle->setVisible(false);

}

void BlockLists::connectSlots()
{

    connect(ui->comboListType,    &QComboBox::currentIndexChanged, this, &BlockLists::changeListType);

}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockLists::changeListType()
{

    m_listType = static_cast<ListType>(ui->comboListType->currentData(Qt::UserRole).toInt());

    switch(m_listType){
    case ListType::None:
        ui->widgetDropCaps->setVisible(false);
        ui->widgetBullet->setVisible(false);
        ui->widgetNumbered->setVisible(false);
        ui->widgetStyle->setVisible(false);

        break;
    case ListType::Bullet:
        ui->widgetDropCaps->setVisible(false);
        ui->widgetBullet->setVisible(true);
        ui->widgetNumbered->setVisible(false);
        ui->widgetStyle->setVisible(true);

        break;
    case ListType::Numbered:
        ui->widgetDropCaps->setVisible(false);
        ui->widgetBullet->setVisible(false);
        ui->widgetNumbered->setVisible(true);
        ui->widgetStyle->setVisible(true);

        break;
    case ListType::DropCap:
        ui->widgetDropCaps->setVisible(true);
        ui->widgetBullet->setVisible(false);
        ui->widgetNumbered->setVisible(false);
        ui->widgetStyle->setVisible(true);

        break;

    }

}
